/**************************************************************************
文件版本：神炽焰 V1.0
**************************************************************************/
#include "main.h"
#include "ShareWare.h"


#define LED0 PCout(6)   	//LED0
#define CAR_ANGLE_SET 1//目标角度
#define CAR_ANGLE_SPEED_SET 0//目标角速度


void SystemClock_Config(void);       

__IO uint16_t Loop_10msTime=0;//10ms轮询时间



u8 t=0;
u8 key=0;
u8 GetData=1;
float pitch,roll,yaw;       //欧拉角
short pitch4,roll4,yaw4,pitc4;      //欧拉角
short aacx,aacy,aacz;       //加速度传感器原始数据
short gyrox,gyroy,gyroz;    //陀螺仪原始数据
short temp;                 //温度
float gyrox4,gyroy4,gyroz4; //陀螺仪原始数据


float g_fAccAngle;//加速度传感器经过解算得到的角度
float g_fGyroAngleSpeed;//陀螺仪角速度
float g_fCarAngle;//小车倾角
float dt = 0.005;//互补滤波器控制周期


short g_fCarAngle4;//小车倾角


float g_fLeftMotorOut,g_fRightMotorOut;
short g_fAngleControlOut;

float g_fAngle_P = 8.6; //角度环P参数
float g_fAngle_D = -1.0;  //角度环D参数

u8 CAR_ANGLE=4;



void AngleControl(void)     //角度环控制函数
{
    g_fAngleControlOut =  (CAR_ANGLE - g_fCarAngle) * g_fAngle_P + (CAR_ANGLE_SPEED_SET - g_fGyroAngleSpeed) * g_fAngle_D;//PD控制器
}


/****************************************************************************/
/**
 * Function Name: main
 * Description: none
 *
 * Param:   none
 * Return:  none
 * Author:  2020/12/30, Lunatic create this function
 ****************************************************************************/
int main(void)
{


    extern uint8_t TXmessage[8];

    HAL_Init();//初始化HAL库
    SystemClock_Config();//系统时钟配置
    MX_TIM8_Init();//TIM8-PWM初始化

	Motor1_GPIO_Init();//电机驱动1 IO初始化函数
    Motor2_GPIO_Init();//电机驱动2 IO初始化函数
    Motor3_GPIO_Init();//电机驱动3 IO初始化函数
    Motor4_GPIO_Init();//电机驱动4 IO初始化函数	
    
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    MX_CAN_Init();
    CAN_Config();

	
//	MX_TIM2_Init();//TIM2-编码器模式初始化
//	MX_TIM3_Init();//TIM3-编码器模式初始化
	MX_TIM4_Init();//TIM4-编码器模式初始化
	MX_TIM5_Init();//TIM5-编码器模式初始化
	Encoder_Struct_Init(&Encoder_M1, 4);//初始化编码器结构体参数   TIM4
//	Encoder_Struct_Init(&Encoder_M2, 2);//初始化编码器结构体参数   TIM2
	Encoder_Struct_Init(&Encoder_M3, 5);//初始化编码器结构体参数
//	Encoder_Struct_Init(&Encoder_M4, 3);//初始化编码器结构体参数
	
	IncPID_Init(&PID_M1, 12, 4, 0);//PID参数初始化
//    IncPID_Init(&PID_M2, 12, 4, 0);//PID参数初始化
    IncPID_Init(&PID_M3, 12, 4, 0);//PID参数初始化
//    IncPID_Init(&PID_M4, 12, 4, 0);//PID参数初始化

	VelControl.M1_SetRPM = 10;//左前电机转速  rpm 数值范围：-8000~8000，数值越大速度越快
//    VelControl.M2_SetRPM = 1000;//右前电机转速  rpm 数值范围：-8000~8000，数值越大速度越快
    VelControl.M3_SetRPM = 10;//左后电机转速 rpm 数值范围：-8000~8000，数值越大速度越快
//    VelControl.M4_SetRPM = 1000;//右后电机转速  rpm 数值范围：-8000~8000，数值越大速度越快


    while(mpu_dmp_init())//MPU DMP初始化
    {
        delay_ms(500);
//        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,0)	;        
    }

//    MX_CAN_Init();
//    CAN_Config();


	
	while(1)
  {	
	
		if(!Loop_10msTime)//10ms轮询一次
		{
//            VelocityControl_4WD(&VelControl);//4WD速度闭环控制函数
			Loop_10msTime = 5;//重新赋值时间


        if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
        {
            temp=MPU_Get_Temperature(); //得到温度值
//            MPU_Get_Accelerometer(&aacx,&aacy,&aacz);   //得到加速度传感器数据
            MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);    //得到陀螺仪数据

            g_fCarAngle=pitch*10;
            g_fCarAngle4=g_fCarAngle;
            g_fGyroAngleSpeed = ((gyrox / 65.5) +1)*10;

            AngleControl();
            if((g_fCarAngle > 400)||(g_fCarAngle < -400)) g_fAngleControlOut=0;
            
            VelocityControl(g_fAngleControlOut);

        }

        CAN_senddata(&hcan);

//        if(TXmessage[0]<254)
//        TXmessage[0] = TXmessage[0]+1;
//        else
//        TXmessage[0] = temp>>8;
//        TXmessage[1] = temp; 


        TXmessage[2] = (u8)g_fCarAngle>>24;
        TXmessage[3] = (u8)g_fCarAngle>>16;
        TXmessage[4] = (u8)g_fCarAngle>>8;
        TXmessage[5] = (u8)g_fCarAngle;
        

        TXmessage[6] = g_fCarAngle4>>8;
        TXmessage[7] = g_fCarAngle4;


        LED0=!LED0;//LED闪烁

		}


     

//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,0)	;	
//        delay_ms(10);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,1)	;
//        delay_ms(10);




/*
              if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
              {
                  temp=MPU_Get_Temperature(); //得到温度值
                  MPU_Get_Accelerometer(&aacx,&aacy,&aacz);   //得到加速度传感器数据
                  MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);    //得到陀螺仪数据



                  g_fGyroAngleSpeed = (gyrox / 16.384) * 10;


                  
                  if(GetData)//GetData=0时 用于USMART调试MPU6050寄存器
                  {
                      
                      if((t%10)==0)
                      {       
      
      
      //                    gyrox4 = (float)gyrox/(0xffff/500);
      //                    gyroy4 = (float)gyroy/(0xffff/500);
      //                    gyroz4 = (float)gyroz/(0xffff/500);
      
                      
                          //temp值
                          if(temp<0)
                          {
                              temp=-temp;     //转为正数
                          }

                              
                          //pitch值
                          pitch4=pitch*1000;
                          pitc4=pitch*10;
      //                    temp = pitch*10;

                          //roll值
                          roll4=roll*10;      
      //                    temp = roll*10;   

                          //yaw值
                          yaw4=yaw*10;
      //                    temp = yaw*10;    

                          t=0;
                          LED0=!LED0;//LED闪烁
                      }
      
                  }
                  
              }
              t++; 


*/







  }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
      Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
// _Error_Handler(__FILE__, __LINE__);
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
