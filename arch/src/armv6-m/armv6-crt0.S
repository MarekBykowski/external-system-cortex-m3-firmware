 /*
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Description:
 *      startup file.
 */

    .syntax unified

    .text

    .global start
    .thumb_func
    .func start
start:

/* Load .data, which is 4-byte aligned */
    ldr     r1, =__DATA_SIZE__
    cmp     r1, #0
    beq     6f
    ldr     r4, =4
    ldr     r0, =__DATA_LMA_START__
    ldr     r2, =__DATA_START__
    cmp     r0, r2
    beq     6f
5:
    ldr     r3, [r0]
    add     r0, r0, r4
    str     r3, [r2]
    add     r2, r2, r4
    subs    r1, r4
    bne     5b
6:
    /* Clear .bss, which is also 4-byte aligned */
    ldr     r1, =__BSS_SIZE__
    cmp     r1, #0
    beq     8f
    ldr     r0, =__BSS_START__
    ldr     r2, =0
7:
    str     r2, [r0]
    add     r0, r4
    subs    r1, r4
    bne     7b

8:
    dsb
    bl      arm_main

9:
    wfi
    b 9b
    .pool
    .endfunc
