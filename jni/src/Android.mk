LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/$(SDL_PATH)/src \
	$(LOCAL_PATH)/$(SDL_PATH)/src/core/android

# Add your application source files here...
LOCAL_SRC_FILES := native.cpp

LOCAL_SHARED_LIBRARIES := SDL2 TPT

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
