#include "stm32f10x.h"
#include "usart.h"
#include "timer.h"
#include "Driver_GPIO.h"


static char usart_Data;
int usart_i;
void (* usart_ptr) (void);
//registre USART1 Rx= PA10
//Usart1 TX = PA9

MyGPIO_Struct_TypeDef Usart_gpio;
MyTimer_Struct_TypeDef Usart_tim4;

char usart_buffer[UsartBufferSize];
int usart_buffer_index=0;

void usart_configure_1_9600bps(){
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Validation horloge
    USART1->CR1 |= USART_CR1_UE; // Activation
		USART1->CR1 |= USART_CR1_RE;
    USART1->CR1 &= ~USART_CR1_M; // Taille de 8 bits de données
    USART1->CR2 &= USART_CR2_STOP; // Choix d'un seul bit de stop
    USART1->BRR |= 468 << 4; // Mantisse register à 468 -> 9600 baud rate
    USART1->BRR |= 75; // Fraction register à 75 -> 9600 baud rate
    USART1->CR1 |= USART_CR1_TE; // Transmitter enable
		Usart_gpio.GPIO= GPIOA;
		Usart_gpio.GPIO_Conf=AltOut_Ppull;
		Usart_gpio.GPIO_Pin=9;
		MyGPIO_Init(&Usart_gpio);
}

void usart_1_send(char data){
    USART1->DR |= data; // Ecriture de la donnée dans DR
    while(!(USART1->SR & USART_SR_TXE)) {} // Attente si data register empty
}
void usart_1_send_string(char * data, int length){
	for (usart_i=0; usart_i<length; usart_i++){
		usart_1_send(data[usart_i]);
	}
}
void USART1_IRQHandler(){
	usart_Data=USART1->DR;
	usart_ptr();
}

char usart_getValue(void)
{
	return usart_Data;
}

void usart_1_configure_IT(void (*fun) (void), char prio){
	USART1->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_SetPriority(USART1_IRQn, prio);
	usart_ptr = fun;
}

