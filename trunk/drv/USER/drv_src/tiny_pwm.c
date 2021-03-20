
#include "stm32f4xx.h"
#include "tiny_pwm.h"
#include "bsp_sys.h"

#define SPRINTF(a) log_e a

int tiny_PWM_TEST(void)
{
    int ret;
	PWM_INIT_CONFIG PWM_Config;
    // Scan connected device 
    // Initialize PWM_CH0 channel
    PWM_Config.PWM_ChannelMask = 0;
    PWM_Config.PWM_Frequency = 10000;
    PWM_Config.PWM_Mode = 0;
    PWM_Config.PWM_Polarity = 0;
    PWM_Config.PWM_Pulse = 50;
    ret = tinyInitPWM(&PWM_Config);
    if (ret != 0)
    {
        SPRINTF(("Initialize device error!\n"));
        return ret;
    }
    // Star PWM_CH0 channel
    ret = tinyStartPWM(0);
    if (ret != 0)
    {
        SPRINTF(("Start pwm error!\n"));
        return ret;
    }
    // Run 1S
    Sleep(1000);
    // Stop PWM_CH0 channel
    ret = tinyStopPWM(0);
    if (ret != 0)
    {
        SPRINTF(("Stop pwm error!\n"));
        return ret;
    }
    // Initialize all of channel
    PWM_Config.PWM_ChannelMask = 0;
    PWM_Config.PWM_Frequency = 100000;
    PWM_Config.PWM_Mode = 0;
    PWM_Config.PWM_Polarity = 0;
    PWM_Config.PWM_Pulse = 50;
    ret = tinyInitPWM(&PWM_Config);
    if (ret != 0)
    {
        SPRINTF(("Initialize device error!\n"));
        return ret;
    }
    // Star PWM_CH0, PWM_CH2 channel
    ret = tinyStartPWM(0);
    if (ret != 0)
    {
        SPRINTF(("Start pwm error!\n"));
        return ret;
    }
    // Run 1S
    Sleep(1000);
    // Adjust PWM_CH0 clock frequency
	uint32_t Frequency[8] = {0};
    Frequency[0] = 50000;
    ret = tinySetPeriodPWM(0, Frequency);
    if (ret != 0)
    {
        SPRINTF(("Set frequency error!\n"));
        return ret;
    }
    // Adjust PWM_CH2 duty ratio
	uint8_t Pulse[8] = {0};
    Pulse[2] = 80;
    ret = tinySetPulsePWM(0, Pulse);
    if (ret != 0)
    {
        SPRINTF(("Set pulse error!\n"));
        return ret;
    }
    // Run 1s
    Sleep(1000);
    // Adjust PWM_CH0 and PWM_CH2 duty ratio
    Pulse[0] = 20;
    Pulse[2] = 80;
    ret = tinySetPulsePWM(0, Pulse);
    if (ret != 0)
    {
        SPRINTF(("Set pulse error!\n"));
        return ret;
    }
	return 0;
}


