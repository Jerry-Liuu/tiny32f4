
#include "stm32f4xx.h"
#include "tiny_dac.h"
#include "bsp_sys.h"

#define SPRINTF(a) log_e a

int tiny_DAC_TEST(void)
{
    int ret;
    //Scan connected device
    uint16_t DAC_Value[2]={1000,2000};
    // Initialize DAC_CH0 channel
    ret = tinyInitDAC(0,DAC_Value,256,0);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
    if (ret != 0)
    {
        SPRINTF(("Initialize DAC Channel 0 error!\r\n"));
        return ret;
    }else{
        SPRINTF(("Initialize DAC Channel 0 success!\r\n"));
    }
    // Set voltage values of DAC_CH0 
	ret = tinyStartDAC(0);
    if (ret != 0)
    {
        SPRINTF(("Start DAC error!\r\n"));
        return ret;
    }else{
        SPRINTF(("DAC Channel 0 Start Output 400MV"));
        SPRINTF(("\r\n"));
    }
	Sleep(100);
	ret = tinyStopDAC(0);
    if (ret != 0)
    {
        SPRINTF(("Stop DAC error!\r\n"));
        return ret;
    }else{
        SPRINTF(("DAC Channel 0 Stop Output"));
        SPRINTF(("\r\n"));
    }	
    // Initialize ADC_CH1
    ret = tinyInitDAC(0,DAC_Value,256,0);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
    if (ret != 0)
    {
        SPRINTF(("Initialize DAC Channel 1 error!\r\n"));
        return ret;
    }else{
        SPRINTF(("Initialize DAC Channel 1 success!\r\n"));
    }
    // Get voltage values of ADC_CH0 & ADC_CH1(each channel transfer a byte of data at a time.)
	ret = tinyStartDAC(0);
    if (ret != 0)
    {
        SPRINTF(("Start DAC data error!\r\n"));
        return ret;
    }
    else
    {
        SPRINTF(("DAC Channel 1 Start Output 400MV"));
		SPRINTF(("\r\n"));
    }
	ret = tinyStopDAC(0);
    if (ret != 0)
    {
        SPRINTF(("Stop DAC data error!\r\n"));
        return ret;
    }
    else
    {
        SPRINTF(("DAC Channel 1 Stop Output"));
		SPRINTF(("\r\n"));
    }	
	// Initialize DAC_CH0 & ADC_CH1, each channel sampling interval is set to 1000us
    ret = tinyInitDAC(0,DAC_Value,256,1000);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
	if (ret != 0)
    {
        SPRINTF(("Initialize DAC error!\r\n"));
        return ret;
    }else{
        SPRINTF(("Initialize DAC Channel 0 and 1 success!\r\n"));
    }
	ret = tinyStartDAC(0);
    if (ret != 0)
    {
        SPRINTF(("Start DAC data error!\r\n"));
        return ret;
    }else
    {
        SPRINTF(("DAC Channel 0 and 1 Start Output 3000MV\r\n"));
    }
	ret = tinyStopDAC(0);
    if (ret != 0)
    {
        SPRINTF(("Stop DAC data error!\r\n"));
        return ret;
    }else{
        SPRINTF(("DAC Channel 0 and 1 Stop Output\r\n"));
    }	
	return 0;
}

