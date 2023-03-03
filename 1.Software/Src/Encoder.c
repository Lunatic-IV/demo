/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�1����ʼ���������ṹ�����
					2�����±�������ֵ
					3����ʱ������жϻص�����
**************************************************************************/
#include "Encoder.h"

__IO uint16_t TIM1_OverflowCount;//��ʱ��1�����������ֵ
__IO uint16_t TIM2_OverflowCount;//��ʱ��2�����������ֵ
__IO uint16_t TIM3_OverflowCount;//��ʱ��3�����������ֵ
__IO uint16_t TIM4_OverflowCount;//��ʱ��4�����������ֵ
__IO uint16_t TIM5_OverflowCount;//��ʱ��5�����������ֵ

/*-----------------------------------------------------------
�������ܣ���ʼ���������ṹ�����
��ڲ������ṹ���������Ӧ�Ķ�ʱ�����
�� �� ֵ��None
˵    ��: 
������TIMx������ָ���ṹ���Ӧ�Ķ�ʱ����ţ���ֵ��ΧΪ1~5����Ӧ��ʱ��TIM1~TIM5
 -----------------------------------------------------------*/
void Encoder_Struct_Init(Encoder_Struct *Encoder, uint8_t TIMx)
{
	Encoder->CaptureCount = 0;	//�������������ֵ
	Encoder->OverflowCount = 0;//�������������
	Encoder->Capture_D_Value = 0;//������ǰ��2�β�������Ĳ�ֵ
	Encoder->CNT_Last = 0;//������һ�ε�TIMx->CNT������ֵ
	Encoder->TIMx = TIMx;//��Ӧ�Ķ�ʱ�����
	
	switch(TIMx)//��0��Ӧ��ʱ�������������ֵ
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
�������ܣ����±�������ֵ
��ڲ������ṹ����������Ų���
�� �� ֵ��None
˵    ��: 
���øú�����Encoder->CaptureCount���롰Encoder->Capture_D_Value�����ø���

��������Ĳ����С�Signed������ֵΪ��1����-1��
����ֵΪ1ʱ����Encoder->CaptureCount���롰Encoder->Capture_D_Value���ĸ���ֵ���³���1
����ֵΪ-1ʱ����Encoder->CaptureCount���롰Encoder->Capture_D_Value���ĸ���ֵ���³���-1
 -----------------------------------------------------------*/
void Encoder_UpdataValue(Encoder_Struct *Encoder, int8_t Signed)
{
  uint16_t Encoder_TIM;
	
	switch(Encoder->TIMx)//��ȡ��Ӧ��ʱ���ļ���ֵ�������������ֵ
	{
		case 1:
		{
			Encoder_TIM = TIM1->CNT;//��ȡTIMx->CNT������ֵ
			Encoder->OverflowCount = TIM1_OverflowCount;//��ʱ��1�����������ֵ
		}break;
		
		case 2:
		{
			Encoder_TIM = TIM2->CNT;//��ȡTIMx->CNT������ֵ
			Encoder->OverflowCount = TIM2_OverflowCount;//��ʱ��1�����������ֵ
		}break;
		
		case 3:
		{
			Encoder_TIM = TIM3->CNT;//��ȡTIMx->CNT������ֵ
			Encoder->OverflowCount = TIM3_OverflowCount;//��ʱ��1�����������ֵ
		}break;
		
		case 4:
		{
			Encoder_TIM = TIM4->CNT;//��ȡTIMx->CNT������ֵ
			Encoder->OverflowCount = TIM4_OverflowCount;//��ʱ��1�����������ֵ
		}break;
		
		case 5:
		{
			Encoder_TIM = TIM5->CNT;//��ȡTIMx->CNT������ֵ
			Encoder->OverflowCount = TIM5_OverflowCount;//��ʱ��1�����������ֵ
		}break;
		
		default: return;//�˳�����
	}
	
	if(Encoder_TIM > Encoder->CNT_Last)
	{
		Encoder->Capture_D_Value = Encoder_TIM - Encoder->CNT_Last;//��ȡ������ǰ��2�β�������Ĳ�ֵ
		if(Encoder->Capture_D_Value > 10000) Encoder->Capture_D_Value -= 65536;//�ж��Ƿ��������
	}
	else
	{
		Encoder->Capture_D_Value = 0-(Encoder->CNT_Last - Encoder_TIM);//��ȡ������ǰ��2�β�������Ĳ�ֵ
		if(Encoder->Capture_D_Value > 10000) Encoder->Capture_D_Value += 65536;//�ж��Ƿ��������
	}
	Encoder->CNT_Last = Encoder_TIM;
	
	Encoder->Capture_D_Value = (Encoder->Capture_D_Value) * Signed;//��ȡ������ǰ��2�β�������Ĳ�ֵ
	Encoder->CaptureCount = (Encoder->OverflowCount*65536 + Encoder_TIM) * Signed;//��ȡ�������������ֵ
}

/*-----------------------------------------------------------
��������: ��������������жϺ���
�������: ��ʱ�����
�� �� ֵ: None
˵    ��: ���������������������жϺ���
 0xFFFF���䵽0x0000�����
 0x0000���䵽0xFFFF�����
 -----------------------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM1_OverflowCount--;       //���¼������
		}
		else
		{
			TIM1_OverflowCount++;  		 //���ϼ������
		}
	}
	
	else if(htim->Instance == TIM2)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM2_OverflowCount--;       //���¼������
		}
		else
		{
			TIM2_OverflowCount++;  		 //���ϼ������
		}
	}
	
	else if(htim->Instance == TIM3)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM3_OverflowCount--;       //���¼������
		}
		else
		{
			TIM3_OverflowCount++;  		 //���ϼ������
		}
	}
	
	else if(htim->Instance == TIM4)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM4_OverflowCount--;       //���¼������
		}
		else
		{
			TIM4_OverflowCount++;  		 //���ϼ������
		}
	}

	else if(htim->Instance == TIM5)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
		{
			TIM5_OverflowCount--;       //���¼������
		}
		else
		{
			TIM5_OverflowCount++;  		 //���ϼ������
		} 
	}
}
