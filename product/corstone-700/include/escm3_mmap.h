/*
 *
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef ESCM3_MMAP_H
#define ESCM3_MMAP_H

#include <stdint.h>
#include <escm3_system_mmap.h>

/* ===========================================================================*/
/* =============      Processor and Core Peripheral Section     ============= */
/* ========================================================================== */

/* ========================================================================== */
/* ================          Peripheral memory map             ============== */
/* ========================================================================== */
#define ES_PL011_UART_BASE    (0x4000F000ul)

/* ============================== MHU Devices ================================*/
#define MHU0_H_ES_BASE 0x40100000
#define MHU0_ES_H_BASE 0x40110000

#define MHU1_H_ES_BASE 0x40120000
#define MHU1_ES_H_BASE 0x40130000

#define MHU0_SE_ES_BASE 0x40140000
#define MHU0_ES_SE_BASE 0x40150000

#define MHU1_SE_ES_BASE 0x40160000
#define MHU1_ES_SE_BASE 0x40170000

enum se_mhu_device_idx {
    ES_H_MHU0_DEVICE_IDX,
    ES_H_MHU1_DEVICE_IDX,
    ES_SE_MHU0_DEVICE_IDX,
    ES_SE_MHU1_DEVICE_IDX,
    ES_MHU_DEVICE_IDX_COUNT,
};

#endif /* ESCM3_MMAP_H */
