
#ifndef __TINY_DAC_H_
#define __TINY_DAC_H_

extern int32_t tinyInitDAC(uint8_t Channel,uint16_t *pWaveData,uint16_t WaveDataNum,uint16_t Period);
extern int32_t tinyStartDAC(uint8_t Channel);
extern int32_t tinyStopDAC(uint8_t Channel);

#endif

