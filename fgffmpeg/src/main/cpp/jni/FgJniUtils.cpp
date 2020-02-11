//
// Created by redos on 2020-02-10.
//

#include "FgJniUtils.h"

std::string FgJniUtils::JStr2Str(JNIEnv *env, jstring jstr) {
    const char* pchStr = env->GetStringUTFChars(jstr, JNI_FALSE);
    std::string str = std::string(pchStr);
    env->ReleaseStringUTFChars(jstr, pchStr);

    return str;
}

jstring FgJniUtils::Str2JStr(JNIEnv *env, std::string str) {
    return env->NewStringUTF(str.c_str());
}
