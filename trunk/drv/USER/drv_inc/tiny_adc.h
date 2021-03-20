

#ifndef __TINY_ADC_H_
#define __TINY_ADC_H_

extern int32_t tinyInitADC(uint8_t Channel, uint16_t Period);
extern int32_t tinyReadDatasADC(uint16_t DataNum,uint16_t *pData);

#endif
