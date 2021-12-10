#include "./Include/stm32f4xx.h"                  // Device header
#include <stdint.h>
#include <math.h>
#include "STM32F413_System.h"
#include "FSMC_NT35510.h"

#define pi 3.1415

int main(void)
{
	
	
	PLL_Config();
	SCO_config();
	
	FSMC_GPIO_Init();
	FSMC_Init();
	NT35510_Init();
	
	LCD_ClearScreen(0x7FFFU);
	LCD_SetDirection(HORIZONTAL_RIGHT);
	LCD_ClearScreen(0X841FU);
	
	// Draw frame:
	LCD_DrawLine(10, 10, 790, 10, 0xFC07U,3);
	LCD_DrawLine(10, 10, 10, 470, 0xFC07U,3);
	LCD_DrawLine(790, 10, 790, 470, 0xFC07U,3);
	LCD_DrawLine(10, 470, 790, 470, 0xFC07U,3);
	// Draw axis:
	LCD_DrawLine(10, 230, 790, 230, 0xFC07U,2);
	LCD_DrawLine(390, 10, 390, 470, 0xFC07U,2);
	
	int N = 780;
	float signal[780] = {0.0f};

	for (int n = 0; n < N; n++)
	{
		signal[n] = 35 * sin((4 * (2*pi)/N) * n) +
			    20 * sin((9 * (2*pi)/N) * n);
		LCD_DrawPoint(10 + n, -signal[n] + 240, 0xF81FU, 5);
	}
	
	while(1)
	{
		
	}
}


