
#include "stm32f4xx.h"
#include "tiny_adc.h"
#include "bsp_sys.h"

#define SPRINTF(a) log_e a

int tiny_ADC_TEST(void)
{
    int ret;
	uint8_t SamplingCnt = 0;
    
    ret = tinyInitADC(0,0);
    if (ret != 0)
    {
        SPRINTF(("Initialize ADC error!\n"));
        return ret;
    }
	uint16_t adc_datas[4096] = {0};
    
    ret = tinyReadDatasADC(1, adc_datas);
    if (ret != 0)
    {
        SPRINTF(("Read ADC data error!\n"));
        return ret;
    }
    else
    {
        SPRINTF(("ADC_CH0 = %.3f\n" ,((adc_datas[0]*3.3)/4095)));
        SPRINTF(("\n"));
    }
    // Initialize ADC_CH0 & ADC_CH1
    ret = tinyInitADC(0, 0);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
    if (ret != 0)
    {
        SPRINTF(("Initialize ADC error!\n"));
        return ret;
    }
    // Get voltage values of ADC_CH0 & ADC_CH1(each channel transfer a byte of data at a time.)
    ret = tinyReadDatasADC(1, adc_datas);
    if (ret != 0)
    {
        SPRINTF(("Read ADC data error!\n"));
        return ret;
    }
    else
    {
        SPRINTF(("ADC_CH0 = %.3f\n" , ((adc_datas[0] * 3.3) / 4095)));
        SPRINTF(("ADC_CH1 = %.3f\n" , ((adc_datas[1] * 3.3) / 4095)));
		SPRINTF(("\n"));
    }
	// Initialize ADC_CH0 & ADC_CH1, each channel sampling interval is set to 1000us
    ret = tinyInitADC(0, 1000);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
    if (ret != 0)
    {
        SPRINTF(("Initialize ADC error!\n"));
        return ret;
    }
	// Get voltage values of ADC_CH0 & ADC_CH1
    ret = tinyReadDatasADC(10, adc_datas);//Get 10 values each channel, return a total of 20 values
    if (ret != 0)
    {
        SPRINTF(("Read ADC data error!\n"));
        return ret;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            SPRINTF(("ADC_CH0[%d] = %.3f\n" ,i, ((adc_datas[i*2] * 3.3) / 4095)));
        }
        SPRINTF(("\n"));
        for (int i = 0; i < 10; i++)
        {
            SPRINTF(("ADC_CH1[%d] = %.3f\n" ,i, ((adc_datas[i*2+1] * 3.3) / 4095)));
        }
    }
	SPRINTF(("=====================================================================\n"));
	while(1)
	{
		// Get voltage values of ADC_CH0 & ADC_CH1
		ret = tinyReadDatasADC(10, adc_datas);//Get 10 values each channel, return a total of 10 values,1ms*10=10ms
		if (ret != 0)
		{
			SPRINTF(("Read ADC data error!\n"));
			return ret; // exit if error ocurred
		}

		// 10ms * 100 =1s in theory,but there is other time-consuming in practice,I choose 50
		if( 50 == ++SamplingCnt ) //
		{
			SamplingCnt = 0;
			SPRINTF(("ADC_CH0 = %.3f\n" , ((adc_datas[0] * 3.3) / 4095)));
		}
	}
}

