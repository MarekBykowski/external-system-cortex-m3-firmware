/*
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Description:
 *      exceptions.
 */


    .syntax unified

    .section .exception

    .global exceptions
exceptions:
    .word __STACK_END__
    .word exception_reset   /* Reset */
    .word exception_invalid /* NMI */
    .word exception_invalid /* HardFault */
    .word exception_invalid /* MemManage */
    .word exception_invalid /* Bus Fault */
    .word exception_invalid /* UsageFault */
    .word exception_invalid /* Reserved */
    .word exception_invalid /* Reserved */
    .word exception_invalid /* Reserved */
    .word exception_invalid /* Reserved */
    .word exception_invalid /* SVCall */
    .word exception_invalid /* DebugMonitor */
    .word exception_invalid /* Reserved */
    .word exception_invalid /* PendSV */
    .word exception_invalid /* SysTick */

    .section .text

    .global exception_invalid
    .thumb_func
    .func exception_invalid
exception_invalid:
    wfi
    b       exception_invalid
    .endfunc
