LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH))

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../Classes/*.cpp)
LOCAL_SRC_FILES := hellocpp/main.cpp../../../Classes/sqlite/sqlite3.c
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)


LOCAL_CPPFLAGS := -DSDKBOX_ENABLED
LOCAL_LDLIBS := -landroid -llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes
LOCAL_WHOLE_STATIC_LIBRARIES := PluginGoogleAnalytics sdkbox PluginChartboost

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module, ./sdkbox)
$(call import-module, ./plugingoogleanalytics)
$(call import-module, ./pluginchartboost)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
