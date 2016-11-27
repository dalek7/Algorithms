#ifndef ANDROIDLOG_H
#define ANDROIDLOG_H

// For handling logging in NDK
// Seung-Chan Kim

#ifdef __ANDROID_API__
#include <jni.h>
#include <android/log.h>
#ifndef LOG_TAG
#define  LOG_TAG    "NDK_TEST"
#endif

#define  LOGUNK(...)  __android_log_print(ANDROID_LOG_UNKNOWN,LOG_TAG,__VA_ARGS__)
#define  LOGDEF(...)  __android_log_print(ANDROID_LOG_DEFAULT,LOG_TAG,__VA_ARGS__)
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGF(...)  __android_log_print(ANDROID_FATAL_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGS(...)  __android_log_print(ANDROID_SILENT_ERROR,LOG_TAG,__VA_ARGS__)

//WIN32
#else
//#elif _POSIX_C_SOURCE >= 199309L

#define  LOGI(...) printf(__VA_ARGS__); printf("\n");
#define  LOGV(...) printf(__VA_ARGS__); printf("\n");
#define  LOGE(...) printf(__VA_ARGS__); printf("\n");


#endif //__ANDROID_API__
#endif
