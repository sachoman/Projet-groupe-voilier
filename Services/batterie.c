#include "stm32f10x.h"
#include "adc.h"
#include "batterie.h" 
#include "Driver_GPIO.h"
#include "usart.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

double niveau_batterie;

MyADC_Struct_TypeDef MONADC1;
MyGPIO_Struct_TypeDef MONGPIOC0;

void init_batterie(void){
	MONADC1.ADC=ADC1;
	MONADC1.prio=4;
	MONADC1.Timer = TIM1;
	MONADC1.voie = 10;
	ADC_init_single(&MONADC1);
	MONGPIOC0.GPIO = GPIOC;
	MONGPIOC0.GPIO_Pin= 0;
	MONGPIOC0.GPIO_Conf=In_Analog;
	MyGPIO_Init(&MONGPIOC0);
}
void batterie_reception_donnees(void)
{
	MyADC_SWSTART(MONADC1.ADC);
	niveau_batterie = get_adcValue();
}

void check_batterie(void) {
	batterie_reception_donnees();
		if (niveau_batterie < 769){
			usart_1_send_string("\nWARNING LOW BATTERY !!!",strlen("\nWARNING LOW BATTERY !!!"));
		}
		else {
			usart_1_send_string("\nBattery ok! =)",strlen("\nBattery ok! =)"));

		}
}
