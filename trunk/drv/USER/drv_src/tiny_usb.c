
#include "stm32f4xx.h"
#include "tiny_usb.h"
#include "bsp_sys.h"

#define SPRINTF(a) log_e a

int tiny_USB_TEST(void)
{
	int ret;
    static uint32_t SendDataNum = 0;
    static uint8_t SendDataBuff[64 *1024]={0x00};
	static uint8_t	read_buffer[8]={0};
    
    ret = tinyInitUSB(0);
    if (ret != 0)
    {
        SPRINTF(("Initialize device error!\r\n"));
        return ret;
    }
    while(1)
    {
        ret = tinyReadByteUSB(read_buffer, 4 ,0);
        if (ret != 0)
        {
            SPRINTF(("Read data error!\r\n"));
            return ret;
        }
        SendDataNum = read_buffer[0]<<24 | read_buffer[1]<<16 | read_buffer[2]<<8 | read_buffer[3];
        SPRINTF(("SendDataNum : %d\n",SendDataNum));
        do{
            ret = tinyWriteByteUSB(SendDataBuff, sizeof(SendDataBuff),0);
            if (ret != 0)
            {
                SPRINTF(("Write data error!\r\n"));
                return ret;
            }     
            SendDataNum--;            
        }while(SendDataNum>0);     
    }
}


