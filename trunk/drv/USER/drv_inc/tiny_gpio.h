

#ifndef _TINY_GPIO_H_
#define _TINY_GPIO_H_

extern int32_t  tinyInitExGPIO(uint32_t PinMask, uint32_t PinMode);
extern int32_t  tinyWriteDatasExGPIO( uint32_t PinMask,uint16_t Data);
extern int32_t  tinyReadDatasExGPIO(uint32_t PiWnMask,uint16_t *pData);
extern int32_t	tinySetPinsExGPIO(uint32_t PinMask);
extern int32_t	tinyResetPinsExGPIO(uint32_t PinMask);
extern int32_t	tinySetInputExGPIO(uint32_t PinMask);
extern int32_t	tinySetOutputExGPIO(uint32_t PinMask);
extern int32_t	tinySetOpenDrainExGPIO(uint32_t PinMask);

#endif


