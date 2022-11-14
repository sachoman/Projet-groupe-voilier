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


int main(void){
	initGestionPlateau();
	initGestionVoile();
	initServo();
	usart_1_send('1');
	systick_Init(20);
	while(1){
	}
}
