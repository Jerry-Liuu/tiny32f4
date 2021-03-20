
#ifndef __TINY_CAN_H_
#define __TINY_CAN_H_

typedef  struct  _CAN_OBJ{
	uint32_t	ID;			   
	uint32_t	TimeStamp;	   
	uint8_t	    TimeFlag;	    
	uint8_t	    SendType;	   
                       
	uint8_t	    RemoteFlag;	       
	uint8_t	    ExternFlag;	       
	uint8_t	    DataLen;	       
	uint8_t	    Data[8];	       
	uint8_t	    Reserved[3];       
}CAN_OBJ,*PCAN_OBJ;

typedef struct _CAN_STATUS{
	uint8_t	    ErrInterrupt;	
	uint8_t	    regMode;		
	uint8_t	    regStatus;		
	uint8_t	    regALCapture;	
	uint8_t	    regECCapture;	
	uint8_t	    regEWLimit;		
	uint8_t	    regRECounter;	
	uint8_t	    regTECounter;	
	uint32_t	regESR;			
	uint32_t	regTSR;			
	uint32_t	BufferSize;		
	uint32_t	Reserved;
}CAN_STATUS,*PCAN_STATUS;


typedef struct _CAN_ERR_INFO{
	uint32_t	ErrCode;			
	uint8_t	    Passive_ErrData[3];	
	uint8_t	    ArLost_ErrData;		
}CAN_ERR_INFO,*PCAN_ERR_INFO;


typedef struct _CAN_INIT_CONFIG{
	uint32_t	AccCode;	    
	uint32_t	AccMask;	    
	uint32_t	Reserved;	    
	uint8_t	    Filter;			
	uint8_t	    Timing0;		
	uint8_t	    Timing1;		
	uint8_t	    Mode;			
}CAN_INIT_CONFIG,*PCAN_INIT_CONFIG;

typedef struct _CAN_INIT_CONFIG_EX{
	uint32_t	CAN_BRP;	
	uint8_t	    CAN_SJW;	
	uint8_t	    CAN_BS1;	
	uint8_t	    CAN_BS2;	
	uint8_t	    CAN_Mode;	
	uint8_t	    CAN_ABOM;	
	uint8_t	    CAN_NART;	
	uint8_t	    CAN_RFLM;	
	uint8_t	    CAN_TXFP;	
	uint8_t	    CAN_RELAY;	
	uint32_t	Reserved;	
}CAN_INIT_CONFIG_EX,*PCAN_INIT_CONFIG_EX;

typedef struct _CAN_FILTER_CONFIG{
	uint8_t	    Enable;			
	uint8_t	    FilterIndex;	
	uint8_t	    FilterMode;		
	uint8_t	    ExtFrame;		
	uint32_t	ID_Std_Ext;		
	uint32_t	ID_IDE;			
	uint32_t	ID_RTR;			
	uint32_t	MASK_Std_Ext;	
	uint32_t	MASK_IDE;		
	uint32_t	MASK_RTR;		
	uint32_t	Reserved;		
}CAN_FILTER_CONFIG,*PCAN_FILTER_CONFIG;

typedef  const struct {
  int BAUD_RATE; 
  unsigned char   SJW;
  unsigned char   BS1;
  unsigned char   BS2;
  unsigned short  PreScale;
} CAN_BaudRate;


typedef void(*PCAN_RECEIVE_CALLBACK)(uint32_t CANIndex,uint32_t Len);
  
extern uint32_t  tinyInitCAN(uint32_t CANIndex, PCAN_INIT_CONFIG pInitConfig);
extern uint32_t  tinyInitExCAN(uint32_t CANIndex, PCAN_INIT_CONFIG_EX pInitConfig);

extern uint32_t  tinyReadErrInfoCAN(uint32_t CANIndex,PCAN_ERR_INFO pErrInfo);
extern uint32_t  tinyReadStatusCAN(uint32_t CANIndex,PCAN_STATUS pCANStatus);

extern uint32_t  tinyGetReferenceCAN(uint32_t CANIndex,uint32_t RefType,void *pData);
extern uint32_t  tinySetReferenceCAN(uint32_t CANIndex,uint32_t RefType,void *pData);
extern uint32_t  tinySetFilterCAN(uint32_t CANIndex,PCAN_FILTER_CONFIG pFilter);

extern uint32_t  tinyGetReceiveNumCAN(uint32_t CANIndex);
extern uint32_t  tinyClearBufferCAN(uint32_t CANIndex);

extern uint32_t  tinyStartCAN(uint32_t CANIndex);
extern uint32_t  tinyResetCAN(uint32_t CANIndex);

extern uint32_t  tinyRegisterReceiveCallbackCAN(PCAN_RECEIVE_CALLBACK pReceiveCallBack);
extern uint32_t  tinyLogoutReceiveCallbackCAN(void);

extern uint32_t  tinyTransmitCAN(uint32_t CANIndex,PCAN_OBJ pSend,uint32_t Len);
extern uint32_t  tinyReceiveCAN(uint32_t CANIndex,PCAN_OBJ pReceive,uint32_t Len,uint32_t WaitTime);

#endif
