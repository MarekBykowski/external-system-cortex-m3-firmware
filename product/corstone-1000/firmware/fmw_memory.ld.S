/*
 *
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Description:
 *     Flash firmware memory layout for the linker script.
 */

#ifndef FMW_MEMORY_LD_S
#define FMW_MEMORY_LD_S

#include <escm3_system_mmap.h>

#define FIRMWARE_MEM_MODE FWK_MEM_MODE_DUAL_REGION_RELOCATION

/*
 * Flash memory
 */
#define FIRMWARE_MEM0_SIZE  FLASH_SIZE
#define FIRMWARE_MEM0_BASE  FLASH_START

/*
 * RAM memory
 */
#define FIRMWARE_MEM1_SIZE  SRAM_SIZE
#define FIRMWARE_MEM1_BASE  SRAM_START

#define FIRMWARE_STACK_SIZE (2 * 1024)

#endif /* FMW_MEMORY_LD_S */
