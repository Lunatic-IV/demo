#ifndef __VELOCITYCONTROL_H
#define __VELOCITYCONTROL_H
#include "main.h"

#define VelocityControl_T 10//速度闭环控制周期 ms
#define RPM_MAX         350.0f //电机最大转速 rpm
#define COUNTS_PER_REV  412 //电机输出轴转一圈编码器计数值
#define WHEEL_DIAMETER  0.068f //轮子直径 m
#define WHEEL_CIRCUMFERENCE 0.213628f//轮子周长 m
#define LR_WHEELS_DISTANCE 0.203f//左右轮距 m
#define FR_WHEELS_DISTANCE 0.175f//前后轮距 m

typedef struct
{
	__IO float M1_RPM;	 //M1电机当前转速 rpm
	__IO float M2_RPM;	 //M2电机当前转速 rpm
	__IO float M3_RPM;	 //M3电机当前转速 rpm
	__IO float M4_RPM;	 //M4电机当前转速 rpm
	__IO float M1_SetRPM;//M1电机目标转速 rpm
	__IO float M2_SetRPM;//M2电机目标转速 rpm
	__IO float M3_SetRPM;//M3电机目标转速 rpm
	__IO float M4_SetRPM;//M4电机目标转速 rpm
}VelControl_Struct; //电机转速控制结构体参数

void VelocityControl_4WD(VelControl_Struct *VelControl);//4WD速度闭环控制函数
void VelocityControl(float VelControl);

#endif
