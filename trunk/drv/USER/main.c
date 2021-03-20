  /*
  ******************************************************************************
  * @file     : tiny_Test.c
  * @Copyright:  
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23
  * @brief    : tiny_Test demo
  ******************************************************************************
  * @attention
  *
  * Copyright 2019-2020, 
  * All Rights Reserved
  * 
  ******************************************************************************
  */
#include <stdio.h>
#include "stm32f4xx.h"
#include "func_map.h"

int main(int argc, char* argv[])
{
#if ADC_FLAG
    tiny_ADC_TEST();
#endif
    
#if CAN_FLAG
    tiny_CAN_TEST();
#endif
    
#if CNT_FLAG
    tiny_CNT_TEST();
#endif
    
#if DAC_FLAG
    tiny_DAC_TEST();
#endif
    
#if GPIO_FLAG
    tiny_GPIO_TEST();
#endif
    
#if I2C_FLAG
    tiny_I2C_TEST();
#endif

#if PWM_FLAG
    tiny_PWM_TEST();
#endif

#if SPI_FLAG
    tiny_SPI_TEST();
#endif

#if USART_FLAG 
    tiny_USART_TEST();
#endif

#if USB_FLAG
    tiny_USB_TEST();
#endif
}
