#include "usart.h"
#include "timer.h"
#include "Driver_Gpio.h"
#include "pilotage-servomoteur.h"
#include "stm32f10x.h"

MyGPIO_Struct_TypeDef Servo_Struct_Gpio_PWM;
MyTimer_Struct_TypeDef Servo_Struct_TIM;

void initServo(void){
	//init gpio
	Servo_Struct_Gpio_PWM.GPIO = Servo_Gpio_PWM;
	Servo_Struct_Gpio_PWM.GPIO_Conf = AltOut_Ppull;
	Servo_Struct_Gpio_PWM.GPIO_Pin  = Servo_Pin_PWM;
	MyGPIO_Init(&Servo_Struct_Gpio_PWM);
	//init PWM
	Servo_Struct_TIM.Timer= Servo_Timer;
	Servo_Struct_TIM.ARR = Servo_ARR;
	Servo_Struct_TIM.PSC = Servo_PSC;
	MyTimer_Base_Init (&Servo_Struct_TIM);
	MyTimer_PWM (Servo_Timer, Servo_tim_channel );
	Cycle_PWM (Servo_Timer, 5 , Servo_tim_channel);
	MyTimer_Base_Start(Servo_Timer);
}

int main(void){
	initServo();
	while (1){
	}
}

