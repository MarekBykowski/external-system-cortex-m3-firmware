/*
 *
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef ESCM3_IRQ_H
#define ESCM3_IRQ_H

#include <fwk_interrupt.h>

typedef enum IRQn {
    /* -------------------  Cortex-M3 Processor Exceptions Numbers  ------------------- */
    NonMaskableInt_IRQn           = -14,        /*  2 Non Maskable Interrupt          */
    HardFault_IRQn                = -13,        /*  3 HardFault Interrupt             */
    MemoryManagement_IRQn         = -12,        /*  4 Memory Management Interrupt     */
    BusFault_IRQn                 = -11,        /*  5 Bus Fault Interrupt             */
    UsageFault_IRQn               = -10,        /*  6 Usage Fault Interrupt           */
    SVCall_IRQn                   =  -5,        /* 11 SV Call Interrupt               */
    DebugMonitor_IRQn             =  -4,        /* 12 Debug Monitor Interrupt         */
    PendSV_IRQn                   =  -2,        /* 14 Pend SV Interrupt               */
    SysTick_IRQn                  =  -1,        /* 15 System Tick Interrupt           */

    /*-------------------  CMSDK Specific Interrupt Numbers ----------------------------*/
    TIMER0_IRQn                   = 0,          /* TIMER 0 Interrupt                    */
    TIMER1_IRQn                   = 1,          /* TIMER 1 Interrupt                    */
    HESMHU0_Combined_IRQn         = 2,          /* Host to External System MHU0 Combined Interrupt */
    ESHMHU0_Combined_IRQn         = 3,          /* External System to Host MHU0 Combined Interrupt */
    HESMHU1_Combined_IRQn         = 4,          /* Host to External System MHU1 Combined Interrupt */
    ESHMHU1_Combined_IRQn         = 5,          /* External System to Host MHU1 Combined Interrupt */
    SEESMHU0_Combined_IRQn        = 6,          /* Boot processor to External System MHU0 Combined Interrupt */
    ESSEMHU0_Combined_IRQn        = 7,          /* External System to Boot processor MHU0 Combined Interrupt */
    SEESMHU1_Combined_IRQn        = 8,          /* Boot processor to External System MHU1 Combined Interrupt */
    ESSEMHU1_Combined_IRQn        = 9,          /* External System to Boot processor MHU1 Combined Interrupt */
    UART0_Tx_IRQn                 = 10,         /* UART 0 TX Interrupt                  */
    UART0_Rx_IRQn                 = 11,         /* UART 0 RX Interrupt                  */
    UART0_RxTimeout_IRQn          = 12,         /* UART 0 RX Timeout Interrupt          */
} IRQn_Type;


#endif /* ESCM3_IRQ_H */
