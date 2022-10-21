

    #include "stm32f10x.h"
    #include "Driver_GPIO.h"
     
    volatile uint32_t * regcr;
    /*
    void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
            if (GPIOStructPtr->GPIO == GPIOA) {
                RCC->APB2ENR = RCC_APB2ENR_IOPAEN;
            }
            else if (GPIOStructPtr->GPIO == GPIOB) {
                RCC->APB2ENR = RCC_APB2ENR_IOPBEN;
            }
            else if (GPIOStructPtr->GPIO == GPIOC) {
                RCC->APB2ENR = RCC_APB2ENR_IOPCEN;
            }
            else if (GPIOStructPtr->GPIO == GPIOD) {
                RCC->APB2ENR = RCC_APB2ENR_IOPDEN;
            }
            else if (GPIOStructPtr->GPIO == GPIOE) {
                RCC->APB2ENR = RCC_APB2ENR_IOPEEN;
            }
            else{
            }
            if (GPIOStructPtr->GPIO_Pin < 8) {
                GPIOStructPtr->GPIO->CRL &= (~(0xF << GPIOStructPtr->GPIO_Pin*4));
                GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << GPIOStructPtr->GPIO_Pin*4);
            }
            else{
                GPIOStructPtr->GPIO->CRH &= (~(0xF << (((GPIOStructPtr->GPIO_Pin)%8)*4)));
                GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << (((GPIOStructPtr->GPIO_Pin)%8)*4));
            }
    }
    */
    void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
        GPIO_TypeDef * GPIO = GPIOStructPtr->GPIO;
        char GPIO_pin = GPIOStructPtr->GPIO_Pin;
        char GPIO_Conf = GPIOStructPtr->GPIO_Conf;
        if (GPIO == GPIOA) {
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN  ;
        }
        if (GPIO == GPIOB) {
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;
        }
        if (GPIO == GPIOC) {
            RCC->APB2ENR |=RCC_APB2ENR_IOPCEN ;
        }
        if (GPIO_pin > 0x7){
            regcr =  &(GPIO->CRH);
        }
        else{
            regcr =  &(GPIO->CRL);
        }
        * regcr &= ~(0xF<<(GPIO_pin%8*4));
        switch (GPIO_Conf){
            case In_PullDown :  
                     * regcr |= (0x8<<(GPIO_pin%8)*4);
                     MyGPIO_Reset(GPIOStructPtr->GPIO, GPIOStructPtr->GPIO_Pin);
            break;
            case In_PullUp :
                     *regcr |= (0x8<<(GPIO_pin%8)*4);
                     MyGPIO_Set(GPIOStructPtr->GPIO, GPIOStructPtr->GPIO_Pin);
            break;
            default:
                     *regcr |= (GPIO_Conf<<(GPIO_pin%8)*4);
            break;
        }
        //diff odr 0 -> pull down, 1-> pull up
    }
    int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
        return (GPIO->IDR&(1<<GPIO_Pin));
    }
    void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
          GPIO->ODR |= (0x1 << GPIO_Pin);
    }
     
    void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
            GPIO->ODR &= ~(1 << GPIO_Pin);
    }
     
    void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
        GPIO->ODR ^= (0x1 << GPIO_Pin);
    }

