LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
$(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
$(LOCAL_PATH)/../../../Classes/Boom.cpp \
$(LOCAL_PATH)/../../../Classes/Enemy.cpp \
$(LOCAL_PATH)/../../../Classes/EnemyFast.cpp \
$(LOCAL_PATH)/../../../Classes/EnemySmart.cpp \
$(LOCAL_PATH)/../../../Classes/EnemyThroughwall.cpp \
$(LOCAL_PATH)/../../../Classes/Fire.cpp \
$(LOCAL_PATH)/../../../Classes/GameScene.cpp \
$(LOCAL_PATH)/../../../Classes/Joystick.cpp \
$(LOCAL_PATH)/../../../Classes/Level.cpp \
$(LOCAL_PATH)/../../../Classes/MainMenu.cpp \
$(LOCAL_PATH)/../../../Classes/MyAnimate.cpp \
$(LOCAL_PATH)/../../../Classes/MyPoint.cpp \
$(LOCAL_PATH)/../../../Classes/PointList.cpp \
$(LOCAL_PATH)/../../../Classes/SoundGame.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
