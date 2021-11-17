#ifndef __LOG_H__
#define __LOG_H__

#ifdef ANDROID
#include <android/log.h>

#define TAG "YOUR_TAG"

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

#endif  // ANDROID

#ifdef WIN32

#define LOGE(...) printf("[ERROR] " "" __VA_ARGS__); printf("\n")
#define LOGW(...) printf("[WARN] " "" __VA_ARGS__); printf("\n")
#define LOGI(...) printf("[INFO] " "" __VA_ARGS__); printf("\n")
#define LOGD(...) printf("[DEBUG] " "" __VA_ARGS__); printf("\n")

#endif

#endif  // __LOG_H__