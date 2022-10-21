#include "stm32f10x.h"
#include "adc.h"

int valeur_ADC;

void ADC_init_single_continuous(MyADC_Struct_TypeDef * adc){
	adc->ADC->CR2 &= ~ADC_CR2_CONT;
	adc->ADC->CR2 |= ADC_CR2_EXTTRIG;
	NVIC_SetPriority(ADC1_2_IRQn,adc->prio);
	NVIC_EnableIRQ(ADC1_2_IRQn);               
	//pour set les timers qui peuvent déclencher la converion
	//adc->ADC->CR2 |= (ADC_CR2_EXTSEL & ~ADC_CR2_EXTSEL_1);
	//TIM4_CC4 event : 101 a la page 225 RM008
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 
  RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; //clock 12MHz
	adc->ADC->SQR1&= ADC_SQR1_L; //nombre de conversion = 1 seule voie 
  adc->ADC->SQR3|= adc -> voie; // on choisit la seule voie a converir 
}

void ADC_on (MyADC_Struct_TypeDef * adc){
		if (adc->ADC->CR2 & ADC_CR2_ADON){
				adc->ADC->CR2|= ADC_CR2_ADON;
		}
	//si jamais on est déja on on ne lance pas la conversion en voulant allumer l'ADC
}

	void ADC_off (MyADC_Struct_TypeDef * adc){
		 adc->ADC->CR2 &= ~ADC_CR2_ADON;
	}

	int ADC_Read(MyADC_Struct_TypeDef * adc){	
		//interruption ou EOC est set ; on peut read 
		//while (!(adc->ADC->SR & ADC_SR_EOC)){}
    return adc->ADC->DR & ~((0x0F) << 12); //les 12 bits qui nous intéressent
	}
	
	void ADC1_2_IRQHandler (void){
		ADC1->SR &= ~ADC_SR_EOC; 
		//ADC2->SR &= ~ADC_SR_EOC;
		valeur_ADC = ADC1->DR & ~((0x0F) << 12);
	}