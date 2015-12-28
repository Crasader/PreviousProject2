LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

FILE_LIST := hellocpp/main.cpp  
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)  
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%) 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
						$(LOCAL_PATH)/../../Classes/bullet \
								$(LOCAL_PATH)/../../Classes/core \
								$(LOCAL_PATH)/../../Classes/data \
								$(LOCAL_PATH)/../../Classes/fish \
								$(LOCAL_PATH)/../../Classes/level \
								$(LOCAL_PATH)/../../Classes/lobby \
								$(LOCAL_PATH)/../../Classes/net \
								$(LOCAL_PATH)/../../Classes/pause \
								$(LOCAL_PATH)/../../Classes/result \
							    $(LOCAL_PATH)/../../Classes/turret \
							    $(LOCAL_PATH)/../../Classes/utill 
																


LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
