/*******************************************************************************************************************************
LIBRARY:	FSMC_NT35510.c
			- only for STM32F413ZHT6 devices.
			- 
				
AUTHOR: 	Mario Gavran, E5029604, 
INSTITUTION:	University of Maribor - FERI
DATE:		feb 28.2020
*******************************************************************************************************************************/
#include "./Include/stm32f4xx.h"			// STM32F413 Device header.
#include "FSMC_NT35510.h"		// NT35510 header.
#include <stdlib.h>			// Standard library header.
#include <stdint.h>			// Standard integers header file.
#include "STM32F413_System.h"		// STM32F413 System functions.

FSMC_LCD_TypeDef* LCD_FSMC = (FSMC_LCD_TypeDef*)0x6001FFFEU;		// Definition of 



/*******************************************************************************************************************************
* name       :FSMC_GPIO_init
* date       :May 9.2020
* function   :Initialize GPIO pins used with FSMC peripheral.
* parameters :N/A
* retvalue   :N/A
*******************************************************************************************************************************/
void FSMC_GPIO_Init(void)
{
	// Enable clock on all ports used with FSMC
	RCC->AHB1ENR	|= RCC_AHB1ENR_GPIOBEN
			  |RCC_AHB1ENR_GPIOCEN
			  |RCC_AHB1ENR_GPIODEN
			  |RCC_AHB1ENR_GPIOEEN;

	//mode out - 01
	GPIOC->MODER	|= GPIO_MODER_MODER6_0;			// PC6  - RST
	//mode af  - 10
	GPIOD->MODER	|= GPIO_MODER_MODER11_1			// PD11 - A[16]	- RS
			  |GPIO_MODER_MODER4_1			// PD4  - NOE   - RD
			  |GPIO_MODER_MODER5_1			// PD5  - NWE   - WR
			  |GPIO_MODER_MODER7_1			// PD7  - NE1 	- CS
			  |GPIO_MODER_MODER14_1			// PD14 - D0
			  |GPIO_MODER_MODER15_1;		// PD15 - D1
	
	GPIOC->MODER	&= ~(GPIO_MODER_MODER11_Msk
			    |GPIO_MODER_MODER12_Msk);// clear before setting
	GPIOC->MODER	|=   GPIO_MODER_MODER11_1		// PC11 - D2
			    |GPIO_MODER_MODER12_1;		// PC12 - D3
	GPIOE->MODER	|=   GPIO_MODER_MODER7_1		// PE7  - D4
			    |GPIO_MODER_MODER8_1		// PE8  - D5
			    |GPIO_MODER_MODER9_1		// PE9  - D6
			    |GPIO_MODER_MODER10_1		// PE10 - D7
			    |GPIO_MODER_MODER11_1		// PE11 - D8
			    |GPIO_MODER_MODER12_1		// PE12 - D9
			    |GPIO_MODER_MODER13_1		// PE13 - D10
			    |GPIO_MODER_MODER14_1		// PE14 - D11
			    |GPIO_MODER_MODER15_1;		// PE15 - D12
	GPIOB->MODER	|=  GPIO_MODER_MODER12_1;		// PB12 - D13
	GPIOD->MODER	|=  GPIO_MODER_MODER9_1			// PD9  - D14
			   |GPIO_MODER_MODER10_1;		// PD10 - D15
	
	
	//type - PUSH PULL - jel ti treba uopce ?, posto je Reset value: 0x0000 0000
	GPIOC->OTYPER	&= ~(GPIO_OTYPER_OT_6);
	GPIOD->OTYPER	&= ~((GPIO_OTYPER_OT_11)
			    |(GPIO_OTYPER_OT_4)
			    |(GPIO_OTYPER_OT_5)
			    |(GPIO_OTYPER_OT_7)
			    |(GPIO_OTYPER_OT_14)
			    |(GPIO_OTYPER_OT_15));
	GPIOC->OTYPER	&= ~((GPIO_OTYPER_OT_11)
			    |(GPIO_OTYPER_OT_12));
	GPIOE->OTYPER	&= ~((GPIO_OTYPER_OT_7)
			    |(GPIO_OTYPER_OT_8)
			    |(GPIO_OTYPER_OT_9)
			    |(GPIO_OTYPER_OT_10)
			    |(GPIO_OTYPER_OT_11)
			    |(GPIO_OTYPER_OT_12)
			    |(GPIO_OTYPER_OT_13)
			    |(GPIO_OTYPER_OT_14)
			    |(GPIO_OTYPER_OT_15));
	GPIOB->OTYPER	&=  ~(GPIO_OTYPER_OT_12);
	GPIOD->OTYPER	&= ~((GPIO_OTYPER_OT_9)
			    |(GPIO_OTYPER_OT_10));
	
	// Enable Compensation cell to enable max speed(OSPEEDR = 0b11 or 0b11).
	RCC->APB2ENR	|= RCC_APB2ENR_SYSCFGEN;		// Enable SYSCFG registers.
	SYSCFG->CMPCR	|= SYSCFG_CMPCR_CMP_PD;			// Enable Compensation cell.
	while(!(SYSCFG->CMPCR & SYSCFG_CMPCR_READY));		// Wait for ENABLE flag
	
	//SPEED - FAST
	GPIOC->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR6_1);
	GPIOD->OSPEEDR |= ((GPIO_OSPEEDER_OSPEEDR11_1)
			  |(GPIO_OSPEEDER_OSPEEDR4_1)
			  |(GPIO_OSPEEDER_OSPEEDR5_1)
			  |(GPIO_OSPEEDER_OSPEEDR7_1)
			  |(GPIO_OSPEEDER_OSPEEDR14_1)
			  |(GPIO_OSPEEDER_OSPEEDR15_1));
	GPIOC->OSPEEDR |= ((GPIO_OSPEEDER_OSPEEDR11_1)
			  |(GPIO_OSPEEDER_OSPEEDR12_1));
	GPIOE->OSPEEDR |= ((GPIO_OSPEEDER_OSPEEDR7_1)
			  |(GPIO_OSPEEDER_OSPEEDR8_1)
			  |(GPIO_OSPEEDER_OSPEEDR9_1)
			  |(GPIO_OSPEEDER_OSPEEDR10_1)
			  |(GPIO_OSPEEDER_OSPEEDR11_1)
			  |(GPIO_OSPEEDER_OSPEEDR12_1)
			  |(GPIO_OSPEEDER_OSPEEDR13_1)
			  |(GPIO_OSPEEDER_OSPEEDR14_1)
			  |(GPIO_OSPEEDER_OSPEEDR15_1));
	GPIOB->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR12_1);
	GPIOD->OSPEEDR |= ((GPIO_OSPEEDER_OSPEEDR9_1)
			  |(GPIO_OSPEEDER_OSPEEDR10_1));
	
	
	//NO PULL UP/DOWN - jel ti treba uopce ?, posto je Reset value: 0x0000 0000
	GPIOC->PUPDR	&= ~(GPIO_PUPDR_PUPD6_Msk);
	GPIOD->PUPDR	&= ~((GPIO_PUPDR_PUPD11_Msk)
			    |(GPIO_PUPDR_PUPD4_Msk)
			    |(GPIO_PUPDR_PUPD5_Msk)
			    |(GPIO_PUPDR_PUPD7_Msk)
			    |(GPIO_PUPDR_PUPD14_Msk)
			    |(GPIO_PUPDR_PUPD15_Msk));
	GPIOC->PUPDR	&= ~((GPIO_PUPDR_PUPD11_Msk)
			    |(GPIO_PUPDR_PUPD12_Msk));
	GPIOE->PUPDR	&= ~((GPIO_PUPDR_PUPD7_Msk)
			    |(GPIO_PUPDR_PUPD8_Msk)
			    |(GPIO_PUPDR_PUPD9_Msk)
			    |(GPIO_PUPDR_PUPD10_Msk)
			    |(GPIO_PUPDR_PUPD11_Msk)
			    |(GPIO_PUPDR_PUPD12_Msk)
			    |(GPIO_PUPDR_PUPD13_Msk)
			    |(GPIO_PUPDR_PUPD14_Msk)
			    |(GPIO_PUPDR_PUPD15_Msk));
	GPIOB->PUPDR	&=  ~(GPIO_PUPDR_PUPD12_Msk);
	GPIOD->PUPDR	&= ~((GPIO_PUPDR_PUPD9_Msk)
			    |(GPIO_PUPDR_PUPD10_Msk));
	
	//AF12(0xC) or AF10(0xA)
	GPIOD->AFR[0] |= 0xC0CC0000;
	GPIOD->AFR[1] |= 0xCC00CCC0;	//PD  4,  5,  7, 9, 10, 11, 14, 15
	
	GPIOC->AFR[1] |= 0x000AA000;	//PC 12, 11
	
	GPIOE->AFR[0] |= 0xC0000000;
	GPIOE->AFR[1] |= 0xCCCCCCCC;	//PE 7, 8, 9, 10, 11, 12, 13, 14, 15
	
	GPIOB->AFR[1] |= 0x000C0000;	//PB 12

}



/*******************************************************************************************************************************
* name       :
* date       :
* function   :
* parameters :N/A
* retvalue   :N/A
*******************************************************************************************************************************/
void FSMC_Init(void)
{
	//enable clock on fsmc peripheral
	RCC->AHB3ENR |= RCC_AHB3ENR_FSMCEN;
	
	//FSMC_BCR1  0x00	 BTCR[0]
	FSMC_Bank1->BTCR[0]	|=   FSMC_BCR1_MBKEN;			// Enable BANK1.
	FSMC_Bank1->BTCR[0]	&= ~(FSMC_BCR1_MUXEN);			// Disable MUX.
	FSMC_Bank1->BTCR[0]	&= ~(FSMC_BCR1_MTYP_Msk);
	FSMC_Bank1->BTCR[0]	|=   FSMC_BCR1_MTYP_1; 			// Select NOR Flash memory type. (0x2)
	FSMC_Bank1->BTCR[0]	|=   FSMC_BCR1_MWID_0;
	FSMC_Bank1->BTCR[0]	&= ~(FSMC_BCR1_MWID_1); 		// 16bit width.
	FSMC_Bank1->BTCR[0] 	|=   FSMC_BCR1_FACCEN;			// Enable NOR Flash memory access operations.
	FSMC_Bank1->BTCR[0]	&= ~(FSMC_BCR1_BURSTEN);		// Disable burst mode. Asynchronous read operations.
	FSMC_Bank1->BTCR[0]	|=   FSMC_BCR1_WREN;			// Enable write operations.
	FSMC_Bank1->BTCR[0]	&= ~(FSMC_BCR1_WAITEN);			// Disable NWAIT signal.
	FSMC_Bank1->BTCR[0]	|=   FSMC_BCR1_EXTMOD;			// Enable extended mode. (mode B, enabling BWTR register)
	FSMC_Bank1->BTCR[0]	&= ~(FSMC_BCR1_ASYNCWAIT);		// NWAIT signal is not taken in to account.
	FSMC_Bank1->BTCR[0]	&= ~(FSMC_BCR1_CPSIZE_Msk); 		// No burst split when crossing page boundary.
	FSMC_Bank1->BTCR[0]	&= ~(FSMC_BCR1_CBURSTRW);		// Disable burst mode. Asynchronous write operations.
	FSMC_Bank1->BTCR[0]	&= ~(FSMC_BCR1_CCLKEN);			// Disable continuous clock.
	FSMC_Bank1->BTCR[0]	&= ~(FSMC_BCR1_WFDIS);			// Enable write FIFO.
	
	
	//FSMC_BTR1  0x04	 BTCR[1]  -  Read Cycle
	FSMC_Bank1->BTCR[1]	&= ~(FSMC_BTR1_ACCMOD_Msk);		// ACCMOD (ModeA)
	FSMC_Bank1->BTCR[1]	&= ~(FSMC_BTR1_BUSTURN_Msk);
	FSMC_Bank1->BTCR[1]	|=   FSMC_BTR1_BUSTURN_0;		// BUSTURN 1 HCLK
	FSMC_Bank1->BTCR[1]	&= ~(FSMC_BTR1_DATAST_Msk);
	FSMC_Bank1->BTCR[1]	|=  (FSMC_BTR1_DATAST_0 
				   | FSMC_BTR1_DATAST_2);		// DATAST 5 HCLK = 50ns>45ns
	FSMC_Bank1->BTCR[1]	&= ~(FSMC_BTR1_ADDSET_Msk);
	FSMC_Bank1->BTCR[1]	|=  (FSMC_BTR1_ADDSET_0	
				   | FSMC_BTR1_ADDSET_3);		// ADDSET 9 HCLK = 90ns=90ns
	
	//FSMC_BWTR1 0x00	 BWTR1[0]  -  Write Cycle
	FSMC_Bank1E->BWTR[0]	&= ~(FSMC_BWTR1_ACCMOD_Msk);		// ACCMOD (ModeA)
	FSMC_Bank1E->BWTR[0]	&= ~(FSMC_BWTR1_BUSTURN_Msk);
	FSMC_Bank1E->BWTR[0]	|=   FSMC_BTR1_BUSTURN_0;		// BUSTURN 1 HCLK
	FSMC_Bank1E->BWTR[0]	&= ~(FSMC_BWTR1_DATAST_Msk);
	FSMC_Bank1E->BWTR[0]	|=   FSMC_BWTR1_DATAST_1;		// DATAST 2 HCLK+1 = 30ns>15ns
	FSMC_Bank1E->BWTR[0]	&= ~(FSMC_BWTR1_ADDSET_Msk);
	FSMC_Bank1E->BWTR[0]	|=   FSMC_BWTR1_ADDSET_1;		// ADDSET 2 HCLK = 20ns>15ns
	
}



/*******************************************************************************************************************************
* name       :
* date       :
* function   :
* parameters :
* retvalue   :N/A
*******************************************************************************************************************************/
void FSMC_WR_REG(uint32_t Reg)
{
	LCD_FSMC->REG = Reg;
}



/*******************************************************************************************************************************
* name       :FSMC_WR_DAT
* date       :
* function   :
* parameters :
* retvalue   :N/A
*******************************************************************************************************************************/
void FSMC_WR_DAT(uint16_t Dat)
{
	LCD_FSMC->DAT = Dat;
}



/*******************************************************************************************************************************
* name       :NT35510_Init
* date       :
* function   :
* parameters :N/A
* retvalue   :N/A
*******************************************************************************************************************************/
void NT35510_Init(void)
{
	RST_LOW;								// Reset on.
	Delay_m(300);								// Short delay needed on power up
	RST_HIGH;								// Reset off.
	Delay_m(800);								// Short delay needed on power up
	
	// Manufacture Command Set selection	
	FSMC_WR_REG(MAUCCTR_0);		FSMC_WR_DAT(0x0055U);
	FSMC_WR_REG(MAUCCTR_1);		FSMC_WR_DAT(0x00AAU);
	FSMC_WR_REG(MAUCCTR_2);		FSMC_WR_DAT(0x0052U);
	FSMC_WR_REG(MAUCCTR_3);		FSMC_WR_DAT(0x0008U);			// Enable Manufacture Command Set
	FSMC_WR_REG(MAUCCTR_4);		FSMC_WR_DAT(0x0001U);			// Select page 1
	
	// AVDD 5.2V
	FSMC_WR_REG(SETAVDD_NORM);	FSMC_WR_DAT(0x000DU);
	FSMC_WR_REG(SETAVDD_IDLE);	FSMC_WR_DAT(0x000DU);
	FSMC_WR_REG(SETAVDD_PART);	FSMC_WR_DAT(0x000DU);
	
	// AVDD ratio
	FSMC_WR_REG(BT1CTR_NORM);	FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT1CTR_IDLE);	FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT1CTR_PART);	FSMC_WR_DAT(0x0034U);
	
	// AVEE  -5.2V
	FSMC_WR_REG(SETAVEE_NORM);	FSMC_WR_DAT(0x000DU);
	FSMC_WR_REG(SETAVEE_IDLE);	FSMC_WR_DAT(0x000DU);
	FSMC_WR_REG(SETAVEE_PART);	FSMC_WR_DAT(0x000DU);
	
	// AVEE ratio
	FSMC_WR_REG(BT2CTR_NORM);	FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT2CTR_IDLE);	FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT2CTR_PART);	FSMC_WR_DAT(0x0034U);
	
	// VCL  -2.5V
	FSMC_WR_REG(SETVCL_NORM);	FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(SETVCL_IDLE);	FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(SETVCL_PART);	FSMC_WR_DAT(0x0000U);
	
	// VCL ratio
	FSMC_WR_REG(BT3CTR_NORM);	FSMC_WR_DAT(0x0024U);
	FSMC_WR_REG(BT3CTR_IDLE);	FSMC_WR_DAT(0x0024U);
	FSMC_WR_REG(BT3CTR_PART);	FSMC_WR_DAT(0x0024U);
	
	// VGH  15V
	FSMC_WR_REG(VGHCTR);		FSMC_WR_DAT(0x01);
	FSMC_WR_REG(SETVGH_NORM);	FSMC_WR_DAT(0x000FU);
	FSMC_WR_REG(SETVGH_IDLE);	FSMC_WR_DAT(0x000FU);
	FSMC_WR_REG(SETVGH_PART);	FSMC_WR_DAT(0x000FU);
	
	// VGH  ratio
	FSMC_WR_REG(BT4CTR_NORM);	FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT4CTR_IDLE);	FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT4CTR_PART);	FSMC_WR_DAT(0x0034U);
	
	// VGL_REG  -10V
	FSMC_WR_REG(0xB500);		FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(0xB500);		FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(0xB501);		FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(0xC200);		FSMC_WR_DAT(0x0003U);
	
	// VGLX  ratio
	FSMC_WR_REG(BT5CTR_NORM);	FSMC_WR_DAT(0x0024U);
	FSMC_WR_REG(BT5CTR_IDLE);	FSMC_WR_DAT(0x0024U);
	FSMC_WR_REG(BT5CTR_PART);	FSMC_WR_DAT(0x0024U);
	
	// VGMP/VGSP 4.5V/0V
	FSMC_WR_REG(SETVGP_0);		FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(SETVGP_1);		FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(SETVGP_2);		FSMC_WR_DAT(0x0000U);
	
	// VGMN/VGSN -4.5V/0V
	FSMC_WR_REG(SETVGN_0);		FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(SETVGN_1);		FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(SETVGN_2);		FSMC_WR_DAT(0x0000U);
	
	// VCOM  -1.325V
	FSMC_WR_REG(SETVCMOFF_0);	FSMC_WR_DAT(0x0000);
	FSMC_WR_REG(SETVCMOFF_1);	FSMC_WR_DAT(0x0089);
	
	// Gamma Setting	 
	FSMC_WR_REG(GMRCTR1_BASE | 0x0000U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0001U);FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0002U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0003U);FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0004U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0005U);FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0006U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0007U);FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0008U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0009U);FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000AU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000BU);FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000CU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000DU);FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000EU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000FU);FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0010U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0011U);FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0012U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0013U);FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0014U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0015U);FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0016U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0017U);FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0018U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0019U);FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001BU);FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001DU);FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001FU);FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0020U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0021U);FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0022U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0023U);FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0024U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0025U);FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0026U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0027U);FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0028U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0029U);FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002BU);FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002DU);FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002FU);FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0030U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0031U);FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0032U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0033U);FSMC_WR_DAT(0x007FU);
			
	FSMC_WR_REG(GMGCTR1_BASE | 0x0000U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0001U);FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0002U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0003U);FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0004U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0005U);FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0006U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0007U);FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0008U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0009U);FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000AU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000BU);FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000CU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000DU);FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000EU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000FU);FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0010U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0011U);FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0012U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0013U);FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0014U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0015U);FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0016U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0017U);FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0018U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0019U);FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001BU);FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001DU);FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001FU);FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0020U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0021U);FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0022U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0023U);FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0024U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0025U);FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0026U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0027U);FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0028U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0029U);FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002BU);FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002DU);FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002FU);FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0030U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0031U);FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0032U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0033U);FSMC_WR_DAT(0x007FU);
		
	FSMC_WR_REG(GMBCTR1_BASE | 0x0000U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0001U);FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0002U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0003U);FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0004U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0005U);FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0006U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0007U);FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0008U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0009U);FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000AU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000BU);FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000CU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000DU);FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000EU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000FU);FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0010U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0011U);FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0012U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0013U);FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0014U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0015U);FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0016U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0017U);FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0018U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0019U);FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001BU);FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001DU);FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001FU);FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0020U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0021U);FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0022U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0023U);FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0024U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0025U);FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0026U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0027U);FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0028U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0029U);FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002BU);FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002DU);FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002FU);FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0030U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0031U);FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0032U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0033U);FSMC_WR_DAT(0x007FU);
		
	FSMC_WR_REG(GMRCTR2_BASE | 0x0000U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0001U);FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0002U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0003U);FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0004U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0005U);FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0006U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0007U);FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0008U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0009U);FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000AU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000BU);FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000CU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000DU);FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000EU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000FU);FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0010U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0011U);FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0012U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0013U);FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0014U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0015U);FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0016U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0017U);FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0018U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0019U);FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001BU);FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001DU);FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001FU);FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0020U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0021U);FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0022U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0023U);FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0024U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0025U);FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0026U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0027U);FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0028U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0029U);FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002BU);FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002DU);FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002FU);FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0030U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0031U);FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0032U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0033U);FSMC_WR_DAT(0x007FU);
		
	FSMC_WR_REG(GMGCTR2_BASE | 0x0000U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0001U);FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0002U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0003U);FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0004U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0005U);FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0006U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0007U);FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0008U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0009U);FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000AU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000BU);FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000CU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000DU);FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000EU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000FU);FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0010U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0011U);FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0012U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0013U);FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0014U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0015U);FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0016U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0017U);FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0018U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0019U);FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001BU);FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001DU);FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001FU);FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0020U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0021U);FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0022U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0023U);FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0024U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0025U);FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0026U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0027U);FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0028U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0029U);FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002BU);FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002DU);FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002FU);FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0030U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0031U);FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0032U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0033U);FSMC_WR_DAT(0x007FU);
		
	FSMC_WR_REG(GMBCTR2_BASE | 0x0000U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0001U);FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0002U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0003U);FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0004U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0005U);FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0006U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0007U);FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0008U);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0009U);FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000AU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000BU);FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000CU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000DU);FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000EU);FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000FU);FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0010U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0011U);FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0012U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0013U);FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0014U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0015U);FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0016U);FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0017U);FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0018U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0019U);FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001BU);FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001DU);FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001FU);FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0020U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0021U);FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0022U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0023U);FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0024U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0025U);FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0026U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0027U);FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0028U);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0029U);FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002AU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002BU);FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002CU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002DU);FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002EU);FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002FU);FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0030U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0031U);FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0032U);FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0033U);FSMC_WR_DAT(0x007FU);
	
	//**************************************************************************************************************************//
	
	// Select Page 0
	FSMC_WR_REG(MAUCCTR_0);		FSMC_WR_DAT(0x0055U);
	FSMC_WR_REG(MAUCCTR_1);		FSMC_WR_DAT(0x00AAU);
	FSMC_WR_REG(MAUCCTR_2);		FSMC_WR_DAT(0x0052U);
	FSMC_WR_REG(MAUCCTR_3);		FSMC_WR_DAT(0x0008U);		// Enable Manufacture Command Set
	FSMC_WR_REG(MAUCCTR_4);		FSMC_WR_DAT(0x0000U);		// Select page 0
	
	// DISPLAY CONTROL
	FSMC_WR_REG(DOPCTR_0);		FSMC_WR_DAT(0x00CCU);
	FSMC_WR_REG(DOPCTR_1);		FSMC_WR_DAT(0x0000U);
	
	FSMC_WR_REG(DPRSLCTR);		FSMC_WR_DAT(0x0050U);			// Display Resolution 480RGB x 800
		
	// SOURCE HOLD TIME
	FSMC_WR_REG(SDHDTCTR);		FSMC_WR_DAT(0x0005U);
	
	// Set Gate EQ
	FSMC_WR_REG(GSEQCTR_ST);	FSMC_WR_DAT(0x0070U);
	FSMC_WR_REG(GSEQCTR_CK);	FSMC_WR_DAT(0x0070U);
	
	// Source EQ control (Mode 2)
	FSMC_WR_REG(SDEQCTR_MOD );	FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(SDEQCTR_EQS1);	FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(SDEQCTR_EQS2);	FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(SDEQCTR_EQS3);	FSMC_WR_DAT(0x0003U);
	
	// INVERSION MODE
	FSMC_WR_REG(INVCTR_NORM);	FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(INVCTR_IDLE);	FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(INVCTR_PART);	FSMC_WR_DAT(0x0000U);
	
	// Timing control
	FSMC_WR_REG(0xC900);		FSMC_WR_DAT(0x00D0U);
	FSMC_WR_REG(0xC901);		FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(0xC902);		FSMC_WR_DAT(0x0050U);
	FSMC_WR_REG(0xC903);		FSMC_WR_DAT(0x0050U);
	FSMC_WR_REG(0xC904);		FSMC_WR_DAT(0x0050U);
  
	//************************************************************************************************************************
	// User Command Set
	FSMC_WR_REG(TEON);   		FSMC_WR_DAT(0x0000U);		// V-Blanking information only
	
	FSMC_WR_REG(COLMOD);   		FSMC_WR_DAT(0x0055U);		// RGB and MCU Interface Data format 16-Bits
	FSMC_WR_REG(MADCTL);		FSMC_WR_DAT(0x0000U);		// MADCTL: MY MX MV RGB MH RSMX RSMY
	
	FSMC_WR_REG(SLPOUT);   						// Sleep Out  
	
	Delay_m(120);
	
	FSMC_WR_REG(DISPON);   						// Display On  
  	Delay_m(200);
	 
	LCD_SetDirection(VERTICAL_UP);		// Vertical-up display orientation as default
}



/*******************************************************************************************************************************
* name		:LCD_SetWindow
* date		:May 10.2020
* function	:Defines accesible area in frame memory that MCU can access. The function is used in
		 LCD_SetDirection function. It calls to FSMC_WR_REG(RAMWR) function at the end.
* parameters	:XS(x start address), YS(y start address), XE(x end address) and YE(y end address)
* retvalue	:N/A
*******************************************************************************************************************************/
void LCD_SetWindow(uint16_t Xs, uint16_t Ys, uint16_t Xe, uint16_t Ye)
{	
	FSMC_WR_REG(CASET_XS_H);	FSMC_WR_DAT(Xs>>8);  
	FSMC_WR_REG(CASET_XS_L);	FSMC_WR_DAT(Xs&0x00FFU);	  
	FSMC_WR_REG(CASET_XE_H);	FSMC_WR_DAT(Xe>>8);   
	FSMC_WR_REG(CASET_XE_L);	FSMC_WR_DAT(Xe&0x00FFU);   
	FSMC_WR_REG(RASET_YS_H);	FSMC_WR_DAT(Ys>>8);   
	FSMC_WR_REG(RASET_YS_L);	FSMC_WR_DAT(Ys&0x00FFU);  
	FSMC_WR_REG(RASET_YE_H);	FSMC_WR_DAT(Ye>>8);   
	FSMC_WR_REG(RASET_YE_L);	FSMC_WR_DAT(Ye&0x00FFU); 
	
	FSMC_WR_REG(RAMWR);
}


/*******************************************************************************************************************************
* name		:LCD_SetDirection
* date		:May 10.2020
* function	:The function sets the desired orientation direction and than defines accessable area
		 of the frame memory. The x and y axis change according to selected orientation 
		 direction, hance the defined accessible frame memory area must be changed to support
		 the selected orientation.
* parameters	:Direction(Use Orientation Direction Definitions defined in FSMC_NT35510.h)
* retvalue	:N/A
*******************************************************************************************************************************/
void LCD_SetDirection(uint8_t Direction)
{
	switch(Direction)
	{
		case 0:
			FSMC_WR_REG(MADCTL); FSMC_WR_DAT(0x0000U);
			LCD_SetWindow(0,0,479,799);
		break;
		case 1:
			FSMC_WR_REG(MADCTL); FSMC_WR_DAT(0x00C0U);
			LCD_SetWindow(0,0,479,799);
		break;
		case 2:
			FSMC_WR_REG(MADCTL); FSMC_WR_DAT(0x0060U);
			LCD_SetWindow(0,0,799,479);
		break;
		case 3:
			FSMC_WR_REG(MADCTL); FSMC_WR_DAT(0x00A0U);
			LCD_SetWindow(0,0,799,479);
		break;
	}
}


/*******************************************************************************************************************************
* name		:LCD_Clear
* date		:May 10.2020
* function	:Rewrite the whole screen with a single color. Does not require
		 LCD_SetWindow function call to set accesible frame memory area, because it clears
		 the whole screen, which is already defined by the LCD_SetDirection function call.
		 LCD_SetDirection function is called during LCD initialization and after every 
		 orientation direction change.
* parameters	:Color(Desired screen color)
* retvalue	:N/A
*******************************************************************************************************************************/
void LCD_ClearScreen(uint16_t Color)
{
  uint32_t i;
	
	for(i=0;i<(480*800);i++)
	{
		FSMC_WR_DAT(Color);
	}
}


/*******************************************************************************************************************************
* name		:LCD_ClearArea
* date		:May 10.2020
* function	:Rewrite defined accesible frame memory area with a single color. It calls to 
		 LCD_SetWindow function to set the accesible frame memory area, because it clears
		 only the desired screen area. Does not need to call FSMC_WR_REG(RAMWR) because it
		 is allready called by the LCD_SetWindow function call.
* parameters	:Xs(x start address), Ys(y start address), Xe(x end address), Ye(y end address) and 
		 Color(Desired area color)
* retvalue	:N/A
*******************************************************************************************************************************/
void LCD_ClearArea(uint16_t Xs, uint16_t Ys, uint16_t Xe, uint16_t Ye, uint16_t Color)
{
  uint32_t i;
	LCD_SetWindow(Xs,Ys,Xe,Ye);
	FSMC_WR_REG(RAMWR);
	for(i=0;i<((Xe-Xs)*(Ye-Ys)-1);i++)
	{
		FSMC_WR_DAT(Color);
	}
}


/*******************************************************************************************************************************
* name		:LCD_DrawPoint
* date		:May 10.2020
* function	:Prints point on the screen. Does not need to call FSMC_WR_REG(RAMWR) because it is
		 allready called by the LCD_SetWindow function call.
* parameters	:X(x address of the center of the point), Y(y address of the center of the point)
		 Color(point color), Size(point size)
* retvalue   	:N/A
*******************************************************************************************************************************/
void LCD_DrawPoint(uint16_t X, uint16_t Y, uint16_t Color, uint8_t Size)
{
  uint32_t i;
	LCD_SetWindow(X, Y, X+(Size-1),Y+(Size-1));
	for(i=0;i<(Size)*(Size);i++)
	{
		FSMC_WR_DAT(Color);
	}
}


/*******************************************************************************************************************************
* name		:LCD_DrawLine
* date		:May 10.2020
* function	:
* parameters	:Xs(x start address), Ys(y start address), Xe(x end address), Ye(y end address), Color(line color), Size(line size)
* retvalue	:N/A
*******************************************************************************************************************************/
void LCD_DrawLine(uint16_t Xs, uint16_t Ys, uint16_t Xe, uint16_t Ye, uint16_t Color, uint8_t Size)
{
	int16_t	deltaX = Xe - Xs;
	if(deltaX<0)deltaX=deltaX*(-1);
	
	int16_t	deltaY = Ye - Ys;
	if(deltaY<0)deltaX=deltaY*(-1);
	
	int8_t		signX = (Xs < Xe) ? (1) : (-1);
	int8_t		signY = (Ys < Ye) ? (1) : (-1);
	int16_t		error	= deltaX - deltaY;
	
	for (;;)
	{
		LCD_DrawPoint(Xs,Ys,Color,Size);
		
		if(Xs == Xe && Ys == Ye)
		break;
		
		int16_t error2 = error;
		
		if(error2 > -deltaY)
		{
			error -= deltaY;
			Xs += signX;
		}
		
		if(error2 < deltaX)
		{
			error += deltaX;
			Ys += signY;
		}
	}
}


/*******************************************************************************************************************************
* name		:LCD_PrintCh
* date		:May 10.2020
* function	:Prints character on the display. Uses the ASCIItable 2D array defined in the 
		 FSMC_NT35510.h file to represent text characters.
* parameters	:X(x start address), Y(y start address), Color(character color), Bcolor(background
		 color), Character(use standard ASCII values for characters) and Size(characters size)
* retvalue	:N/A
********************************************************************************************************************************/
void LCD_PrintCh(uint16_t X, uint16_t Y, uint16_t Color, uint16_t Bcolor, uint8_t Character, uint8_t Size)
{
	uint8_t i,j,k,p=0;
	uint16_t c=0;
	LCD_SetWindow(X,Y,X+(8*Size-1),Y+(8*Size-1));		// Define area by character size.
	
	for(i=0;i<8;i++)					// 8 row-loops because there are 8 row-bytes per character.
	{
		for(j=0;j<Size;j++)				// Print each row size times.
		{
			for(k=0;k<8;k++)			// 8 column-loops because there are 8 column-bits per row-byte
			{
				if((ASCIItable[Character][i]>>(7-k)) & 0x01)	c=Color;
				else c=Bcolor;
				for(p=0;p<Size;p++)		// Print each column-bit size times.
				{
					FSMC_WR_DAT(c);
				}
			}
		}
	}
}


/********************************************************************************************************************************
* name		:LCD_PrintStr
* date		:May 10.2020
* function	:Prints string of text using LCD_PrintCh function.
* parameters	:x(x start address), y(y start address), color(character color), bcolor(background
		 color), string(pointer to an array of characters, standard ASCII values) and size
		 (character size)
* retvalue	:N/A
********************************************************************************************************************************/
void LCD_PrintStr(uint16_t X, uint16_t Y, uint16_t Color, uint16_t Bcolor, uint8_t* String, uint8_t Size)
{
	X=X-8*Size;
	while(*String) LCD_PrintCh(X=X+8*Size, Y, Color, Bcolor, *String++, Size);
}

