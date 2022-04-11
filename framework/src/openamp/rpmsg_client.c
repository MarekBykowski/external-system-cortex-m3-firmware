/*
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
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
#include <openamp/rpmsg_internal.h>
#include <openamp/rpmsg_client.h>
#include <libmetal/mutex.h>
#include <mod_mhuv2.h>
#include <mod_log.h>
#include <mod_eventhandler.h>

struct rpmsg_ctx {
    /* Log API pointer */
    const struct mod_log_api *log_api;
    const struct mod_mhu_driver_api *mhu2_api;
    const struct mod_eventhandler_api *eventhandler_api;
};
static struct rpmsg_ctx rpmsg_ctx;

static struct rpmsg_device *rpmesg_device;

struct rpmsg_endpoint* get_endpoint(uint32_t address)
{
    return rpmsg_get_endpoint(rpmesg_device,"arm-rpmsg", RPMSG_ADDR_ANY, address);
}

static int rpmsg_endpoint_cb(struct rpmsg_endpoint *ept, void *data, size_t len,
                 uint32_t src, void *priv)
{
    int status = fwk_module_bind(FWK_ID_MODULE(FWK_MODULE_IDX_EVENTHANDLER),
                     FWK_ID_API(FWK_MODULE_IDX_EVENTHANDLER, 0),&rpmsg_ctx.eventhandler_api);
    if (status != FWK_SUCCESS)
        return FWK_E_PANIC;

    rpmsg_ctx.eventhandler_api->handleRpmsgEvent(ept, data, len);
    return RPMSG_SUCCESS;
}

struct rpmsg_endpoint* endpoint_create(struct rpmsg_device *rdev, void *dest)
{

    struct rpmsg_endpoint *lept;
    uint32_t  dest_addr =  (uint32_t)dest;
    int status;
    lept = fwk_mm_calloc(1,sizeof(*lept));
    status = rpmsg_create_ept(lept, rdev, "arm-rpmsg",RPMSG_ADDR_ANY,
            dest_addr,rpmsg_endpoint_cb, NULL);
    if (status == RPMSG_SUCCESS)
        return lept;
    else
        return RPMSG_SUCCESS;
}

static int send_rpmsg(struct rpmsg_device *rdev,
                                   uint32_t src, uint32_t dst,
                                   const void *data, int size, int wait)
{
    uint32_t message;
    int status;
    fwk_id_t fwk_dst;

    status = fwk_module_bind(FWK_ID_MODULE(FWK_MODULE_IDX_MHUV2),
                FWK_ID_API(FWK_MODULE_IDX_MHUV2, 0),&rpmsg_ctx.mhu2_api);
    if (status != FWK_SUCCESS)
            return FWK_E_PANIC;

    fwk_dst = rpmsg_ctx.mhu2_api->lookup_channel(dst);
    message = *(uint32_t *)data;
    status = rpmsg_ctx.mhu2_api->send_message(fwk_dst, message);

    if(status == FWK_SUCCESS){
        return RPMSG_SUCCESS;
    } else {
        return status;
    }

}

struct rpmsg_device* init_rpmsg()
{
    struct rpmsg_device *rdev;
    rdev = fwk_mm_calloc(1,sizeof(*rdev));
    metal_mutex_init(&rdev->lock);
    metal_list_init(&rdev->endpoints);
    rdev->ops.send_offchannel_raw = send_rpmsg;
    rdev->ns_bind_cb = NULL;
    rpmesg_device = rdev;
    return rdev;
}
