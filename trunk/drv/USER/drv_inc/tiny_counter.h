


#ifndef __TINY_COUNTER_H_
#define __TINY_COUNTER_H_

typedef struct _CNT_INIT_CONFIG{
	uint8_t 	CounterMode;		
	uint8_t		CounterPolarity;	
	uint8_t		CounterBitWide;		
}CNT_INIT_CONFIG,*PCNT_INIT_CONFIG;


extern int32_t  tinyInitCNT(uint8_t Channel, PCNT_INIT_CONFIG pInitConfig);
extern int32_t  tinySetCNT(uint8_t Channel, uint32_t *pCounterValue);
extern int32_t  tinyGetCNT(uint8_t Channel, uint32_t *pCounterValue);
extern int32_t  tinyStartCNT(uint8_t Channel);
extern int32_t  tinyStopCNT(uint8_t Channel);


#endif

