/*
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef MOD_EVENTHANDLER_H
#define MOD_EVENTHANDLER_H

#include <openamp/rpmsg_internal.h>
#include <stddef.h>

struct mod_eventhandler_api {
    int (*handleRpmsgEvent)(struct rpmsg_endpoint *ept, void *data, size_t len);
};

#endif /* MOD_eventhandler_H */