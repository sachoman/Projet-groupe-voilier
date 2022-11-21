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

extern int compteursystick;
void systick_fun (void);

int main(void){
		spi_accelero_init();
	Systick_ActiveIT(systick_fun);
	systick_Init(20);
	initGestionPlateau();
	initGestionVoile();
	initServo();


	
	while(1){
	}
}

void systick_fun (void){
	if (compteursystick % 5 == 0){
		//100ms
		voilegestion();
		
	}
	if (compteursystick % 150 == 0){
		// 3s 
		/*char anglevoilier1[] = "L'angle du voilier est de ";
		char anglevoilier2[10];
		char allurevoilier1[] = "L'allure du voilier est : ";
		char* allurevoilier2;
		sprintf(anglevoilier2,"%d",getAngle());
		usart_1_send_string(strcat(anglevoilier1,anglevoilier2),strlen(anglevoilier1));
		// on a l'angle on essaie de récupérer l'allure ! 
		allurevoilier2 = VoileGetAllure();
		usart_1_send_string(strcat(allurevoilier1,allurevoilier2),strlen(allurevoilier1));*/
	}
	//20ms
	receptionDonnees();
	check_roulis();
	compteursystick++;
}
