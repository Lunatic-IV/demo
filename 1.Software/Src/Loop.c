#include "Loop.h"

extern __IO uint16_t Loop_10msTime;//10ms��ѯʱ��

/*-----------------------------------------------------------
��������: �δ�ʱ���жϺ���
�������: None
�� �� ֵ: None
˵    ��: �δ�ʱ���ж�����Ϊ1ms��ÿ��1ms�ͻ����һ�θú���
 -----------------------------------------------------------*/
void HAL_SYSTICK_Callback()//ϵͳ�δ�ʱ��1ms�жϺ���
{
	if(Loop_10msTime) Loop_10msTime--;//10ms��ѯʱ���Լ�

}