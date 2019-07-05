/*
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <assert.h>
#include <fwk_module_idx.h>
#include <fwk_module.h>
#include <mod_log.h>
#include <mod_eventhandler.h>
#include <escm3_mmap.h>
#include <limits.h>
#include <openamp/rpmsg.h>
#include <openamp/rpmsg_client.h>

const struct mod_log_api *log_api;

/* MHU Test command syntax
 bit 3 downto 0  : command
 bit 31 downto 4 : value
*/

#define BITMASK(x) ((unsigned)-1 >> ((sizeof(int) * CHAR_BIT) - x))
#define CMD_WIDTH 4
#define COMMAND(message) (message & BITMASK(CMD_WIDTH))
#define VALUE(message)  ((unsigned)message >> CMD_WIDTH)
#define ENCODE(command, value) ((command & BITMASK(CMD_WIDTH)) | ((value) << CMD_WIDTH))

enum Command {
    NONE,
    INC_RETURN,     // Increment the value and return the value to sender
    INC_ECHO_SE,    // increment, send to SE, make it increment and echo back
                    // to this ES
    NUM_COMMANDS,
};

static int handleRpmsgEvent(struct rpmsg_endpoint *ept, void *data, size_t len){
    log_api->log(MOD_LOG_GROUP_INFO,"Received '%x' ", *(int*)data);
    if (ept->dest_addr == MHU0_ES_H_BASE)
        log_api->log(MOD_LOG_GROUP_INFO,"From Host MHU0\n");
    else if (ept->dest_addr == MHU1_ES_H_BASE)
        log_api->log(MOD_LOG_GROUP_INFO,"From Host MHU1\n");
    else if (ept->dest_addr == MHU0_ES_SE_BASE)
        log_api->log(MOD_LOG_GROUP_INFO,"From SE MHU0\n");
    else if (ept->dest_addr == MHU1_ES_SE_BASE)
        log_api->log(MOD_LOG_GROUP_INFO,"From SE MHU1\n");
    else
        log_api->log(MOD_LOG_GROUP_INFO,"From unknown source\n");

    int message = *(int*)data;
    switch (COMMAND(message)) {
        case NONE:
            log_api->log(MOD_LOG_GROUP_INFO,
                "CMD: Do nothing...\r\n");
            break;
        case INC_RETURN: {
            log_api->log(MOD_LOG_GROUP_INFO,
                "CMD: Increment and return to sender...\r\n");
            const int command = ENCODE(NONE, VALUE(message) + 1);
            int status = rpmsg_send(ept, &command, sizeof(command));
            if(status != RPMSG_SUCCESS){
                log_api->log(MOD_LOG_GROUP_INFO,
                "EventHandler: Could not send message via rpmsg_send\r\n");
            }
            break;
        }
        case INC_ECHO_SE: {
            struct rpmsg_endpoint* se_ept;
            switch(ept->dest_addr) {
                case MHU0_ES_H_BASE:
                    se_ept = get_endpoint(MHU0_ES_SE_BASE);
                    break;
                case MHU1_ES_H_BASE:
                    se_ept = get_endpoint(MHU1_ES_SE_BASE);
                    break;
                default:
                    log_api->log(MOD_LOG_GROUP_INFO,
                    "ECHO SE command should be triggered from a host MHU\r\n");
                    return FWK_SUCCESS;
            }
            log_api->log(MOD_LOG_GROUP_INFO,
                "CMD: Increment and echo to SE...\r\n");
            const int command = ENCODE(INC_RETURN, VALUE(message) + 1);
            int status = rpmsg_send(se_ept, &command, sizeof(command));
            if(status != RPMSG_SUCCESS){
                log_api->log(MOD_LOG_GROUP_INFO,
                "EventHandler: Could not send message via rpmsg_send\r\n");
            }
            break;
        }
        default: {
            log_api->log(MOD_LOG_GROUP_INFO,
                "CMD: Unknwn command: %u\r\n", COMMAND(message));
            break;
        }
    }
    return FWK_SUCCESS;
}

static struct mod_eventhandler_api module_api = {
    .handleRpmsgEvent = handleRpmsgEvent,
};

static int eventhandler_process_bind_request(
    fwk_id_t requester_id,
    fwk_id_t id,
    fwk_id_t api_id,
    const void **api)
{
    *api = &module_api;
    return FWK_SUCCESS;
}

static int eventhandler_init(fwk_id_t id, unsigned int element_count,
    const void* data){
    return FWK_SUCCESS;
}

static int eventhandler_bind(fwk_id_t id, unsigned int round)
{
    int status;

    if ((round == 1)) {
        status = fwk_module_bind(FWK_ID_MODULE(FWK_MODULE_IDX_LOG),
                                     FWK_ID_API(FWK_MODULE_IDX_LOG, 0),
                                     &log_api);
        if (status != FWK_SUCCESS) {
            /* Unable to bind back to SMT channel */
            assert(false);
            return status;
        }

    }
    return FWK_SUCCESS;
}

const struct fwk_module module_eventhandler = {
    .name = "eventhandler",
    .type = FWK_MODULE_TYPE_DRIVER,
    .api_count = 1,
    .bind = eventhandler_bind,
    .init = eventhandler_init,
    .process_bind_request = eventhandler_process_bind_request,
};
