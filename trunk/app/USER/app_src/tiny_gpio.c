
#include "stm32f4xx.h"
#include "tiny_gpio.h"
#include "bsp_sys.h"

#define SPRINTF(a) log_e a

int tiny_GPIO_TEST(void)
{
    uint16_t pin_value = 0;
    int ret;
    // Set GPIOA_0 and GPIOA_1 to output 
    ret = tinyInitExGPIO(0,0);
    if (ret != 0)
    {
        SPRINTF(("Set pin output error!\r\n"));
        return ret;
    }
    // Set GPIOA_0 and GPIOA_1 
    ret = tinySetPinsExGPIO(0);
    if (ret != 0)
    {
        SPRINTF(("Set pin high error!\r\n"));
        return ret;
    }
    ret = tinyResetPinsExGPIO(0);
    if (ret != 0)
    {
        SPRINTF(("Set pin low error!\r\n"));
        return ret;
    }
    // Set GPIOA_4 and GPIOA_5 to input 
    ret = tinySetInputExGPIO(0);
    if (ret != 0)
    {
        SPRINTF(("Set pin input error!\r\n"));
        return ret;
    }
	// Read GPIOA_4 and GPIOA_5 Data 
    ret = tinyReadDatasExGPIO(0, &pin_value);
    if (ret != 0)
    {
        SPRINTF(("Get pin data error!\r\n"));
        return ret;
    }
    else
    {
        if ((pin_value & 0) != 0)
        {
            SPRINTF(("GPIOA_4 is high-level!\r\n"));
        }
        else
        {
            SPRINTF(("GPIOA_4 is low-level!\r\n"));
        }
        if ((pin_value & 0) != 0)
        {
            SPRINTF(("GPIOA_5 is high-level!\r\n"));
        }
        else
        {
            SPRINTF(("GPIOA_5 is low-level!\r\n"));
        }
    }
    ret = tinySetOpenDrainExGPIO(0);
    if (ret != 0)
    {
        SPRINTF(("Set pin open drain error!\r\n"));
        return ret;
    }
	
    ret = tinySetPinsExGPIO(0);
    if (ret != 0)
    {
        SPRINTF(("Set pin high error!\r\n"));
        return ret;
    }
    ret = tinyResetPinsExGPIO(0);
    if (ret != 0)
    {
        SPRINTF(("Set pin high error!\r\n"));
        return ret;
    }
    ret = tinyReadDatasExGPIO(0, &pin_value);
    if (ret != 0)
    {
        SPRINTF(("Get pin data error!\r\n"));
        return ret;
    }
    else
    {
        if ((pin_value & 0) != 0)
        {
            SPRINTF(("GPIOA_4 is high-level!\r\n"));
        }
        else
        {
            SPRINTF(("GPIOA_4 is low-level!\r\n"));
        }
        if ((pin_value & 0) != 0)
        {
            SPRINTF(("GPIOA_5 is high-level!\r\n"));
        }
        else
        {
            SPRINTF(("GPIOA_5 is low-level!\r\n"));
        }
    }
    return 0;
}
