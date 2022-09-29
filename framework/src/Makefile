#
# Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

BS_LIB_NAME := framework

BS_LIB_SOURCES += fwk_arch.c
BS_LIB_SOURCES += fwk_assert.c
BS_LIB_SOURCES += fwk_dlist.c
BS_LIB_SOURCES += fwk_id.c
BS_LIB_SOURCES += fwk_interrupt.c
BS_LIB_SOURCES += fwk_mm.c
BS_LIB_SOURCES += fwk_module.c
BS_LIB_SOURCES += fwk_slist.c
ifeq ($(BUILD_HAS_OPENAMP),yes)
    BS_LIB_SOURCES += openamp/rpmsg.c
    BS_LIB_SOURCES += openamp/rpmsg_client.c
endif
ifeq ($(BUILD_HAS_MULTITHREADING),yes)
    BS_LIB_SOURCES += fwk_multi_thread.c
else
    BS_LIB_SOURCES += fwk_thread.c
endif
ifeq ($(BUILD_HAS_NOTIFICATION),yes)
    BS_LIB_SOURCES += fwk_notification.c
endif

BS_LIB_INCLUDES += $(ARCH_DIR)/include
BS_LIB_INCLUDES += $(FWK_DIR)/include

BS_LIB_INCLUDES += $(FWK_DIR)/../module/mhuv2/include
BS_LIB_INCLUDES += $(FWK_DIR)/../module/log/include
ifeq ($(PRODUCT), corstone-700)
    BS_LIB_INCLUDES += $(FWK_DIR)/../product/corstone-700/include/
    BS_LIB_INCLUDES += $(FWK_DIR)/../product/corstone-700/module/eventhandler/include/
else ifeq ($(PRODUCT), corstone-1000)
    BS_LIB_INCLUDES += $(FWK_DIR)/../product/corstone-1000/include/
    BS_LIB_INCLUDES += $(FWK_DIR)/../product/corstone-1000/module/eventhandler/include/
endif

include $(BS_DIR)/lib.mk
