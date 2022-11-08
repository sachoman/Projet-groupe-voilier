#include "usart.h"
#include "rotation-plateau.h"
#include "stm32f10x.h"

char g_p_c;
int g_p_i;

void receptionDonnees(){
	g_p_c= usart_getValue();
	g_p_i= (int)g_p_c;
	if (g_p_i > 128){
		//droite
		g_p_i = (256 - g_p_i);
		tourneDroite(g_p_i);
	}
	else{
		tourneGauche(g_p_i);
	}
}

void initGestionPlateau(){
	usart_configure_1_9600bps();
	usart_1_configure_IT(receptionDonnees, 2);
	initPlateau();
}

int main(void){
	initGestionPlateau();
	while (1){
	}
}
