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

#define Constrain(AMT, MIN, MAX) ((AMT) < (MIN)? (MIN):( (AMT) > (MAX)?(MAX):(AMT) ))//Լ������


extern IncPID_Struct PID_M1;//����M1���PID�ṹ�����
extern IncPID_Struct PID_M2;//����M2���PID�ṹ�����
extern IncPID_Struct PID_M3;//����M3���PID�ṹ�����
extern IncPID_Struct PID_M4;//����M4���PID�ṹ�����

extern Encoder_Struct Encoder_M1;//����M1�������ṹ�����
extern Encoder_Struct Encoder_M2;//����M2�������ṹ�����
extern Encoder_Struct Encoder_M3;//����M3�������ṹ�����
extern Encoder_Struct Encoder_M4;//����M4�������ṹ�����

extern VelControl_Struct VelControl;//�������ת�ٿ��ƽṹ�����





#ifdef __cplusplus
}
#endif

#endif
