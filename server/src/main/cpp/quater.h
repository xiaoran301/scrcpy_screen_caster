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

#ifndef SCRCPY_SCREEN_CASTER_SERVER_SRC_MAIN_CPP_QUATER_H_
#define SCRCPY_SCREEN_CASTER_SERVER_SRC_MAIN_CPP_QUATER_H_

#include <jni.h>
#include <math.h>
#include <cmath>

// 定义四元数结构体
typedef struct {
    double w, x, y, z;
} Quaternion;

#define M_PI 3.14159265358979323846

// 欧拉角转换为四元数函数
Quaternion eulerToQuaternion(double roll, double pitch, double yaw);

#endif //SCRCPY_SCREEN_CASTER_SERVER_SRC_MAIN_CPP_QUATER_H_
