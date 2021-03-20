
#ifndef _TINY_PWM_H_
#define _TINY_PWM_H_

typedef struct _PWM_INIT_CONFIG{
	uint8_t		PWM_ChannelMask;		
	uint8_t   	PWM_Mode;		        
	uint8_t		PWM_Pulse;		        
	uint8_t		PWM_Polarity;	        
	uint32_t 	PWM_Frequency;	        
}PWM_INIT_CONFIG,*PPWM_INIT_CONFIG;


extern int32_t tinyInitPWM(PPWM_INIT_CONFIG pInitConfig);
extern int32_t tinyStartPWM(uint8_t ChannelMask);
extern int32_t tinyStopPWM(uint8_t ChannelMask);
extern int32_t tinySetPulsePWM(uint8_t ChannelMask,uint8_t *pPulse);
extern int32_t tinySetPeriodPWM(uint8_t ChannelMask,uint32_t *pFrequency);


#endif

