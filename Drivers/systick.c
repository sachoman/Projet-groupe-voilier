#include "stm32f10x.h"
#include "gestionVoile.h"
#include "girouette.h"
#include "usart.h"


int compteursystick = 0;


void systick_Init(int periode){
	SysTick->CTRL |= SysTick_CTRL_ENABLE;
	SysTick->CTRL |= SysTick_CTRL_TICKINT;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;
	SysTick->LOAD |=  (72000000/(1000/periode) - 1);
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 8);
}

void SysTick_Handler (void){
	if (compteursystick % 5 == 0){
		voileHandler();
		USART1_handler_reception_systick();
		USART1_handler_envoi_systick();
	}
	
	compteursystick++;
}
