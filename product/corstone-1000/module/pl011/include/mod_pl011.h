/*
 *
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef MOD_PL011_H
#define MOD_PL011_H

#include <stdint.h>
#include <fwk_id.h>

/*!
 * \addtogroup GroupModules Modules
 * @{
 */

/*!
 * \defgroup GroupModulePl011 PL011 Driver
 *
 * \brief Arm PL011 device driver, fulfilling the Log module's driver API.
 *
 * \details This module implements a device driver for the Primecell® PL011
 *      UART.
 * @{
 */

#define UART_CLK_MHZ (1000UL * 1000UL)

/*!
 * \brief PL011 device configuration data.
 */
struct mod_pl011_device_config {
    /*! Base address of the device registers */
    uintptr_t reg_base;

    /*! Baud rate (bits per second) */
    unsigned int baud_rate_bps;

    /*! Reference clock (Hertz) */
    uint64_t clock_rate_hz;

    /*! Identifier of the clock that this device depends on */
    fwk_id_t clock_id;
};

/*!
 * @}
 */

/*!
 * @}
 */

#endif /* MOD_PL011_H */
