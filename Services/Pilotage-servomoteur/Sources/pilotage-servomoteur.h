#ifndef PilotageServoH
#define PilotageServoH
#include "stm32f10x.h"

#define Servo_Gpio_PWM GPIOB
#define Servo_Pin_PWM 6
#define Servo_ARR 48000
#define Servo_PSC 30
#define Servo_Timer TIM4
#define Servo_tim_channel 1

void initServo(void);
#endif
