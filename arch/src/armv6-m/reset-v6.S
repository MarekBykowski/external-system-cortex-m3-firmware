/*
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Description:
 *      reset vector.
 */

    .syntax unified

    .text

    .global exception_reset
    .thumb_func
    .func exception_reset
exception_reset:
    bl      start
    .pool
    .endfunc
