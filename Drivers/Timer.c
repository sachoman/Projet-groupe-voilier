#include "stm32f10x.h"
#include "timer.h"

void (*ptr1) (void);
void (*ptr2) (void);
void (*ptr3) (void);
void (*ptr4) (void);
int Tim_cycle_pwm;

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ){
	if ( Timer->Timer == TIM1){
		RCC->APB2ENR|=RCC_APB2ENR_TIM1EN;
	}
	if ( Timer->Timer == TIM2){
		RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
	}
	if ( Timer->Timer == TIM3){
		RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
	}
	if ( Timer->Timer == TIM4){
		RCC->APB1ENR|=RCC_APB1ENR_TIM4EN;
	}
	Timer->Timer->ARR= Timer->ARR;
	Timer->Timer->PSC=Timer->PSC;
	Timer->Timer->CR1 &= ~(0x1<<0x4); //DIR reset (default upcounter)
}

void MyTimer_ActiveIT( MyTimer_Struct_TypeDef * Timer, char Prio, void (*IT_function) (void)){
	Timer->Timer->DIER |= TIM_DIER_UIE; // demande interruption transmise au NVIC a chaque débordement
	//TIm2 bit 28 du registre
	if (Timer->Timer == TIM2 ){
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, Prio);
		ptr2 = IT_function;
	}
	else if (Timer->Timer == TIM3){
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, Prio);
		ptr3 = IT_function;
	}
	else if (Timer->Timer == TIM4){
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, Prio);
		ptr4 = IT_function;
	}
	else if (Timer->Timer == TIM1){
		NVIC_EnableIRQ(TIM1_UP_IRQn);
		NVIC_SetPriority(TIM1_UP_IRQn, Prio);
		ptr1 = IT_function;
	}
}

void TIM2_IRQHandler ( void )
{
	TIM2->SR &= ~TIM_SR_UIF;	// met à 0 le bit UIF du timer
	ptr2();
}
void TIM1_UP_IRQHandler ( void )
{
	TIM1->SR &= ~TIM_SR_UIF;	// met à 0 le bit UIF du timer
	ptr1();
}
void TIM3_IRQHandler ( void )
{
	TIM3->SR &= ~TIM_SR_UIF;	// met à 0 le bit UIF du timer
	ptr3();
}
void TIM4_IRQHandler ( void )
{
	TIM4->SR &= ~TIM_SR_UIF;	// met à 0 le bit UIF du timer
	ptr4();
}
//voir p177 doc pour savoir quel channel avec timer sort la pwm
//ou datasheet p29 colonne lqsf64
void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ){
	if (Channel ==1){
		Timer->CCMR1 &= ~TIM_CCMR1_OC1M_0; //reset configuration pwm doc p413
		Timer->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;; //on met en mode 1 (110)
		Timer->CCER |= TIM_CCER_CC1E;
	}
	else if (Channel == 2){
		Timer->CCMR1 &= ~TIM_CCMR1_OC2M_0; //reset configuration pwm doc p413
		Timer->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;; //on met en mode 1 (110)
		Timer->CCER |= TIM_CCER_CC2E;
	}
	else if (Channel == 3){
		Timer->CCMR2 &= ~TIM_CCMR2_OC3M_0; //reset configuration pwm doc p413
		Timer->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;; //on met en mode 1 (110)
		Timer->CCER |= TIM_CCER_CC3E;
	}
	else if (Channel == 4){
		Timer->CCMR2 &= ~TIM_CCMR2_OC4M_0; //reset configuration pwm doc p413
		Timer->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;; //on met en mode 1 (110)
		Timer->CCER |= TIM_CCER_CC4E;
	}
}

void Cycle_PWM(TIM_TypeDef * Timer, int alpha, char channel){
	Tim_cycle_pwm = (alpha*Timer->ARR)/10000;
	if (channel == 1){
	Timer->CCR1=Tim_cycle_pwm;
	}
	else if (channel ==2){
		Timer->CCR2=Tim_cycle_pwm;
	}
	else if (channel == 3){
		Timer->CCR3=Tim_cycle_pwm;
	}
	else if (channel == 4){
		Timer->CCR4=Tim_cycle_pwm;
	}
}
