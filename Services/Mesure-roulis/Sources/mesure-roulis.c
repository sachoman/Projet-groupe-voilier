#include "usart.h"
#include "timer.h"
#include "MyI2C.h"
#include "Driver_Gpio.h"
#include "mesure-roulis.h"
#include "stm32f10x.h"
MyI2C_RecSendData_Typedef MR_struct;
char SlaveAdresse;
char * MR_tab;
char MR_nb_data;

void Callbackerr(void){
}


void initMesureRoulis(void){
	SlaveAdresse = I2C_OAR1;
	MyI2C_Init(I2C1, 2,Callbackerr);
}


int main(void){
	while (1){
	}
}
