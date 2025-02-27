#
# Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

include $(BS_DIR)/defs.mk

BS_ARCH_CPU := $(BS_FIRMWARE_CPU)

# Supported ARMv6-M CPUs
ARMV6M_CPU := cortex-m0plus

# Supported ARMv7-M CPUs
ARMV7M_CPUS := cortex-m3 cortex-m7

ifneq ($(findstring $(BS_FIRMWARE_CPU),$(ARMV6M_CPU)),)
    BS_ARCH_ARCH := armv6-m
    BS_ARCH_ISA := thumb
    $(call add_once,LDFLAGS_GCC,--specs=nano.specs)


else ifneq ($(findstring $(BS_FIRMWARE_CPU),$(ARMV7M_CPUS)),)
    BS_ARCH_ARCH := armv7-m
    BS_ARCH_ISA := thumb
    $(call add_once,LDFLAGS_GCC,--specs=nano.specs)

else ifeq ($(BS_FIRMWARE_CPU),host)
    BS_ARCH_ARCH := host

else
    $(erro "$(BS_FIRMWARE_CPU) is not a supported CPU. Aborting...")
endif

