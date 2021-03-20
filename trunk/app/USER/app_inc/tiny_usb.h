
#ifndef __TINY_USB_H_
#define __TINY_USB_H_

extern int32_t  tinyInitUSB(int32_t USBMode);
extern int32_t  tinyWriteByteUSB(uint8_t *p_WriteData,uint32_t Lenth,uint16_t waittime);
extern int32_t  tinyReadByteUSB(uint8_t *p_ReadData,uint32_t Lenth,uint16_t waittime);
extern int32_t  tinyGetReceiveNumUSB(void);

#endif

