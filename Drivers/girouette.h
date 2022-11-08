#ifndef GIROUETTE_H
#define GIROUETTE_H
#include "stm32f10x.h"
#include "timers.h"

//ici on utilise les gpio 
/*
	MyGPIO_Struct_TypeDef  MyGPIOA6;
	MyGPIO_Struct_TypeDef  MyGPIOA7;
	MyGPIO_Struct_TypeDef  MyGPIOC8;
	
	MyGPIOA6.GPIO = GPIOA;
	MyGPIOA6.GPIO_Pin = 6;
	MyGPIOA6.GPIO_Conf = In_Floating;
	MyGPIO_Init(&MyGPIOA6);
	
	
	
	MyGPIOA7.GPIO = GPIOA;
	MyGPIOA7.GPIO_Pin = 7;
	MyGPIOA7.GPIO_Conf = In_Floating;
	MyGPIO_Init(&MyGPIOA7);
	
	
	MyGPIOC8.GPIO = GPIOC;
	MyGPIOC8.GPIO_Pin = 8;
	MyGPIOC8.GPIO_Conf = In_Floating;
	MyGPIO_Init(&MyGPIOC8);
	
	*/
void girouette_init(MyTimer_Struct_TypeDef MonTimer1);

#endif