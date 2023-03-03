#ifndef __SHAREWARE_H
#define __SHAREWARE_H
#include "main.h"
#include <stdarg.h>
#include <math.h>

#include "uart.h"
#include "tim2.h"
#include "tim3.h"
#include "tim4.h"
#include "tim5.h"
#include "tim8.h"
#include "delayus.h"
#include "MotorControl.h"

#include "Encoder.h"
#include "pid.h"
#include "VelocityControl.h"

#include "mpu6050.h"  
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "sys.h"
#include "can.h"



#ifdef __cplusplus
 extern "C" {
#endif

#define Constrain(AMT, MIN, MAX) ((AMT) < (MIN)? (MIN):( (AMT) > (MAX)?(MAX):(AMT) ))//约束函数


extern IncPID_Struct PID_M1;//创建M1电机PID结构体参数
extern IncPID_Struct PID_M2;//创建M2电机PID结构体参数
extern IncPID_Struct PID_M3;//创建M3电机PID结构体参数
extern IncPID_Struct PID_M4;//创建M4电机PID结构体参数

extern Encoder_Struct Encoder_M1;//创建M1编码器结构体参数
extern Encoder_Struct Encoder_M2;//创建M2编码器结构体参数
extern Encoder_Struct Encoder_M3;//创建M3编码器结构体参数
extern Encoder_Struct Encoder_M4;//创建M4编码器结构体参数

extern VelControl_Struct VelControl;//创建电机转速控制结构体参数





#ifdef __cplusplus
}
#endif

#endif
