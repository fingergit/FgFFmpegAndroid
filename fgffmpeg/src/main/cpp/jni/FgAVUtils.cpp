#include <jni.h>
#include <string>
#include "FgJniUtils.h"
#include "CFgAVUtils.h"

extern "C"{
#include <libavcodec/jni.h>
#include <ffmpeg.h>
}

extern "C" JNIEXPORT jstring JNICALL Java_com_github_fgffmpeg_FgJNIAVUtils_getFileInfo
        (JNIEnv *env, jclass, jstring filePath) {
    std::string fileInfo = CFgAVUtils::getFileInfo(FgJniUtils::JStr2Str(env, filePath));
    return FgJniUtils::Str2JStr(env, fileInfo);
}

JNIEnv *g_env = NULL;
jobject g_callback;
jmethodID g_javaCallbackId;
jmethodID g_javaOnErrorId;
static void OnFFmpegProgress(int64_t taskId, int status, int64_t frames, int64_t totalFrames) {
    g_env->CallVoidMethod(g_callback, g_javaCallbackId,taskId,status,frames,totalFrames);
}

static void OnFFmpegError(int64_t taskId) {
    g_env->CallVoidMethod(g_callback, g_javaOnErrorId,taskId,taskId);
}

extern "C" JNIEXPORT jint JNICALL Java_com_github_fgffmpeg_FgJNIAVUtils_ffmpegMain
        (JNIEnv *env, jclass, jlong taskId, jobjectArray argv, jobject callback) {
    //set java vm
    JavaVM *jvm = NULL;
    env->GetJavaVM(&jvm);
    av_jni_set_java_vm(jvm, NULL);

    jint argc = env->GetArrayLength(argv);
    char *argCmd[argc] ;
    jstring buf[argc];

    for (int i = 0; i < argc; ++i) {
        buf[i] = static_cast<jstring>(env->GetObjectArrayElement(argv, i));
        char *string = const_cast<char *>(env->GetStringUTFChars(buf[i], JNI_FALSE));
        argCmd[i] = string;
        LOGD("argCmd=%s",argCmd[i]);
    }

    jclass javaClass = env->GetObjectClass(callback);
    jmethodID javaCallbackId = env->GetMethodID(javaClass, "OnProgress", "(JIJJ)V");
    g_javaOnErrorId = env->GetMethodID(javaClass, "OnError", "(JI)V");
    env->DeleteLocalRef(javaClass);

    g_env = env;
    g_callback = callback;
    g_javaCallbackId = javaCallbackId;
    int retCode = CFgAVUtils::ffmpegMain(argc, argCmd, OnFFmpegError, OnFFmpegProgress, taskId);
    LOGD("ffmpeg-invoke: retCode=%d",retCode);

    for (int i = 0; i < argc; ++i) {
        env->ReleaseStringUTFChars(buf[i], argCmd[i]);
    }

    return retCode;
}

extern "C" JNIEXPORT void JNICALL Java_com_github_fgffmpeg_FgJNIAVUtils_printCodecs
        (JNIEnv *, jclass) {
    CFgAVUtils::printCodecs();
}
