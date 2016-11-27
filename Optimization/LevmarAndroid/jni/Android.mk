
LOCAL_PATH := $(call my-dir)
# reference : https://github.com/3deggi/levmar-ndk/blob/master/jni/Android.mk


export MAINDIR:= $(LOCAL_PATH)

#LAPACK, BLAS, F2C compilation
include $(CLEAR_VARS)
include $(MAINDIR)/Thirdparty/clapack/Android.mk
LOCAL_PATH := $(MAINDIR)
include $(CLEAR_VARS)
LOCAL_MODULE:= lapack
LOCAL_STATIC_LIBRARIES := tmglib clapack1 clapack2 clapack3 blas f2c
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS)
include $(BUILD_STATIC_LIBRARY)

#LEVMAR compilation
include $(CLEAR_VARS)
LMOBJ = $(MAINDIR)/Thirdparty/levmar/lm.c $(MAINDIR)/Thirdparty/levmar/Axb.c $(MAINDIR)/Thirdparty/levmar/misc.c $(MAINDIR)/Thirdparty/levmar/lmlec.c $(MAINDIR)/Thirdparty/levmar/lmbc.c $(MAINDIR)/Thirdparty/levmar/lmblec.c $(MAINDIR)/Thirdparty/levmar/lmbleic.c   
LOCAL_MODULE          := levmar
LOCAL_SRC_FILES := $(LMOBJ)  
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS)
include $(BUILD_STATIC_LIBRARY)


# Main compilation

include $(CLEAR_VARS)

#########
#include $(CLEAR_VARS)
$(info ================================================)
$(info $(LOCAL_PATH))

ThirdParty_PATH := $(LOCAL_PATH)/Thirdparty
LOCAL_C_INCLUDES :=    $(LOCAL_PATH)/Thirdparty


LOCAL_MODULE := levmarjni

LOCAL_SRC_FILES := levmarjni.cpp
LOCAL_SRC_FILES += Test.cpp

#LOCAL_STATIC_LIBRARIES  += lapack
LOCAL_STATIC_LIBRARIES  = levmar lapack



LOCAL_LDFLAGS := -llog


include $(BUILD_SHARED_LIBRARY)



