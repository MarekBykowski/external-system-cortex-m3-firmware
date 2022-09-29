/*
 *
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef ESCM3_SYSTEM_MMAP_H
#define ESCM3_SYSTEM_MMAP_H

/*Memory*/

#define FLASH_START  0x00000000
#define FLASH_SIZE   0x00040000 /* 256 KiB */


/* Data memory zones */
#define SRAM_START  0x20000000
#define SRAM_SIZE   0x00008000 /* 32 KiB */

#endif /* ESCM3_SYSTEM_MMAP_H */
