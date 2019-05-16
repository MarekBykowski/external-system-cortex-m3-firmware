#
# Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

include $(BS_DIR)/cpu.mk

BS_LIB_NAME = arch

BS_LIB_SOURCES_armv6-m += armv6-m/exception.S
BS_LIB_SOURCES_armv6-m += armv6-m/reset-v6.S
BS_LIB_SOURCES_armv6-m += armv6-m/armv6-crt0.S
BS_LIB_SOURCES_armv6-m += armv6-m/arm_nvic.c
BS_LIB_SOURCES_armv6-m += arm_main.c
BS_LIB_SOURCES_armv6-m += arm_mm.c

BS_LIB_INCLUDES_armv6-m += $(TOP_DIR)/cmsis/CMSIS/Core/Include/

BS_LIB_SOURCES_armv7-m += armv7-m/exception.S
BS_LIB_SOURCES_armv7-m += armv7-m/reset-v7.S
BS_LIB_SOURCES_armv7-m += armv7-m/armv7-crt0.S
BS_LIB_SOURCES_armv7-m += armv7-m/arm_nvic.c
BS_LIB_SOURCES_armv7-m += arm_main.c
BS_LIB_SOURCES_armv7-m += arm_mm.c

BS_LIB_INCLUDES_armv7-m += $(TOP_DIR)/cmsis/CMSIS/Core/Include/

BS_LIB_INCLUDES += $(ARCH_DIR)/include
BS_LIB_INCLUDES += $(FWK_DIR)/include

#
# Select arch-specific sources and includes
#
BS_LIB_SOURCES += $(BS_LIB_SOURCES_$(BS_ARCH_CPU))
BS_LIB_SOURCES += $(BS_LIB_SOURCES_$(BS_ARCH_ARCH))
BS_LIB_INCLUDES += $(BS_LIB_INCLUDES_$(BS_ARCH_CPU))
BS_LIB_INCLUDES += $(BS_LIB_INCLUDES_$(BS_ARCH_ARCH))

include $(BS_DIR)/lib.mk
