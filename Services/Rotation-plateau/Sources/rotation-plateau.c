#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "rotation-plateau.h"
#include "Timer.h"

	MyGPIO_Struct_TypeDef Rot_Struct_Gpio_PWM;
	MyGPIO_Struct_TypeDef Rot_Struct_Gpio_Sens;
	MyTimer_Struct_TypeDef Rot_Struct_TIM;

void initPlateau(void){
	//init gpio
	Rot_Struct_Gpio_PWM.GPIO = Rot_Gpio_PWM;
	Rot_Struct_Gpio_Sens.GPIO = Rot_Gpio_sens;
	Rot_Struct_Gpio_PWM.GPIO_Conf = AltOut_Ppull;
	Rot_Struct_Gpio_Sens.GPIO_Conf = Out_Ppull;
	Rot_Struct_Gpio_PWM.GPIO_Pin  = Rot_Pin_PWM;
	Rot_Struct_Gpio_Sens.GPIO_Pin = Rot_Pin_sens ;
	MyGPIO_Init(&Rot_Struct_Gpio_PWM);
	MyGPIO_Init(&Rot_Struct_Gpio_Sens);
	
	//init PWM
	Rot_Struct_TIM.Timer= Rot_Timer;
	Rot_Struct_TIM.ARR = Rot_ARR;
	Rot_Struct_TIM.PSC = Rot_PSC;
	MyTimer_Base_Init (&Rot_Struct_TIM);
	MyTimer_PWM (Rot_Timer, Rot_tim_channel );
	Cycle_PWM (Rot_Timer, 0, Rot_tim_channel);
	MyTimer_Base_Start(Rot_Timer);
}

void tourneGauche(int alpha){
	Rot_Gpio_sens->ODR |= (1<<Rot_Pin_sens);
	Cycle_PWM (Rot_Timer, alpha, Rot_tim_channel);
}
void tourneDroite(int alpha){
	Rot_Gpio_sens->ODR &= ~(1<<Rot_Pin_sens);
	Cycle_PWM (Rot_Timer, alpha, Rot_tim_channel);
}
/*
int main(void){
	initPlateau();
	while(1){
	}
}
*/
