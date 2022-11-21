#include "stm32f10x.h"
#include "girouette.h"

void girouette_init(MyTimer_Struct_TypeDef MonTimer1){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI8_PC;
	EXTI->RTSR |= EXTI_RTSR_TR8;
	EXTI->IMR |= EXTI_IMR_MR8;
	EXTI->EMR |= EXTI_EMR_MR8;
	EXTI->FTSR |= EXTI_FTSR_TR8;
	NVIC_SetPriority(EXTI9_5_IRQn,3);
	NVIC_EnableIRQ(EXTI9_5_IRQn);	
	
	MyTimer_Base_Init(&MonTimer1);
	
	MonTimer1.Timer->CCMR1 |= TIM_CCMR1_CC1S_0;
	MonTimer1.Timer->CCMR1 &= ~TIM_CCMR1_IC1F;
	MonTimer1.Timer->CCER &= ~TIM_CCER_CC1P;
	MonTimer1.Timer->CCER &= ~TIM_CCER_CC1NP;
	MonTimer1.Timer->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	MonTimer1.Timer->CR1 |= TIM_CR1_CEN;
	
	MonTimer1.Timer->CCMR1 |= TIM_CCMR1_CC2S_0;
	MonTimer1.Timer->CCMR1 &= ~TIM_CCMR1_IC2F;
	MonTimer1.Timer->CCER &= ~TIM_CCER_CC2P;
	MonTimer1.Timer->CCER &= ~TIM_CCER_CC2NP;
}

void EXTI9_5_IRQHandler (void){
	EXTI->PR |= EXTI_PR_PR8;
	TIM3->CNT=0;
}
