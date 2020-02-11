//
// Created by redos on 2020-02-10.
//
#ifndef MYFFMPEGTEST_FGJNIUTILS_H
#define MYFFMPEGTEST_FGJNIUTILS_H

#include <jni.h>
#include <string>
#include "android/log.h"

#define TAG "FFMPEG_JNI"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,TAG ,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)

class FgJniUtils {
public:
    static std::string JStr2Str(JNIEnv *env, jstring jstr);
    static jstring Str2JStr(JNIEnv *env, std::string str);
};


#endif //MYFFMPEGTEST_FGJNIUTILS_H
