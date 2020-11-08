#include "STM32F413_System.h"

/********************************************************************************************************************/
void PLL_Config(void)
{
	RCC->CR		|= RCC_CR_HSION;						// HSI enable.
	while((RCC->CR & RCC_CR_HSIRDY) != (RCC_CR_HSIRDY));				// Wait for stable HSI.
	
	RCC->CR		&= ~(RCC_CR_PLLON);						// Disable main-PLL.
	
	RCC->APB1ENR	|= RCC_APB1ENR_PWREN;
	PWR->CR		&= ~(PWR_CR_VOS);
	PWR->CR		|= PWR_CR_VOS;							// Scale 1 mode(0x11) <= 100 MHz.
	
	FLASH->ACR	&= ~(FLASH_ACR_LATENCY);
	FLASH->ACR	|= FLASH_ACR_LATENCY_5WS;					// Set LATENCY.
	while((FLASH->ACR & FLASH_ACR_LATENCY) != (FLASH_ACR_LATENCY_5WS));		// Check LATENCY.
	FLASH->ACR	|= (FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN);
	
	// Configuration of factors M, P, Q, N and PLL source.
	RCC->PLLCFGR	&= ~(RCC_PLLCFGR_PLLSRC);		// HSI as PLL source.
	RCC->PLLCFGR	&= ~(RCC_PLLCFGR_PLLM);
	RCC->PLLCFGR	|= (8U<<RCC_PLLCFGR_PLLM_Pos);		// M=8
	RCC->PLLCFGR	&= ~(RCC_PLLCFGR_PLLN);
	RCC->PLLCFGR	|= (200U<<RCC_PLLCFGR_PLLN_Pos);	// N=200
	RCC->PLLCFGR	&= ~(RCC_PLLCFGR_PLLP);
	RCC->PLLCFGR	|= (0x01U<<RCC_PLLCFGR_PLLP_Pos);	// P=4
	RCC->PLLCFGR	&= ~(RCC_PLLCFGR_PLLQ);
	RCC->PLLCFGR	|= (9U<<RCC_PLLCFGR_PLLQ_Pos);		// Q=8
	
	RCC->CR		|= RCC_CR_PLLON;			// Enable main-PLL.
	while((RCC->CR & RCC_CR_PLLRDY) != (RCC_CR_PLLRDY));	// Wait for PLL lock.
	while((PWR->CSR & PWR_CSR_VOSRDY) != (PWR_CSR_VOSRDY));	// Wait for VOSRDY.
	
	RCC->CFGR	&= ~(RCC_CFGR_PPRE1);
	RCC->CFGR	|= (RCC_CFGR_PPRE1_DIV2);		// APB1 50MHz.
	
	RCC->CFGR	&= ~(RCC_CFGR_SW);
	RCC->CFGR	|= (RCC_CFGR_SW_PLL);			// System clock source switch to PLL.
	while((RCC->CFGR & RCC_CFGR_SWS) != (RCC_CFGR_SWS_PLL));
}



/********************************************************************************************************************/
void SCO_config(void)
{
		// Clock initialization for USART1 peripheral and GPIO pins:
	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;			// Enable PORTA
	
	GPIOC->MODER	|= GPIO_MODER_MODER9_1;			// Set PC9 as AF.
	GPIOC->MODER	&= ~(GPIO_MODER_MODER9_0);		// Set PC9 as AF.
	
	GPIOC ->AFR[1]	&= ~(GPIO_AFRH_AFSEL9);			// Turn on AF0 on PC9.(MCO2)
					
	RCC->CFGR	&= ~(RCC_CFGR_MCO2_Msk);		// System clock (SYSCLK) selected.
	RCC->CFGR	|= RCC_CFGR_MCO2PRE_Msk;		// No prescaler.
}



/*Delay function*/
/********************************************************************************************************************/
void Delay_m(uint32_t ms) 
{
	uint32_t i=0;
	while(i<=(ms*100000)){
		i++;
	}
	i=0;
}

