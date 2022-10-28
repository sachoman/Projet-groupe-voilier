#ifndef usarth
#define usarth
#include "stm32f10x.h"

#define UsartTimer TIM4
#define UsartTimerArr 10000
#define UsartTimerPsc 720
#define UsartBufferSize 10

void usart_configure_1_9600bps();
void usart_1_send(char data);
void usart_1_configure_IT(void (*fun) (void), char prio);
char usart_getValue(void);
#endif
