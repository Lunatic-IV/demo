/**************************************************************************
文件版本：神炽焰 V1.0
文件功能：1、初始化编码器结构体参数
					2、更新编码器数值
					3、定时器溢出中断回调函数
**************************************************************************/
#include "Encoder.h"

__IO uint16_t TIM1_OverflowCount;//定时器1溢出次数计数值
__IO uint16_t TIM2_OverflowCount;//定时器2溢出次数计数值
__IO uint16_t TIM3_OverflowCount;//定时器3溢出次数计数值
__IO uint16_t TIM4_OverflowCount;//定时器4溢出次数计数值
__IO uint16_t TIM5_OverflowCount;//定时器5溢出次数计数值

/*-----------------------------------------------------------
函数功能：初始化编码器结构体参数
入口参数：结构体参数，对应的定时器序号
返 回 值：None
说    明: 
参数“TIMx”用于指定结构体对应的定时器序号，数值范围为1~5，对应定时器TIM1~TIM5
 -----------------------------------------------------------*/
void Encoder_Struct_Init(Encoder_Struct *Encoder, uint8_t TIMx)
{
	Encoder->CaptureCount = 0;	//编码器捕获计数值
	Encoder->OverflowCount = 0;//编码器溢出次数
	Encoder->Capture_D_Value = 0;//编码器前后2次捕获计数的差值
	Encoder->CNT_Last = 0;//缓存上一次的TIMx->CNT计数器值
	Encoder->TIMx = TIMx;//对应的定时器序号
	
	switch(TIMx)//清0对应定时器溢出次数计数值
	{
		case 1: TIM1_OverflowCount=0;break;
		case 2: TIM2_OverflowCount=0;break;
		case 3: TIM3_OverflowCount=0;break;
		case 4: TIM4_OverflowCount=0;break;
		case 5: TIM5_OverflowCount=0;break;
		default:break;
	}
}

/*-----------------------------------------------------------
函数功能：更新编码器数值
入口参数：结构体参数，符号参数
返 回 值：None
说    明: 
调用该函数后“Encoder->CaptureCount”与“Encoder->Capture_D_Value”会获得更新

函数传入的参数中“Signed”的数值为“1”或“-1”
该数值为1时，“Encoder->CaptureCount”与“Encoder->Capture_D_Value”的更新值重新乘以1
该数值为-1时，“Encoder->CaptureCount”与“Encoder->Capture_D_Value”的更新值重新乘以-1
 -----------------------------------------------------------*/
void Encoder_UpdataValue(Encoder_Struct *Encoder, int8_t Signed)
{
  uint16_t Encoder_TIM;
	
	switch(Encoder->TIMx)//获取对应定时器的计数值与溢出次数计数值
	{
		case 1:
		{
			Encoder_TIM = TIM1->CNT;//读取TIMx->CNT计数器值
			Encoder->OverflowCount = TIM1_OverflowCount;//定时器1溢出次数计数值
		}break;
		
		case 2:
		{
			Encoder_TIM = TIM2->CNT;//读取TIMx->CNT计数器值
			Encoder->OverflowCount = TIM2_OverflowCount;//定时器1溢出次数计数值
		}break;
		
		case 3:
		{
			Encoder_TIM = TIM3->CNT;//读取TIMx->CNT计数器值
			Encoder->OverflowCount = TIM3_OverflowCount;//定时器1溢出次数计数值
		}break;
		
		case 4:
		{
			Encoder_TIM = TIM4->CNT;//读取TIMx->CNT计数器值
			Encoder->OverflowCount = TIM4_OverflowCount;//定时器1溢出次数计数值
		}break;
		
		case 5:
		{
			Encoder_TIM = TIM5->CNT;//读取TIMx->CNT计数器值
			Encoder->OverflowCount = TIM5_OverflowCount;//定时器1溢出次数计数值
		}break;
		
		default: return;//退出函数
	}
	
	if(Encoder_TIM > Encoder->CNT_Last)
	{
		Encoder->Capture_D_Value = Encoder_TIM - Encoder->CNT_Last;//获取编码器前后2次捕获计数的差值
		if(Encoder->Capture_D_Value > 10000) Encoder->Capture_D_Value -= 65536;//判断是否溢出跳变
	}
	else
	{
		Encoder->Capture_D_Value = 0-(Encoder->CNT_Last - Encoder_TIM);//获取编码器前后2次捕获计数的差值
		if(Encoder->Capture_D_Value > 10000) Encoder->Capture_D_Value += 65536;//判断是否溢出跳变
	}
	Encoder->CNT_Last = Encoder_TIM;
	
	Encoder->Capture_D_Value = (Encoder->Capture_D_Value) * Signed;//获取编码器前后2次捕获计数的差值
	Encoder->CaptureCount = (Encoder->OverflowCount*65536 + Encoder_TIM) * Signed;//获取编码器捕获计数值
}

/*-----------------------------------------------------------
函数功能: 编码器计数溢出中断函数
输入参数: 定时器句柄
返 回 值: None
说    明: 编码器计数溢出后会进入该中断函数
 0xFFFF跳变到0x0000，溢出
 0x0000跳变到0xFFFF，溢出
 -----------------------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM1_OverflowCount--;       //向下计数溢出
		}
		else
		{
			TIM1_OverflowCount++;  		 //向上计数溢出
		}
	}
	
	else if(htim->Instance == TIM2)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM2_OverflowCount--;       //向下计数溢出
		}
		else
		{
			TIM2_OverflowCount++;  		 //向上计数溢出
		}
	}
	
	else if(htim->Instance == TIM3)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM3_OverflowCount--;       //向下计数溢出
		}
		else
		{
			TIM3_OverflowCount++;  		 //向上计数溢出
		}
	}
	
	else if(htim->Instance == TIM4)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM4_OverflowCount--;       //向下计数溢出
		}
		else
		{
			TIM4_OverflowCount++;  		 //向上计数溢出
		}
	}

	else if(htim->Instance == TIM5)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM5_OverflowCount--;       //向下计数溢出
		}
		else
		{
			TIM5_OverflowCount++;  		 //向上计数溢出
		} 
	}
}
