LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := TbuServer
LOCAL_SRC_FILES := libTbuServer.so 
include $(PREBUILT_SHARED_LIBRARY)

