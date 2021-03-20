
#include "stm32f4xx.h"
#include "tiny_counter.h"
#include "bsp_sys.h"

#define SPRINTF(a) log_e a

int tiny_CNT_TEST(void)
{
	int ret;
    
	CNT_INIT_CONFIG CNTConfig;
	CNTConfig.CounterBitWide = 32;
	CNTConfig.CounterMode = 0;
	CNTConfig.CounterPolarity = 0;
	ret = tinyInitCNT(0,&CNTConfig);
	if(ret != 0){
		SPRINTF(("Config device error!\n"));
		return ret;
	}
	//Clear counter
	uint32_t CounterValue[4]={0,0,0,0};
	ret = tinySetCNT(0,CounterValue);
	if(ret != 0){ 
		SPRINTF(("Set counter value error!\n"));
		return ret;
	}
	//Start counter
	ret = tinyStartCNT(0);
	if(ret != 0){
		SPRINTF(("Start counter error!\n"));
		return ret;
	}
	while(1)
	{
		//Get counter value
		ret = tinyGetCNT(0,CounterValue);
		if(ret != 0){
			SPRINTF(("Get counter value error!\n"));
			//break;
		}else{
			SPRINTF(("Counter Value :%d\n",CounterValue[0]));
		}
		Sleep(1000);
	}
	//Stop counter
	ret = tinyStopCNT(0);
	if(ret != 0){
		SPRINTF(("Stop counter error!\n"));
		return ret;
	}
	return 0;
}
