LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := TPT

LOCAL_C_INCLUDES := \
	$(wildcard $(LOCAL_PATH)/) \
	$(wildcard $(LOCAL_PATH)/data) \
	$(wildcard $(LOCAL_PATH)/generated) \
	$(wildcard $(LOCAL_PATH)/src) \
	$(wildcard $(LOCAL_PATH)/src/bson) \
	$(wildcard $(LOCAL_PATH)/src/cajun) \
	$(wildcard $(LOCAL_PATH)/src/cat) \
	$(wildcard $(LOCAL_PATH)/src/client) \
	$(wildcard $(LOCAL_PATH)/src/client/requestbroker) \
	$(wildcard $(LOCAL_PATH)/src/debug) \
	$(wildcard $(LOCAL_PATH)/src/graphics) \
	$(wildcard $(LOCAL_PATH)/src/gui) \
	$(wildcard $(LOCAL_PATH)/src/gui/colourpicker) \
	$(wildcard $(LOCAL_PATH)/src/gui/console) \
	$(wildcard $(LOCAL_PATH)/src/gui/dialogues) \
	$(wildcard $(LOCAL_PATH)/src/gui/elementsearch) \
	$(wildcard $(LOCAL_PATH)/src/gui/filebrowser) \
	$(wildcard $(LOCAL_PATH)/src/gui/game) \
	$(wildcard $(LOCAL_PATH)/src/gui/interface) \
	$(wildcard $(LOCAL_PATH)/src/gui/localbrowser) \
	$(wildcard $(LOCAL_PATH)/src/gui/login) \
	$(wildcard $(LOCAL_PATH)/src/gui/options) \
	$(wildcard $(LOCAL_PATH)/src/gui/preview) \
	$(wildcard $(LOCAL_PATH)/src/gui/profile) \
	$(wildcard $(LOCAL_PATH)/src/gui/render) \
	$(wildcard $(LOCAL_PATH)/src/gui/save) \
	$(wildcard $(LOCAL_PATH)/src/gui/search) \
	$(wildcard $(LOCAL_PATH)/src/gui/tags) \
	$(wildcard $(LOCAL_PATH)/src/gui/update) \
	$(wildcard $(LOCAL_PATH)/src/pim) \
	$(wildcard $(LOCAL_PATH)/src/powdertoyjava) \
	$(wildcard $(LOCAL_PATH)/src/resampler) \
	$(wildcard $(LOCAL_PATH)/src/simulation) \
	$(wildcard $(LOCAL_PATH)/src/simulation/elements) \
	$(wildcard $(LOCAL_PATH)/src/simulation/tools) \
	$(wildcard $(LOCAL_PATH)/src/socket) \
	$(wildcard $(LOCAL_PATH)/src/tasks) \
	$(wildcard $(LOCAL_PATH)/src/virtualmachine) \
	$(wildcard $(LOCAL_PATH)/tptlibrary) \
	$(wildcard $(LOCAL_PATH)/../SDL/include) \
	$(wildcard $(LOCAL_PATH)/../lua) \
	$(wildcard $(LOCAL_PATH)/../bzip2) \
	$(wildcard $(LOCAL_PATH)/../zlib) \

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/generated/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/socket/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/socket/*.c) \
	$(wildcard $(LOCAL_PATH)/src/tasks/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/cat/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/graphics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/simulation/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/simulation/tools/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/simulation/elements/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/cajun/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/debug/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/elementsearch/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/profile/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/colourpicker/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/search/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/preview/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/tags/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/options/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/localbrowser/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/game/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/update/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/console/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/save/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/filebrowser/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/dialogues/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/login/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/render/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/gui/interface/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/client/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/client/requestbroker/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/resampler/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/bson/*.cpp) \
	)

LOCAL_CPPFLAGS += -DUSE_SDL -DLUA_CONSOLE -DSTABLE -DANDROID -fexceptions
LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES := SDL2 lua bzip2 zlib

include $(BUILD_SHARED_LIBRARY)
