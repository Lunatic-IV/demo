#ifndef __VELOCITYCONTROL_H
#define __VELOCITYCONTROL_H
#include "main.h"

#define VelocityControl_T 10//�ٶȱջ��������� ms
#define RPM_MAX         350.0f //������ת�� rpm
#define COUNTS_PER_REV  412 //��������תһȦ����������ֵ
#define WHEEL_DIAMETER  0.068f //����ֱ�� m
#define WHEEL_CIRCUMFERENCE 0.213628f//�����ܳ� m
#define LR_WHEELS_DISTANCE 0.203f//�����־� m
#define FR_WHEELS_DISTANCE 0.175f//ǰ���־� m

typedef struct
{
	__IO float M1_RPM;	 //M1�����ǰת�� rpm
	__IO float M2_RPM;	 //M2�����ǰת�� rpm
	__IO float M3_RPM;	 //M3�����ǰת�� rpm
	__IO float M4_RPM;	 //M4�����ǰת�� rpm
	__IO float M1_SetRPM;//M1���Ŀ��ת�� rpm
	__IO float M2_SetRPM;//M2���Ŀ��ת�� rpm
	__IO float M3_SetRPM;//M3���Ŀ��ת�� rpm
	__IO float M4_SetRPM;//M4���Ŀ��ת�� rpm
}VelControl_Struct; //���ת�ٿ��ƽṹ�����

void VelocityControl_4WD(VelControl_Struct *VelControl);//4WD�ٶȱջ����ƺ���
void VelocityControl(float VelControl);

#endif
