/*
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#include <fwk_element.h>
#include <fwk_id.h>
#include <fwk_module.h>
#include <mod_mhuv2.h>
#include <escm3_irq.h>
#include <escm3_mmap.h>

static const struct fwk_element mhu_element_table[] = {
    [ES_H_MHU0_DEVICE_IDX] = {
        .name = "MHU0_H",
        .sub_element_count = 1,
        .data = &((struct mod_mhu2_channel_config) {
            .irq = HESMHU0_Combined_IRQn,
            .recv = MHU0_H_ES_BASE,
            .send = MHU0_ES_H_BASE,
            .channel = 0,
        })
    },

    [ES_H_MHU1_DEVICE_IDX] = {
        .name = "MHU1_H",
        .sub_element_count = 1,
        .data = &((struct mod_mhu2_channel_config) {
            .irq = HESMHU1_Combined_IRQn,
            .recv = MHU1_H_ES_BASE,
            .send = MHU1_ES_H_BASE,
            .channel = 0,
        })
    },

    [ES_SE_MHU0_DEVICE_IDX] = {
        .name = "MHU0_SE",
        .sub_element_count = 1,
        .data = &((struct mod_mhu2_channel_config) {
            .irq = SEESMHU0_Combined_IRQn,
            .recv = MHU0_SE_ES_BASE,
            .send = MHU0_ES_SE_BASE,
            .channel = 0,
        })
    },

    [ES_SE_MHU1_DEVICE_IDX] = {
        .name = "MHU1_SE",
        .sub_element_count = 1,
        .data = &((struct mod_mhu2_channel_config) {
            .irq = SEESMHU1_Combined_IRQn,
            .recv = MHU1_SE_ES_BASE,
            .send = MHU1_ES_SE_BASE,
            .channel = 0,
        })
    },

    [ES_MHU_DEVICE_IDX_COUNT] = {},
};

static const struct fwk_element *mhu_get_element_table(fwk_id_t module_id)
{
    return mhu_element_table;
}

struct fwk_module_config config_mhuv2 = {
    .get_element_table = mhu_get_element_table,
};
