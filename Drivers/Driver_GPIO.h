#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"
typedef struct
{
GPIO_TypeDef * GPIO ;
char GPIO_Pin ; // numero de 0 a 15
char GPIO_Conf ; // voir ci dessous
} MyGPIO_Struct_TypeDef ;
#define In_Floating 0x4
#define In_PullDown 0x8 //a voir
#define In_PullUp 0xC //a voir
#define In_Analog 0x0 
#define Out_Ppull 0x1 //2 ou 3 en fct fréquence 10 (défaut) 2 ou 50 mHz
#define Out_OD 0x5 //6 ou 7 pareil
#define AltOut_Ppull 0x9 // A ou B pareil
#define AltOut_OD 0xD // E ou F pareil
void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) ;
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ; // r e n v o i e 0 ou a u t r e chose d i f f e r e n t de 0
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
#endif
