#include "Loop.h"

extern __IO uint16_t Loop_10msTime;//10ms轮询时间

/*-----------------------------------------------------------
函数功能: 滴答定时器中断函数
输入参数: None
返 回 值: None
说    明: 滴答定时器中断周期为1ms，每隔1ms就会进入一次该函数
 -----------------------------------------------------------*/
void HAL_SYSTICK_Callback()//系统滴答定时器1ms中断函数
{
	if(Loop_10msTime) Loop_10msTime--;//10ms轮询时间自减

}
