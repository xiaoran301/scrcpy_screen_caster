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

#include "quater.h"
// 欧拉角转换为四元数函数
Quaternion eulerToQuaternion(double roll, double pitch, double yaw) {
    Quaternion q;
    
    // 将角度转换为弧度
    roll = roll * M_PI / 180.0;
    pitch = pitch * M_PI / 180.0;
    yaw = yaw * M_PI / 180.0;
    
    // 计算四元数的各个分量
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    
    q.w = cy * cr * cp + sy * sr * sp;
    q.x = cy * sr * cp - sy * cr * sp;
    q.y = cy * cr * sp + sy * sr * cp;
    q.z = sy * cr * cp - cy * sr * sp;
    
    return q;
}
