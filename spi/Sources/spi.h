#ifndef spih
#define spih
#include "stm32f10x.h"



#define SPI_accelero SPI2;
#define GPIO_spi_cs GPIOC
#define PIN_spi_cs 3
void lecture_data_accelero(void);


#endif
