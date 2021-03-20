
#include "stm32f4xx.h"
#include "tiny_spi.h"
#include "bsp_sys.h"

#define SPRINTF(a) log_e a

int tiny_SPI_TEST(void)
{
	int ret,i;
	SPI_INIT_CONFIGEX	SPI_Init;
	uint8_t	WriteDataTemp[512]={0};
	uint8_t	ReadDataTemp[512]={0};
    uint8_t spi_index = 0;
    
	// Device initialization
	SPI_Init.ClockSpeed = 1125000;
	SPI_Init.ControlMode = 1;
	SPI_Init.CPHA = 1;
	SPI_Init.CPOL = 1;
	SPI_Init.LSBFirst = 0;
	SPI_Init.MasterMode = 1;
	SPI_Init.SelPolarity = 0;
	SPI_Init.TranBits = 8;
    SPI_Init.SPI_Index = spi_index;
	ret = tinyInitExSPI(&SPI_Init);
	if(ret != 0){
		SPRINTF(("Initialization device error :%d\n",ret));
		return ret;
	}else{
		SPRINTF(("Initialization device success!\n"));
	}
	// JEDEC ID
	WriteDataTemp[0] = 0x9F;
	ret = tinyWriteReadBytesSPI(spi_index,WriteDataTemp,1,ReadDataTemp,3);
	if(ret != 0){
		SPRINTF(("Read flash ID error :%d\n",ret));
		return ret;
	}else{
		SPRINTF(("Flash ID = 0x%06X\n",(ReadDataTemp[0]<<16)|(ReadDataTemp[1]<<8)|(ReadDataTemp[2])));
	}
	// Write Enable
	WriteDataTemp[0] = 0x06;
	ret = tinyWriteBytesSPI(spi_index,WriteDataTemp,1);
	if(ret != 0){
		SPRINTF(("Flash write enable error :%d\n",ret));
		return ret;
	}else{
		SPRINTF(("Write enable success!\n"));
	}
	// Sector Erase (4KB)
	WriteDataTemp[0] = 0x20;
	WriteDataTemp[1] = 0x00;
	WriteDataTemp[2] = 0x00;
	WriteDataTemp[3] = 0x00;
	ret = tinyWriteBytesSPI(spi_index,WriteDataTemp,4);
	if(ret != 0){
		SPRINTF(("Sector Erase start error :%d\n",ret));
		return ret;
	}else{
		SPRINTF(("Sector erase start success!\n"));
	}
	// Check the operation to complete
	do{
		WriteDataTemp[0] = 0x05;// Read Status Register-1
		ret = tinyWriteReadBytesSPI(spi_index,WriteDataTemp,1,ReadDataTemp,1);

	}while((ReadDataTemp[0]&0x01)&&(ret == 0));
	if(ret != 0){
		SPRINTF(("Sector Erase error :%d\n",ret));
		return ret;
	}else{
		SPRINTF(("Sector erase success!\n"));
	}
	// Write Enable
	WriteDataTemp[0] = 0x06;
	ret = tinyWriteBytesSPI(spi_index,WriteDataTemp,1);
	if(ret != 0){
		SPRINTF(("Flash write enable error :%d\n",ret));
		return ret;
	}else{
		SPRINTF(("Write enable success!\n"));
	}
	// Page Program
	WriteDataTemp[0] = 0x02;// Page Program command
	WriteDataTemp[1] = 0x00;// Address
	WriteDataTemp[2] = 0x00;
	WriteDataTemp[3] = 0x00;
	for(i=4;i<(256+4);i++){
		WriteDataTemp[i] = i-4;
	}
	ret = tinyWriteBytesSPI(spi_index,WriteDataTemp,256+4);
	if(ret != 0){
		SPRINTF(("Page program start error :%d\n",ret));
		return ret;
	}else{
		SPRINTF(("Page program start success!\n"));
	}
	// Check the operation to complete
	do{
		WriteDataTemp[0] = 0x05;// Read Status Register-1
		ret = tinyWriteReadBytesSPI(spi_index,WriteDataTemp,1,ReadDataTemp,1);

	}while((ReadDataTemp[0]&0x01)&&(ret == 0));
	if(ret != 0){
		SPRINTF(("Page program error :%d\n",ret));
		return ret;
	}else{
		SPRINTF(("Page program success!\n"));
	}
	// Read Data
	WriteDataTemp[0] = 0x03;//Read Data command
	WriteDataTemp[1] = 0x00;//address
	WriteDataTemp[2] = 0x00;
	WriteDataTemp[3] = 0x00;
	ret = tinyWriteReadBytesSPI(spi_index,WriteDataTemp,4,ReadDataTemp,256);
	if(ret != 0){
		SPRINTF(("Read Data error :%d\n",ret));
		return ret;
	}else{
		SPRINTF(("Read Data success\n"));
	}
	for(i=0;i<256;i++){
		if((i%26)==0){
			SPRINTF(("\n"));
		}
		SPRINTF(("%02X ",ReadDataTemp[i]));
	}
	SPRINTF(("\n\n"));
	return 0;
}


