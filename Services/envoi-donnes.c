#include "usart.h"
#include "envoi-donnees.h"


void envoi_angle(int angle){
	usart_1_send_string("test", 4); 
}
