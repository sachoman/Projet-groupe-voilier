#ifndef rotationPlateau
#define rotationPlateau
#include "stm32f10x.h"
#define Rot_Gpio_PWM GPIOA
#define Rot_Gpio_sens GPIOA
#define Rot_Pin_PWM 1
#define Rot_Pin_sens 4
#define Rot_ARR 3599
#define Rot_PSC 0
#define Rot_Timer TIM2
#define Rot_tim_channel 2

void initPlateau(void);
void tourneGauche(int vitesse);
void tourneDroite(int vitesse);


#endif
