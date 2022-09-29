/*
 *
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Description:
 *      Message Handling Unit (MHU) v2 Device Driver.
 */
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <fwk_errno.h>
#include <fwk_id.h>
#include <fwk_interrupt.h>
#include <fwk_mm.h>
#include <fwk_module.h>
#include <fwk_module_idx.h>
#include <mod_mhuv2.h>
#include <mod_log.h>
#include <openamp/rpmsg_internal.h>
#include <openamp/rpmsg_client.h>

#define MHU_V2_INT_EN_OFS       0xF98
#define MHU_V2_AIDR_OFS         0xFCC

#define MHU_V2_CHCOMB           (1 << 2)

#define MHU_V2_AIDR_MINOR(_reg) ((_reg) & 0xF)

/* MHU channel context */
struct mhu2_channel_ctx {
    /* Pointer to the channel configuration */
    const struct mod_mhu2_channel_config *config;

    /* Pointer to send register set */
    struct mhu2_send_reg *send;

    /* Pointers to channel-specific register sets */
    struct mhu2_send_channel_reg *send_channel;
    struct mhu2_recv_channel_reg *recv_channel;
    fwk_id_t channel_id;
    struct rpmsg_endpoint *ept;
    const struct mod_log_api *log_api;
};

/* MHU v2 context */
static struct mhu2_ctx {
    /* Table of channel contexts */
    struct mhu2_channel_ctx *channel_ctx_table;

    /* Number of channels in the channel context table*/
    unsigned int channel_count;
    struct rpmsg_device *rdev;
} ctx;

static void mhu2_isr(uintptr_t ctx_param)
{
    struct mhu2_channel_ctx *channel_ctx = (struct mhu2_channel_ctx *)ctx_param;
    uint32_t message;
    assert(channel_ctx != NULL);

    message = channel_ctx->recv_channel->STAT;

    channel_ctx->log_api->log(MOD_LOG_GROUP_INFO,
                         "MHUv2: Message from \'%s\': 0x%x\n",
                         fwk_module_get_name(channel_ctx->channel_id),
                         message);
    channel_ctx->ept->cb(channel_ctx->ept, &message, 4, RPMSG_ADDR_ANY, NULL);
    channel_ctx->recv_channel->STAT_CLEAR = message;
}

static fwk_id_t lookup_channel(uint32_t dst) {
    struct mhu2_channel_ctx *channel_ctx;
    int ch_i = -1;
    for(unsigned int i = 0; i < ctx.channel_count; i++) {
        channel_ctx = &ctx.channel_ctx_table[i];
        if(channel_ctx->config->send == dst) {
            ch_i = i;
            break;
        }
    }
    assert(ch_i != -1);
    return fwk_id_build_element_id(FWK_ID_MODULE(FWK_MODULE_IDX_MHUV2), ch_i);
}

static int send_message(fwk_id_t channel_id, uint32_t message)
{
    int status;
    struct mhu2_channel_ctx *channel_ctx;
    struct mhu2_send_reg *send;

    status = fwk_module_check_call(channel_id);
    if (status != FWK_SUCCESS)
        return status;

    channel_ctx = &ctx.channel_ctx_table[fwk_id_get_element_idx(channel_id)];
    send = channel_ctx->send;

    /* Turn on receiver */
    send->ACCESS_REQUEST = 1;
    while (send->ACCESS_READY != 1)
        continue;
    channel_ctx->send_channel->STAT_SET = message;

    /* Signal that the receiver is no longer needed */
    send->ACCESS_REQUEST = 0;

    return FWK_SUCCESS;
}

static const struct mod_mhu_driver_api mhu2_mod_driver_api = {
        .send_message = send_message,
        .lookup_channel = lookup_channel,
};

/*
 * Framework handlers
 */

static int mhu2_init(fwk_id_t module_id,
                     unsigned int channel_count,
                     const void *unused)
{
    if (channel_count == 0) {
        /* There must be at least 1 mhu channel */
        assert(false);
        return FWK_E_PARAM;
    }

    ctx.channel_ctx_table = fwk_mm_calloc(channel_count,
        sizeof(ctx.channel_ctx_table[0]));
    if (ctx.channel_ctx_table == NULL) {
        /* Unable to allocate memory for channel context table */
        assert(false);
        return FWK_E_NOMEM;
    }
    ctx.rdev = init_rpmsg();
    ctx.channel_count = channel_count;

    return FWK_SUCCESS;
}

static int mhu2_channel_init(fwk_id_t channel_id,
                             unsigned int unused,
                             const void *data)
{
    const struct mod_mhu2_channel_config *config = data;
    struct mhu2_channel_ctx *channel_ctx;
    struct mhu2_recv_reg *recv_reg;

    if ((config == NULL) || (config->recv == 0) || (config->send == 0)) {
        assert(false);
        return FWK_E_DATA;
    }

    channel_ctx = &ctx.channel_ctx_table[fwk_id_get_element_idx(channel_id)];
    channel_ctx->send = (struct mhu2_send_reg *)config->send;

    if (config->channel >= channel_ctx->send->MSG_NO_CAP) {
        assert(false);
        return FWK_E_DATA;
    }

    channel_ctx->config = config;

    channel_ctx->send_channel = &channel_ctx->send->channel[config->channel];
    recv_reg = (struct mhu2_recv_reg *)config->recv;
    channel_ctx->recv_channel = &recv_reg->channel[config->channel];
    channel_ctx->channel_id = channel_id;
    channel_ctx->ept = endpoint_create(ctx.rdev, (void *)channel_ctx->send);

    const uint32_t aidr = *(uint32_t*)((void*)channel_ctx->recv_channel + MHU_V2_AIDR_OFS);
    if(MHU_V2_AIDR_MINOR(aidr) >= 1) {
        // Enable combined receiver interrupt for MHUv2.1
        uint32_t* reg_inten = ((void*)channel_ctx->recv_channel + MHU_V2_INT_EN_OFS);
        *reg_inten = MHU_V2_CHCOMB;
    }

    return FWK_SUCCESS;
}

static int mhu2_bind(fwk_id_t id, unsigned int round)
{
    int status;
    struct mhu2_channel_ctx *channel_ctx;

    if ((round == 1) && fwk_id_is_type(id, FWK_ID_TYPE_ELEMENT)) {
        channel_ctx = &ctx.channel_ctx_table[fwk_id_get_element_idx(id)];

        status = fwk_module_bind(FWK_ID_MODULE(FWK_MODULE_IDX_LOG),
                                     FWK_ID_API(FWK_MODULE_IDX_LOG, 0),
                                     &channel_ctx->log_api);
        if (status != FWK_SUCCESS) {
            /* Unable to bind back to SMT channel */
            assert(false);
            return status;
        }
    }
    return FWK_SUCCESS;
}

static int mhu2_process_bind_request(fwk_id_t source_id,
                                    fwk_id_t target_id,
                                    fwk_id_t api_id,
                                    const void **api)
{
    *api = &mhu2_mod_driver_api;
    return FWK_SUCCESS;
}

static int mhu2_start(fwk_id_t id)
{
    int status;
    struct mhu2_channel_ctx *channel_ctx;

    if (fwk_id_get_type(id) == FWK_ID_TYPE_MODULE)
        return FWK_SUCCESS;

    channel_ctx = &ctx.channel_ctx_table[fwk_id_get_element_idx(id)];

    // Route IRQ to NVIC
    status = fwk_interrupt_set_isr_param(channel_ctx->config->irq,
                                            &mhu2_isr,
                                            (uintptr_t)channel_ctx);
    if (status != FWK_SUCCESS) {
        /* Failed to set isr */
        assert(false);
        return status;
    }

    status = fwk_interrupt_enable(channel_ctx->config->irq);
    if (status != FWK_SUCCESS) {
        /* Failed to enable isr */
        assert(false);
        return status;
    }


    channel_ctx->log_api->log(MOD_LOG_GROUP_INFO, "MHUv2 module \'%s\' started\n",
         fwk_module_get_name(id));

    return FWK_SUCCESS;
}

/* MHU v2 module definition */
const struct fwk_module module_mhuv2 = {
    .name = "MHUV2",
    .type = FWK_MODULE_TYPE_DRIVER,
    .api_count = MOD_MHU2_API_IDX_COUNT,
    .init = mhu2_init,
    .element_init = mhu2_channel_init,
    .start = mhu2_start,
    .bind = mhu2_bind,
    .process_bind_request = mhu2_process_bind_request,
};
