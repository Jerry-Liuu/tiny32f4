
#ifndef __TINY_SPI_H__
#define __TINY_SPI_H__

typedef struct _SPI_INIT_CONFIG{
    uint8_t     ControlMode;     
    uint8_t     TranBits;		
    uint8_t     MasterMode;		
    uint8_t     CPOL;			
    uint8_t     CPHA;			
    uint8_t     LSBFirst;		
    uint8_t     SelPolarity;	
	uint32_t	ClockSpeed;		
								
}SPI_INIT_CONFIG,*PSPI_INIT_CONFIG;

typedef struct _SPI_INIT_CONFIGEX{
    uint8_t     SPI_Index;      
//    uint8_t    *pSendData;    
//    uint8_t    *pReceive;     
//    uint32_t    DataLength;   
    uint8_t     ControlMode;    
    uint8_t     TranBits;		
    uint8_t     MasterMode;		
    uint8_t     CPOL;			
    uint8_t     CPHA;			
    uint8_t     LSBFirst;		
    uint8_t     SelPolarity;	
	uint32_t	ClockSpeed;		
								
}SPI_INIT_CONFIGEX,*PSPI_INIT_CONFIGEX;

typedef struct _SPI_FLASH_INIT_CONFIG
{
	uint32_t	page_size;
	uint32_t	page_num;
	uint8_t		write_enable[8];
	uint8_t		read_status[8];
	uint8_t		chip_erase[8];
	uint8_t		write_data[8];
	uint8_t		read_data[8];
	uint8_t		first_cmd[8];
	uint8_t		busy_bit;
	uint8_t		busy_mask;
	uint8_t		addr_bytes;
	uint8_t		addr_shift;
	uint8_t		init_flag;
}SPI_FLASH_INIT_CONFIG,*PSPI_FLASH_INIT_CONFIG;

extern int32_t tinyInitSPI(PSPI_INIT_CONFIG pInitConfig);
extern int32_t tinyInitExSPI(PSPI_INIT_CONFIGEX pInitConfigEx);
extern int32_t tinyWriteBytesSPI(int32_t SPIIndex,uint8_t *pWriteData,uint16_t Len);
extern int32_t tinyReadBytesSPI(int32_t SPIIndex,uint8_t *pReadData,uint16_t Len);
extern int32_t tinyWriteReadBytesSPI(int32_t SPIIndex,uint8_t* pWriteData,
									uint16_t WriteLen,uint8_t * pReadData,uint16_t ReadLen);
extern int32_t tinyWriteBitsSPI(int32_t SPIIndex,uint8_t *pWriteBitStr);
extern int32_t tinyReadBitsSPI(int32_t SPIIndex,uint8_t *pReadBitStr,int32_t ReadBitsNum);
extern int32_t tinyWriteReadBitsSPI(int32_t SPIIndex,
								uint8_t *pWriteBitStr,uint8_t *pReadBitStr,int32_t ReadBitsNum);
extern int32_t tinySlaveReadBytesSPI(uint8_t *pReadData,int32_t *pBytesNum,int32_t WaitTime);
extern int32_t tinySlaveWriteBytesSPI(uint8_t *pWriteData,int32_t WriteBytesNum);	
extern int32_t tinyFlashInitSPI(PSPI_FLASH_INIT_CONFIG pFlashInitConfig);
extern int32_t tinyFlashWriteBytesSPI(int32_t PageAddr,uint8_t *pWriteData,uint16_t WriteLen);
extern int32_t tinyFlashReadBytesSPI(int32_t PageAddr,uint8_t *pReadData,uint16_t ReadLen);

extern int32_t tinyBlockWriteBytesSPI(int32_t SPIIndex,uint8_t *pWriteData,
									uint16_t BlockSize,uint16_t BlockNum,uint32_t IntervalTime);	
extern int32_t tinyBlockReadBytesSPI(int32_t SPIIndex,uint8_t *pReadData,
									uint16_t BlockSize,uint16_t BlockNum,uint32_t IntervalTime);
extern int32_t tinyBlockWriteReadBytesSPI(int32_t SPIIndex,uint8_t *pWriteData,uint16_t WriteBlockSize,
										uint8_t *pReadData,uint16_t ReadBlockSize,uint16_t BlockNum,uint32_t IntervalTime);

#endif

