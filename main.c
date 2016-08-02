
/* 
 * Serial: serial i/o routines for the STM32L011
*/


#include "stm32l011.h"
#include "serial.h"
void delay(int);

void delay(int dly)
{
  while( dly--);
}

void initClockHSI16()
{
    // Use the HSI16 clock as the system clock - allows operation down to 1.5V
        RCC_CR &= ~BIT24;
        RCC_CR |= BIT0; // turn on HSI16 (16MHz clock)
        while ((RCC_CR & BIT2)==0); // wait for HSI to be ready
        // set HSI16 as system clock source 
        RCC_CFGR |= BIT0;
}
void configPins()
{
	// Enable PORTB where LED is connected
	RCC_IOPENR |= BIT1;
	GPIOB_MODER |= BIT6; // make bit3  an output
	GPIOB_MODER &= ~BIT7; // make bit3  an output
}	

int main()
{
        uint32_t Counter=0;
	initClockHSI16();
	configPins(); 
        initUART(9600);
	
	while(1)
	{
		GPIOB_ODR |= BIT3;
		delay(2000000);
		GPIOB_ODR &= ~BIT3;
		delay(2000000);
                printHex(bytesAvailable());
                eputs("\r\n");                
	} 
	return 0;
}








