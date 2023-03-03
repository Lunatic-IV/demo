#ifndef __ENCODER_H
#define __ENCODER_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
typedef struct
{	
	__IO uint32_t CaptureCount;	//编码器捕获计数值
	__IO uint16_t OverflowCount ;//编码器溢出次数
	__IO int16_t  Capture_D_Value;//编码器前后2次捕获计数的差值
	__IO uint16_t CNT_Last;//缓存上一次的TIMx->CNT计数器值
	__IO uint8_t TIMx;//对应的定时器序号
}Encoder_Struct;//电机编码器结构体参数

extern __IO uint16_t TIM1_OverflowCount;//定时器1溢出次数计数值
extern __IO uint16_t TIM2_OverflowCount;//定时器2溢出次数计数值
extern __IO uint16_t TIM3_OverflowCount;//定时器3溢出次数计数值
extern __IO uint16_t TIM4_OverflowCount;//定时器4溢出次数计数值
extern __IO uint16_t TIM5_OverflowCount;//定时器5溢出次数计数值

void Encoder_Struct_Init(Encoder_Struct *Encoder, uint8_t TIMx);//初始化编码器结构体参数
void Encoder_UpdataValue(Encoder_Struct *Encoder, int8_t Signed);//更新编码器数值

#ifdef __cplusplus
}
#endif

#endif
