
#ifndef __TINY_I2C_H_
#define __TINY_I2C_H_

typedef struct _I2C_INIT_CONFIG{
	uint8_t		MasterMode;		
	uint8_t		ControlMode;	
	uint8_t		AddrType;		
	uint8_t		SubAddrWidth;	
	uint16_t	Addr;			
	uint32_t	ClockSpeed;		
}I2C_INIT_CONFIG,*PI2C_INIT_CONFIG;

typedef struct _I2C_SNIFFER_CONFIG{
    uint16_t* TimBuffer;
    uint16_t* DataBuffer;
    uint16_t  TimBuffLen;
    uint16_t  DataBuffLen;
}I2C_SNIFFER_CONFIG,*PI2C_SNIFFER_CONFIG;

typedef struct _I2C_TIME_CONFIG
{
    uint16_t tHD_STA;   
    uint16_t tSU_STA;   
    uint16_t tLOW;      
    uint16_t tHIGH;     
    uint16_t tSU_DAT;   
    uint16_t tSU_STO;   
    uint16_t tDH;       
    uint16_t tDH_DAT;   
    uint16_t tAA;       
    uint16_t tR;        
    uint16_t tF;        
    uint16_t tBuf;      
    uint8_t tACK[4];
    uint16_t tStart;
    uint16_t tStop;
}I2C_TIME_CONFIG,*PI2C_TIME_CONFIG;


extern int32_t tinyTimeConfigI2C(int32_t I2CIndex, PI2C_TIME_CONFIG pTimeConfig);
extern int32_t tinyInitI2C(int32_t I2CIndex, PI2C_INIT_CONFIG pInitConfig);
extern int32_t tinyWriteBytesI2C(int32_t I2CIndex,uint16_t SlaveAddr,uint32_t SubAddr,uint8_t *pWriteData,uint16_t Len);
extern int32_t tinyReadBytesI2C(int32_t I2CIndex,uint16_t SlaveAddr,uint32_t SubAddr,uint8_t *pReadData,uint16_t Len);
extern int32_t tinySlaveReadBytesI2C(int32_t I2CIndex,uint8_t* pReadData,uint16_t *pLen);
extern int32_t tinySlaveWriteBytesI2C(int32_t I2CIndex,uint8_t* pWriteData,uint16_t Len);
extern int32_t tinySlaveWriteRemainI2C(int32_t I2CIndex,uint16_t* pRemainBytes);


#endif
