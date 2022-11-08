#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "usart.h"
char c;
int i;

void usart_handler (){
	
	usart_1_send(usart_getValue());
}

int main(void){
	usart_configure_1_9600bps();
	usart_1_configure_IT(&usart_handler, 2);
	usart_1_send('a');
	while(1){
	}
}
