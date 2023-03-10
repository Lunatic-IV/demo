#include "delayus.h"
/*---------------------------------------------us延时函数---------------------------------------------*/
//delayus(x)实际延迟(x+1)微妙
#define CPU_FREQUENCY_MHZ    72

static __IO uint32_t TimingDelay;

void delay_us(__IO uint32_t nTime)//us延时函数
{
    int old_val,new_val,val;

    if(nTime > 900)
    {
        for(old_val = 0; old_val < nTime/900; old_val++)
        {
            delay_us(900);
        }
        nTime = nTime%900;
    }

    old_val = SysTick->VAL;
    new_val = old_val - CPU_FREQUENCY_MHZ*nTime;
    if(new_val >= 0)
    {
        do
        {
            val = SysTick->VAL;
        }
        while((val < old_val)&&(val >= new_val));
    }
    else
    {
        new_val +=CPU_FREQUENCY_MHZ*1000;
        do
        {
            val = SysTick->VAL;
        }
        while((val <= old_val)||(val > new_val));

    }
}



//延时nms
//nms:要延时的ms数
void delay_ms(uint32_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) delay_us(1000);
}

