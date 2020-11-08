#include "./Include/stm32f4xx.h"                  // Device header
#include <stdint.h>
#include "STM32F413_System.h"
#include "FSMC_NT35510.h"

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
	
	
	/*
	__asm{
		LDR x,[__current_pc(),#64]
		MOV x,0x00012345U
		mov x,y
		ADD x,0xC
	}
	*/
	
	while(1)
	{
		
	}
}


