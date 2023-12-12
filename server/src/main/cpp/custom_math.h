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
* Created by xuhengjin on 2023/12/12.
* Brief:
*************************************************************/

#ifndef SCRCPY_SCREEN_CASTER_SERVER_SRC_MAIN_CPP_CUSTOM_MATH_H_
#define SCRCPY_SCREEN_CASTER_SERVER_SRC_MAIN_CPP_CUSTOM_MATH_H_

struct Vector3{
       float x, y, z;
       void reset(){
           x = y = z = 0.0f;
       }
};
#endif //SCRCPY_SCREEN_CASTER_SERVER_SRC_MAIN_CPP_CUSTOM_MATH_H_
