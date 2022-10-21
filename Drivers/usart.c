#include "stm32f10x.h"
#include "usart.h"

//registre USART1 Rx= PA10
//Usart1 TX = PA9

void configure_usart1_9600bps(){
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Validation horloge
    USART1->CR1 |= USART_CR1_UE; // Activation
    USART1->CR1 &= ~USART_CR1_M; // Taille de 8 bits de données
    USART1->CR2 &= USART_CR2_STOP; // Choix d'un seul bit de stop
    USART1->BRR |= 468 << 4; // Mantisse register à 468 -> 9600 baud rate
    USART1->BRR |= 75; // Fraction register à 75 -> 9600 baud rate
    USART1->CR1 |= USART_CR1_TE; // Transmitter enable
}

void send(char data){
    USART1->DR |= data; // Ecriture de la donnée dans le registre DR
    while(!(USART1->SR & USART_SR_TC)) {} // Attente de la fin de transmission
}