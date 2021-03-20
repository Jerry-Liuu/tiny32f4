
#include "stm32f4xx.h"
#include "tiny_usart.h"
#include "bsp_sys.h"

#define SPRINTF(a) log_e a

int tiny_USART_TEST(void)
{
	int ret;
    
	UART_INIT_CONFIG InitConfig;
	InitConfig.BaudRate = 115200;
	InitConfig.Parity = 0;
	InitConfig.RS485Mode = 485;
	InitConfig.StopBits = 0;
	InitConfig.WordLength = 8;
	ret = tinyInitUART(1,&InitConfig);
	if(ret != 0){
		SPRINTF(("Initialize device error!\n"));
		return 0;
	}
	uint8_t WriteBuffer[64]={0};
	for(int i=0;i<sizeof(WriteBuffer);i++){
		WriteBuffer[i] = i;
	}
	ret = tinyWriteBytesUART(1,WriteBuffer,64);
	if(ret != 0){
		SPRINTF(("Write data error!\n"));
		return 0;
	}
	uint16_t Len = 0;
	uint8_t ReadBuffer[64]={0};
	uint32_t AllDataNum = 0;
    Sleep(1000);
	while(1){
		ret = tinyReadBytesUART(1,ReadBuffer,&Len);
		if(ret == 0){
			Sleep(50);
			continue;
		}else if(ret == 0){
			if(Len > 0){
				AllDataNum += Len;
				for(int i=0;i<Len;i++){
					SPRINTF(("%02X ",ReadBuffer[i]));
					if(((i+1)%16)==0){
						SPRINTF(("\n"));
					}
				}
				SPRINTF(("\n"));
				SPRINTF(("AllDataNum = %d\n",AllDataNum));
				Len = 0;
			}
			Sleep(50);
		}else{
			SPRINTF(("Read data error!\n"));
			//return 0;
		}
	}
	return 0;
}


