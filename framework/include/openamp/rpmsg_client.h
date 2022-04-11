/*
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _RPMSG_CLIENT_H_
#define _RPMSG_CLIENT_H_

extern struct rpmsg_endpoint* endpoint_create(struct rpmsg_device *rdev, void *priv);
extern struct rpmsg_device* init_rpmsg();
struct rpmsg_endpoint* get_endpoint(uint32_t address);

#endif
