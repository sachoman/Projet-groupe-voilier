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

	void ADC_init_single_continuous(MyADC_Struct_TypeDef * adc);
	//CONT BIT ? 
	//EOC FLAG ? 
	/*The AWD analog watchdog status bit is set if the analog voltage converted by the ADC is 
			below a low threshold or above a high threshold. These thresholds are programmed in the 
			12 least significant bits of the ADC_HTR and ADC_LTR 16-bit registers. An interrupt can be 
			enabled by using the AWDIE bit in the ADC_CR1 register.
			The threshold value is independent of the alignment selected by the ALIGN bit in the 
			ADC_CR2 register. The comparison is done before the alignment (see Section 11.5).
			The analog watchdog can be enabled on one or more channels by configuring the 
			ADC_CR1 register as shown in Table 66.*/
	//SCAN BIT 
	/*Scan mode can be selected by setting the SCAN bit in the ADC_CR1 register. Once this bit 
			is set, ADC scans all the channels selected in the ADC_SQRx registers (for regular 
			channels) or in the ADC_JSQR (for injected channels). A single conversion is performed for 
			each channel of the group. After each end of conversion the next channel of the group is 
			converted automatically. If the CONT bit is set, conversion does not stop at the last selected 
			group channel but continues again from the first selected group channel.
			When using scan mode, DMA bit must be set and the direct memory access controller is 
			used to transfer the converted data of regular group channels to SRAM after each update of 
			the ADC_DR register.
			The injected channel converted data is always stored in the ADC_JDRx registers.*/

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
	

#endif