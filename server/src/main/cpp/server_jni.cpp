/************************************************************
* Copyright 2023 PICO. All rights reserved
*
* NOTICE: All information contained herein is, and remains the property of PICO.
* The intellectual and technical concepts contained herein are proprietary to PICO
* and may be covered by patents, patents in process, and are protected by trade
* secret or copyright law. Dissemination of this information or reproduction of
* this material is strictly forbidden unless prior written permission is obtained
* from PICO.
*
* Created by xuhengjin on 2023/12/7.
* Brief:
*************************************************************/
#include "log_util.h"
#include <jni.h>
#include "server_jni.h"
JavaVM *globalJVM = nullptr;
extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnLoad");
    (void) reserved;
    globalJVM = vm;
    return JNI_VERSION_1_6;
}

bool open_hook(bool flag);
extern "C" JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnUnLoad");
    open_hook(false);
    globalJVM->DetachCurrentThread();
    globalJVM = nullptr;
}
