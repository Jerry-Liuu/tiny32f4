
#ifndef __FUNC_MAP_H_
#define __FUNC_MAP_H_


#if ADC_FLAG
extern int tiny_ADC_TEST(void);
#endif
    
#if CAN_FLAG
extern int tiny_CAN_TEST(void);
#endif
    
#if CNT_FLAG
extern int tiny_CNT_TEST(void);
#endif
    
#if DAC_FLAG
extern int tiny_DAC_TEST(void);
#endif
    
#if GPIO_FLAG
extern int tiny_GPIO_TEST(void);
#endif
    
#if I2C_FLAG
extern int tiny_I2C_TEST(void);
#endif

#if PWM_FLAG
extern int tiny_PWM_TEST(void);
#endif

#if SPI_FLAG
extern int tiny_SPI_TEST(void);
#endif

#if USART_FLAG 
extern int tiny_USART_TEST(void);
#endif

#if USB_FLAG
extern int tiny_USB_TEST(void);
#endif

#endif


