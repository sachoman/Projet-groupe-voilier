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
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "accelero.h"
#include "batterie.h"

extern int compteursystick;

void systick_fun (void);

int main(void){
	spi_accelero_init();
	Systick_ActiveIT(systick_fun);
	systick_Init(20);
	initGestionPlateau();
	initGestionVoile();
	initServo();
	init_batterie();
	
	while(1){
	}
	
}

void systick_fun (void){
	if (compteursystick % 5 == 0){
		//100ms
		voilegestion();
		
	}
	if (compteursystick % 150 == 0){
		//3s 
		affichage_allure_angle();
		check_batterie();

	}
	//20ms
	receptionDonnees();
	check_roulis();
	compteursystick++;
}
