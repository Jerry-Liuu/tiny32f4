
#ifndef __TINY_USART_H_
#define __TINY_USART_H_

typedef struct _UART_INIT_CONFIG{
	uint8_t		StopBits;		    
	uint8_t		WordLength;		    
	uint8_t		Parity;			    
	uint16_t	RS485Mode;		    
	uint32_t	BaudRate;		    
}UART_INIT_CONFIG,*PUART_INIT_CONFIG;

typedef struct _tinyINITEX_CONFIG{
	uint8_t		StopBits;		     
	uint8_t		WordLength;		     
	uint8_t		Parity;			     
    uint16_t	RS485Mode;           
    uint32_t	BaudRate;		     
    uint16_t    HardwareFlowControl; 
}UART_INITEX_CONFIG,*PUART_INITEX_CONFIG;


extern int32_t  tinyInitUART(int32_t UARTIndex, PUART_INIT_CONFIG pInitConfig);
extern int32_t  tinyInitExUART(int32_t USARTIndex, PUART_INITEX_CONFIG pInitConfig);
extern int32_t  tinyWriteBytesUART(int32_t UARTIndex,uint8_t* pWriteData,uint16_t Len);
extern int32_t  tinyReadBytesUART(int32_t UARTIndex,uint8_t *pReadData,uint16_t *pLen);

#endif


