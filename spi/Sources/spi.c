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
#include "MySPI.h"
#include "spi.h"

MyGPIO_Struct_TypeDef spi_GPIO_struct;
char datax1;
char datax2;
char datay1;
char datay2;
char dataz1;
char dataz2;


short int s_i_x;
short int s_i_y;
short int s_i_z;
double gx;
double gy;
double gz;

char spi_byte;
void spi_accelero_init(void){
	//initGestionPlateau gpio
	//init bus spi
	MySPI_Init(SPI2);
	//configuration regsiteres acelerometres
	MySPI_Set_NSS();
	//power ctl
	MySPI_Clear_NSS();
	spi_byte = 0x2D;
	MySPI_Send(spi_byte);
	spi_byte=8;
	MySPI_Send(spi_byte); //unbiquement le bit measure à 1 tout le reste à 0
	MySPI_Set_NSS();
	//BWD rate
	MySPI_Clear_NSS();
	spi_byte = 0x2C;
	MySPI_Send(spi_byte);
	spi_byte=0xA;
	MySPI_Send(spi_byte); //set le bwd rate bà 100Hz
	MySPI_Set_NSS();
	//Data Format
	MySPI_Clear_NSS();
	spi_byte = 0x31;
	MySPI_Send(spi_byte);
	spi_byte=0xB;
	MySPI_Send(spi_byte); //setup dataformat
	MySPI_Set_NSS();
	datax1 =  0;
	datax2 =  0;
	datay1 =  0;
	datay2 = 0;
	dataz1 =  0;
	dataz2 = 0;
}

void lecture_data_accelero(void){
	MySPI_Clear_NSS();
	spi_byte= (3<<6) + 0x32;
	MySPI_Send(spi_byte); //send 11 + adresse 50
	datax1 =  MySPI_Read();
	datax2 =  MySPI_Read();
	datay1 =  MySPI_Read();
	datay2 =  MySPI_Read();
	dataz1 =  MySPI_Read();
	dataz2 =  MySPI_Read();
	MySPI_Set_NSS();
	
}
void convert(void){
	s_i_x = datax1 + (datax2<<8);
	gx = s_i_x * 0.004;
	s_i_y = datay1 + (datay2<<8);
	gy = s_i_y * 0.004;
	s_i_z = dataz1 + (dataz2<<8);
	gz = s_i_z * 0.004;
}

void check_roulis(void){
	lecture_data_accelero();
		convert();
	if ((gy > 0.5)){
		Cycle_PWM (Servo_Timer, 500 , Servo_tim_channel);
	}
}
