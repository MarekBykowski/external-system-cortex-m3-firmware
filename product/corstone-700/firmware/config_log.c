/*
 *
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#include <fwk_banner.h>
#include <fwk_macros.h>
#include <fwk_module.h>
#include <fwk_module_idx.h>
#include <system_clock.h>
#include <mod_log.h>
#include <mod_pl011.h>
#include <escm3_mmap.h>

/*
 * PL011 module
 */
static const struct fwk_element pl011_element_desc_table[] = {
    [0] = {
        .name = "uart",
        .data = &((struct mod_pl011_device_config) {
            .reg_base = ES_PL011_UART_BASE,
            .baud_rate_bps = 115200,
            .clock_rate_hz = SYSTEM_CLOCK,
            .clock_id = FWK_ID_NONE_INIT,
            }),
    },
    [1] = {},
};

static const struct fwk_element *get_pl011_table(fwk_id_t module_id)
{
    return pl011_element_desc_table;
}

struct fwk_module_config config_pl011 = {
    .get_element_table = get_pl011_table,
};

/*
 * Log module
 */
static const struct mod_log_config log_data = {
    .device_id = FWK_ID_ELEMENT(FWK_MODULE_IDX_PL011, 0),
    .api_id = FWK_ID_API(FWK_MODULE_IDX_PL011, 0),
    .log_groups = MOD_LOG_GROUP_ERROR |
                  MOD_LOG_GROUP_INFO |
                  MOD_LOG_GROUP_WARNING |
                  MOD_LOG_GROUP_DEBUG,
    .banner = FWK_BANNER_ES
              BUILD_VERSION_DESCRIBE_STRING "\n",
};

struct fwk_module_config config_log = {
    .data = &log_data,
};
