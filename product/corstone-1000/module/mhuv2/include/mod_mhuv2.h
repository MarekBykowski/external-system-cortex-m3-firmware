/*
 *
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Description:
 *      Message Handling Unit (MHU) v2 Device Driver.
 */

#ifndef MOD_MHU2_H
#define MOD_MHU2_H

#include <stdint.h>
#include <fwk_macros.h>

#define CHANNEL_MAX 124

enum mod_mhu2_api_idx {
    MOD_MHU2_API_IDX_DRIVER,
    MOD_MHU2_API_IDX_COUNT,
};

struct mod_mhu2_channel_config {
    /*! IRQ number of the receive interrupt line */
    unsigned int irq;

    /*! Indicates whether interrupt is within NVIC or a collated IRQ */
    bool irq_is_collated;

    /*! Base address of the registers of the incoming MHU */
    uintptr_t recv;

    /*! Base address of the registers of the outgoing MHU */
    uintptr_t send;

    /*! Channel number */
    unsigned int channel;
};


struct mhu2_id_reg {
    FWK_R  uint32_t  PID4;
           uint8_t   RESERVED1[0x10 - 0x4];
    FWK_R  uint32_t  PID0;
    FWK_R  uint32_t  PID1;
    FWK_R  uint32_t  PID2;
    FWK_R  uint32_t  PID3;
    FWK_R  uint32_t  COMPID0;
    FWK_R  uint32_t  COMPID1;
    FWK_R  uint32_t  COMPID2;
    FWK_R  uint32_t  COMPID3;
};

struct mhu2_send_channel_reg {
    FWK_R  uint32_t  STAT;
           uint8_t   RESERVED0[0xC - 0x4];
    FWK_W  uint32_t  STAT_SET;
           uint8_t   RESERVED1[0x20 - 0x10];
};

struct mhu2_send_reg {
    struct mhu2_send_channel_reg channel[CHANNEL_MAX];
    FWK_R  uint32_t  MSG_NO_CAP;
    FWK_RW uint32_t  RESP_CFG;
    FWK_RW uint32_t  ACCESS_REQUEST;
    FWK_R  uint32_t  ACCESS_READY;
    FWK_R  uint32_t  INT_ACCESS_STAT;
    FWK_W  uint32_t  INT_ACCESS_CLR;
    FWK_W  uint32_t  INT_ACCESS_EN;
           uint8_t   RESERVED0[0xFD0 - 0xF9C];
    struct mhu2_id_reg id;
};

struct mhu2_recv_channel_reg {
    FWK_R  uint32_t  STAT;
    FWK_R  uint32_t  STAT_PEND;
    FWK_W  uint32_t  STAT_CLEAR;
           uint8_t   RESERVED0[0x10 - 0x0C];
    FWK_R  uint32_t  MASK;
    FWK_W  uint32_t  MASK_SET;
    FWK_W  uint32_t  MASK_CLEAR;
           uint8_t   RESERVED1[0x20 - 0x1C];
};

struct mhu2_recv_reg {
    struct mhu2_recv_channel_reg channel[CHANNEL_MAX];
    FWK_R  uint32_t  MSG_NO_CAP;
           uint8_t   RESERVED0[0xFD0 - 0xF84];
    struct mhu2_id_reg id;
};

struct mod_mhu_driver_api {
       int (*send_message) (fwk_id_t slot_id, uint32_t message);
       fwk_id_t (*lookup_channel) (uint32_t dst);
};

#endif /* MOD_MHU2_H */
