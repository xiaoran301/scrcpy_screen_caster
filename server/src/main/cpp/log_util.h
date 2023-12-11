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
* Created by xuhengjin on 2023/12/6.
* Brief:
*************************************************************/

#ifndef SCRCPY_SCREEN_CASTER_SERVER_SRC_MAIN_CPP_LOG_UTIL_H_
#define SCRCPY_SCREEN_CASTER_SERVER_SRC_MAIN_CPP_LOG_UTIL_H_
#include <android/log.h>
#define LOG_TAG "scrcpy_server_pico"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif //SCRCPY_SCREEN_CASTER_SERVER_SRC_MAIN_CPP_LOG_UTIL_H_
