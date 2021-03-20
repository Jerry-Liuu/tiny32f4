
#include "stm32f4xx.h"
#include "tiny_i2c.h"
#include "bsp_sys.h"

#define SPRINTF(a) log_e a

int tiny_I2C_TEST(void)
{
	int ret,i;
    
	I2C_INIT_CONFIG I2C_Config;
	uint8_t write_buffer[8]={0};
	uint8_t	read_buffer[8]={0};
    int8_t I2C_Index = 0;
    
    //Initializes the device
    I2C_Config.AddrType = 0;
    I2C_Config.ClockSpeed = 400000;
    I2C_Config.ControlMode = 0;
    I2C_Config.MasterMode = 0;
    I2C_Config.SubAddrWidth = 0;
    ret = tinyInitI2C(I2C_Index, &I2C_Config);
    if (ret != 0)
    {
        SPRINTF(("Initialize device error!\r\n"));
        return ret;
    }
	//Write 8 byte data to 0x00
	for (i = 0; i < 8; i++)
    {
        write_buffer[i] = i+2;
    }
    ret = tinyWriteBytesI2C(I2C_Index, 0xA0, 0x00, write_buffer, 8);
    if (ret != 0)
    {
        SPRINTF(("Write data error!\r\n"));
        return ret;
    }
    //Delay
    Sleep(100);
	//Read 8 byte data from 0x00
    ret = tinyReadBytesI2C(I2C_Index, 0xA0, 0x00, read_buffer, 8);
    if (ret != 0)
    {
        SPRINTF(("Read data error!\r\n"));
        return ret;
    }
	else
	{
		SPRINTF(("Read Data:\r\n"));
		for(i=0;i<8;i++)
		{
			SPRINTF(("%02X ",read_buffer[i]));
		}
		SPRINTF(("\r\n"));
	}
    return 0;
}
