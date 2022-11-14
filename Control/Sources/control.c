#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "girouette.h"
#include "usart.h"
#include "Timer.h"
#include "envoi-donnees.h"
#include "pilotage-servomoteur.h"
#include "gestion-plateau.h"
#include "usart.h"
#include "gestionVoile.h"
#include "systick.h"

extern int compteursystick;

void systick_fun (void){
	if (compteursystick % 5 == 0){
		voilegestion();
		
	}
	if (compteursystick % 150 == 0){
		usart_1_send('C');
		
	}
	receptionDonnees();
	compteursystick++;
}


int main(void){
	initGestionPlateau();
	initGestionVoile();
	initServo();
	usart_1_send('A');
	usart_1_send('A');
	usart_1_send('A');
	usart_1_send('A');

	Systick_ActiveIT(systick_fun);
	systick_Init(20);
	while(1){
	}
}

