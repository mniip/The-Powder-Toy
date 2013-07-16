LOCAL_PATH := $(call my-dir)

###########################
#
# SDL shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := lua

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/*.c) \
	)

LOCAL_CFLAGS += -DLUA_USE_POSIX -DLUA_USE_DLOPEN
LOCAL_LDLIBS := -ldl

include $(BUILD_SHARED_LIBRARY)
