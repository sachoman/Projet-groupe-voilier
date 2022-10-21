#ifndef timerh
#define timerh
#include "stm32f10x.h"
typedef struct
{
TIM_TypeDef * Timer ; // TIM1 à TIM4
unsigned short ARR ;
unsigned short PSC ;
} MyTimer_Struct_TypeDef ;
/*
*****************************************************************************************
* @brief
* @param -> Paramè t r e sous forme d ’ une s t r u c t u r e ( son a d r e s s e ) c o n t e n a n t l e s
i n f o r m a t i o n s de base
* @Note -> F o n c t i o n à l a n c e r s y s t é matiquement avant d ’ a l l e r p l u s en dé t a i l dans l e s
c o n f p l u s f i n e s (PWM, codeur i n c . . . )
*************************************************************************************************
*/
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ) ;
void MyTimer_ActiveIT ( MyTimer_Struct_TypeDef * Timer , char Prio, void (*IT_function) (void) ) ;
#define MyTimer_Base_Start(Timer) (Timer->CR1|= TIM_CR1_CEN) //CEN counter enable
#define MyTimer_Base_Stop ( Timer ) (Timer->CR1 &= ~TIM_CR1_CEN)) //CEN ocunter disbale


/* *
* @brief
* @param . . . .
* @Note A c t i v e l e channel sp é c i f i é suTimerr l e t i m e r sp é c i f i é
* l a g e s t i o n de l a c o n f i g u r a t i o n I /O n ’ e s t pas f a i t e dans c e t t e f o n c t i o n
* n i l e r é g l a g e de l a pé r i o d e de l a PWM (ARR , PSC )
*/
void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) ;
void Cycle_PWM(TIM_TypeDef * Timer, int alpha, char channel); 
#endif
