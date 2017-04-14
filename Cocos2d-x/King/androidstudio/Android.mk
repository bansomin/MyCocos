LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
				   ../../../Classes/Helper/Sqlite3/sqlite3.c \
				   ../../../Classes/Helper/CSVParser/CSVParser.cpp \
				   ../../../Classes/Model/Notice.cpp \
				   ../../../Classes/Model/BuildingSprite.cpp \
				   ../../../Classes/Model/Robots.cpp \
				   ../../../Classes/UI/DialogScene/NewBuildDialog.cpp \
				   ../../../Classes/UI/HelloScene/HelloWorldScene.cpp \
                   ../../../Classes/UI/HomeScene/HomeScene.cpp \
                   ../../../Classes/UI/HomeScene/HomeHubLayer.cpp \
                   ../../../Classes/UI/HomeScene/HomeMapLayer.cpp \
                   ../../../Classes/UI/HomeScene/HomeOptionLayer.cpp \
                   ../../../Classes/UI/WorldScene/WorldScene.cpp \
                   ../../../Classes/UI/WorldScene/WorldHubLayer.cpp \
                   ../../../Classes/Utils/DataManager.cpp \
				   ../../../Classes/Utils/DBManager.cpp \
				   ../../../Classes/Utils/GlobalManager.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
