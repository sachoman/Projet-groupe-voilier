#ifndef ADC_H
#define ADC_H
#include "stm32f10x.h"

typedef struct
{
	/*
	?? rajouter ce qu'il faut à la struct
	*/
	char prio;
	TIM_TypeDef * Timer;
	char voie; 
	ADC_TypeDef * ADC;
} MyADC_Struct_TypeDef;

//eventuellement créer un trype case pour chaque mode et faire un seul init 
		//avec un grand if

	void ADC_init_single(MyADC_Struct_TypeDef * adc);
	
	void ADC_on (MyADC_Struct_TypeDef * adc);
/*The ADC can be powered-on by setting the ADON bit in the ADC_CR2 register. When the
	ADON bit is set for the first time, it wakes up the ADC from Power Down mode.*/
	void ADC_off (MyADC_Struct_TypeDef * adc);
	//void start_conversion(MyADC_Struct_TypeDef * adc);
	//just set the "ADON" bit again 
	int ADC_Read(MyADC_Struct_TypeDef * adc);
	
	//ADC CLOCK : 
	/*La documentation nous apprend que l'horloge de l'ADC doit avoir une 
			fréquence inférieure à 14 MHz pour que le périphérique fonctionne. 
			Il faut donc modifier cette fréquence en configurant les registres du RCC. 
			Pour cela, ajoutez la ligne suivante qui va permettre de diviser par 6 la 
			fréquence d'entrée (72 MHz) */

#define MyADC_SWSTART(A)(A->CR2|=ADC_CR2_SWSTART) 
//Macro pour le software trigger

#endif
