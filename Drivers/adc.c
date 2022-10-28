#include "stm32f10x.h"
#include "adc.h"

static int valeur_ADC;

void ADC_init_single(MyADC_Struct_TypeDef * adc){
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; //clock 12MHz
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 
  adc->ADC->CR2 &= ~ADC_CR2_CONT;
	adc->ADC->CR2 |= ADC_CR2_EXTTRIG;
	adc->ADC->CR1 |= ADC_CR1_EOCIE;
	NVIC_SetPriority(ADC1_2_IRQn,adc->prio);
	NVIC_EnableIRQ(ADC1_2_IRQn);               
	//pour set les timers qui peuvent déclencher la converion
	adc->ADC->CR2 |= ADC_CR2_EXTSEL ;
	//la on est en software control bit
	adc->ADC->SQR1&= ADC_SQR1_L; //nombre de conversion = 1 seule voie 
  adc->ADC->SQR3|= adc -> voie; // on choisit la seule voie a converir 
	adc->ADC->CR2|= ADC_CR2_ADON;
}

void ADC_on (MyADC_Struct_TypeDef * adc){
				adc->ADC->CR2|= ADC_CR2_ADON;
}


	void ADC_off (MyADC_Struct_TypeDef * adc){
		 adc->ADC->CR2 &= ~ADC_CR2_ADON;
	}

	int ADC_Read(MyADC_Struct_TypeDef * adc){	
		//interruption ou EOC est set ; on peut read 
    return adc->ADC->DR & ~((0x0F) << 12); //les 12 bits qui nous intéressent
	}
	
	int get_adcValue(){
		return valeur_ADC;
	}
	void ADC1_2_IRQHandler (void){
		ADC1->SR &= ~ADC_SR_EOC; 
		//ADC2->SR &= ~ADC_SR_EOC;
		valeur_ADC = ADC1->DR & ~((0x0F) << 12);
	}

