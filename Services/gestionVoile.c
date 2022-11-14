
#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "girouette.h"
#include "usart.h"
#include "Timer.h"
#include "pilotage-servomoteur.h"
#include "gestion-plateau.h"
#include "rotation-plateau.h"
#include "usart.h"
#include "gestionVoile.h"

extern MyTimer_Struct_TypeDef Servo_Struct_TIM;
extern MyTimer_Struct_TypeDef Rot_Struct_TIM;
int VoileCyclePwm;

 MyTimer_Struct_TypeDef Voile_MonTimer1;
		MyGPIO_Struct_TypeDef  MyGPIOA6;
	MyGPIO_Struct_TypeDef  MyGPIOA7;
	MyGPIO_Struct_TypeDef  MyGPIOC8;
	int currentVoileAngle;
	
	
	
int getAngle(void){
	return TIM3->CNT/4;
}


void voilegestion(void){
	currentVoileAngle = getAngle();
	if ((currentVoileAngle< 45) || (currentVoileAngle > 315)){
		Cycle_PWM (Servo_Timer, 500 , Servo_tim_channel);
	}
	else{
		if (currentVoileAngle > 180){
			currentVoileAngle = 360-currentVoileAngle;
		}
		currentVoileAngle = currentVoileAngle-45;
		VoileCyclePwm = 500+(500*(currentVoileAngle))/135;
		Cycle_PWM (Servo_Timer, VoileCyclePwm, Servo_tim_channel);
	}
}

void initGestionVoile(void){
	    Voile_MonTimer1.Timer = TIM3;
    Voile_MonTimer1.ARR = 360*4-1;
    Voile_MonTimer1.PSC = 0;
	
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
	girouette_init(Voile_MonTimer1);
	/*
	MyTimer_ActiveIT(&Rot_Struct_TIM, 2, voileHandler);
	*/
	
}



