#
# Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

BS_FIRMWARE_CPU := cortex-m3
BS_FIRMWARE_HAS_MULTITHREADING := no
BS_FIRMWARE_HAS_NOTIFICATION := yes
BS_FIRMWARE_HAS_OPENAMP := yes

BS_FIRMWARE_MODULES := \
    pl011 \
    log \
    mhuv2

BS_FIRMWARE_SOURCES := \
    config_log.c \
    config_mhuv2.c

include $(BS_DIR)/firmware.mk
