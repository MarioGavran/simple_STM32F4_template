#include "stm32f413xx.h"

static const int a=7;
int z=8;
static int sum;

void main(void)
{
	int var=0x10;
	sum = var+a+z;
	sum = a+z+3;

	RCC->AHB1ENR	|=	RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER	&=	~GPIO_MODER_MODER7;
	GPIOB->MODER	|=	GPIO_MODER_MODER7_0;
	GPIOB->ODR	|=	GPIO_ODR_ODR_7;

	while(1)
	{
		z++;
		if(z >= 800000)
		{
			z = 0;
			GPIOB->ODR	^=	GPIO_ODR_ODR_7;
		}
	}
}

