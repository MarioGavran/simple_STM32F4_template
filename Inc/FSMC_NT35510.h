/************************************************************************************************************
LIBRARY:	FSMC_NT35510.h
			- only for STM32F413ZHT6 devices.
			- declares all the functions defined in FSMC_NT35510.c file.
			- defines all register addresses of the NT35510 driver controller.
			
AUTHOR: 	Mario Gavran, E5029604, 
INSTITUTION:	University of Maribor - FERI
DATE:		feb.28.2020
*************************************************************************************************************/
#ifndef	__FSMC_NT35510_H__
#define __FSMC_NT35510_H__

#include "./Include/stm32f4xx.h"                  // Device header
#include <stdint.h>											// Standard integers header file.


extern void FSMC_GPIO_Init(void);
extern void FSMC_Init(void);

extern void FSMC_WR_REG(uint32_t Reg);
extern void FSMC_WR_DAT(uint16_t Dat);

extern void NT35510_Init(void);

extern void LCD_SetWindow(uint16_t Xs, uint16_t Ys, uint16_t Xe, uint16_t Ye);
extern void LCD_SetDirection(uint8_t Direction);
extern void LCD_ClearScreen(uint16_t Color);
extern void LCD_ClearArea(uint16_t Xs, uint16_t Ys, uint16_t Xe, uint16_t Ye, uint16_t Color);

extern void LCD_DrawPoint(uint16_t X, uint16_t Y, uint16_t Color, uint8_t Size);
extern void LCD_DrawLine(uint16_t Xs, uint16_t Ys, uint16_t Xe, uint16_t Ye, uint16_t Color, uint8_t Size);

extern void LCD_PrintCh(uint16_t X, uint16_t Y, uint16_t Color, uint16_t Bcolor, uint8_t Character, uint8_t Size);
extern void LCD_PrintStr(uint16_t X, uint16_t Y, uint16_t Color, uint16_t Bcolor, uint8_t* String, uint8_t Size);


#define RST_HIGH	GPIOC->ODR |=	GPIO_ODR_ODR_6		// Reset off.
#define RST_LOW		GPIOC->ODR &=	~(GPIO_ODR_ODR_6)	// Reset on.

// Orientation direction definitions.
#define VERTICAL_UP		0
#define VERTICAL_DOWN		1
#define HORIZONTAL_LEFT		2
#define HORIZONTAL_RIGHT	3

// Definition of the FSMC LCD structure for reading/writing to/from the LCD driver controller.
// The first element of the structure(REG) is a 16 bit integer, and because memory is addressed by
// bytes the next structure element(RAM) is offsetted by 0x2, and that address will turn on the addres
// bit A16
// CMMD ADDRESS
// 0x   6     0     0     1           F     F     F     E
// 0b    0110  0000  0000  0001        1111  1111  1111  1110
// 
// DATA ADDRESS
// 0x   6     0     0     2           0     0     0     0
// 0b    0110  0000  0000  0010        0000  0000  0000  0000
//                         /^\
//                         A16

typedef struct
{
	volatile uint16_t REG;
	volatile uint16_t	DAT;
}	FSMC_LCD_TypeDef;


//****************************************************************************************************
// Register addresses
//****************************************************************************************************

//****************************************************************************************************
// User Command Set
//****************************************************************************************************

#define NOP		0x0000U				// W	No effect. It can be used as dummy command.
#define SWRESET		0x0100U				// W	Software Reset. It resets the commands and parameters to default values.

// Read Display ID. 24-bit display identification information.
#define RDDID_ID1	0x0400U				// R	Manufacture ID
#define RDDID_ID2	0x0401U				// R	Driver version ID
#define RDDID_ID3	0x0402U				// R	Driver ID

#define RDNUMED		0x0000U				// R	Read Number of Errors on DSI. Not used for other interfaces. Mapped to NOP.
#define RDDPM		0x0A00U				// R	Read Display Power Mode
#define RDDMADCTL	0x0B00U				// R	Read Display MADCTL register
#define RDDCOLMOD	0x0C00U				// R	Read Display Pixel Format
#define RDDIM		0x0D00U				// R	Read Display Image Mode
#define RDDSM		0x0E00U				// R	Read Display Signal Mode
#define RDDSDR		0x0F00U				// R	Read Display Self-Diagnostic Result

#define SLPIN		0x1000U				// W	Sleep In
#define SLPOUT		0x1100U				// W	Sleep Out
#define PTLON		0x1200U				// W	Partial Display Mode On
#define NORON		0x1300U				// W	Normal Display Mode On
#define INVOFF		0x2000U				// W	Display Inversion Off
#define INVON		0x2100U				// W	Display Inversion On
#define ALLPOFF		0x2200U				// W	All Pixel Off
#define ALLPON		0x2300U				// W	All Pixel On
#define GAMSET		0x2600U				// W	Gamma Set
#define DISPOFF		0x2800U				// W	Display Off
#define DISPON		0x2900U				// W	Display On

// Column Address Set. Define area of frame memory where MPU can access.
#define CASET_XS_H	0x2A00U				// W	X Start[15:8]
#define CASET_XS_L	0x2A01U				// W	X Start[7:0]
#define CASET_XE_H	0x2A02U				// W	X End[15:8]
#define CASET_XE_L	0x2A03U				// W	X End[7:0]
// Row Address Set.
#define RASET_YS_H	0x2B00U				// W	Y Start[15:8]
#define RASET_YS_L	0x2B01U				// W	Y Start[7:0]
#define RASET_YE_H	0x2B02U				// W	Y End[15:8]
#define RASET_YE_L	0x2B03U				// W	Y End[7:0]

#define RAMWR		0x2C00U				// W 	Memory Write
#define RAMRD		0x2E00U				// R 	Memory Read

// Partial Area. Defines the partial mode display area.
#define PTLAR_PS_H	0x3000U				// W	PS[15:8]
#define PTLAR_PS_L	0x3001U				// W	PS[7:0]
#define PTLAR_PE_H	0x3002U				// W	PE[15:8]
#define PTLAR_PE_L	0x3003U				// W	PE[7:0]

#define TEOFF		0x3400U				// W  	Tearing Effect Line OFF
#define TEON		0x3500U				// W  	Tearing Effect Line ON
#define MADCTL		0x3600U				// W  	Memory Data Access Control
#define IDMOFF		0x3800U				// W  	Idle Mode Off
#define IDMON		0x3900U				// W  	Idle Mode On
#define COLMOD		0x3A00U				// W  	Interface Pixel Format

#define RAMWRC		0x3C00U				// W  	Memory Write Continue
#define RAMRDC		0x3E00U				// R  	Memory Read Continue

// Set Tearing Effect Scan Line.
#define STESL_H		0x4400U			  	// W  	N[15:8]
#define STESL_L		0x4401U			  	// W  	N[7:0]

// Get Scan Line.
#define GSL_H		0x4500U				// R  	N[15:8]
#define GSL_L		0x4501U				// R  	N[7:0]

#define DPCKRGB_UCS	0x4A00U				// W  	Display Clock in RGB Interface
#define DSTBON		0x4F00U				// W	Deep Standby Mode On

// Write Profile Value for Display.
#define WRPFD_01	0x5000U				// W	V01[7:0]
#define WRPFD_02	0x5001U				// W	V02[7:0]
#define WRPFD_03	0x5002U				// W	V03[7:0]
#define WRPFD_04	0x5003U				// W	V04[7:0]
#define WRPFD_05	0x5004U				// W	V05[7:0]
#define WRPFD_06	0x5005U				// W	V06[7:0]
#define WRPFD_07	0x5006U				// W	V07[7:0]
#define WRPFD_08	0x5007U				// W	V08[7:0]
#define WRPFD_09	0x5008U				// W	V09[7:0]
#define WRPFD_10	0x5009U				// W	V10[7:0]
#define WRPFD_11	0x500AU				// W	V11[7:0]
#define WRPFD_12	0x500BU				// W	V12[7:0]
#define WRPFD_13	0x500CU				// W	V13[7:0]
#define WRPFD_14	0x500DU				// W	V14[7:0]
#define WRPFD_15	0x500EU				// W	V15[7:0]
#define WRPFD_16	0x500FU				// W	V16[7:0]

#define WRDISBV		0x5100U				// W	Write Display Brightness Value
#define RDDISBV		0x5200U				// R	Read Display Brightness Value
#define WRCTRLD		0x5300U				// W	Write CTRL Display Value
#define RDCTRLD		0x5400U				// R	Read CTRL Display Value
#define WRCABC		0x5500U				// W	Write Content Adaptive Brightness Control
#define RDCABC		0x5600U				// R	Read Content Adaptive Brightness Control

// Write Hysteresis
#define WRHYSTE_I01_H	0x5700U				// W	I01[15:8]
#define WRHYSTE_I01_L	0x5701U				// W	I01[7:0]
#define WRHYSTE_I02_H	0x5702U				// W	I02[15:8]
#define WRHYSTE_I02_L	0x5703U				// W	I02[7:0]
#define WRHYSTE_I03_H	0x5704U				// W	I03[15:8]
#define WRHYSTE_I03_L	0x5705U				// W	I03[7:0]
#define WRHYSTE_I04_H	0x5706U				// W	I04[15:8]
#define WRHYSTE_I04_L	0x5707U				// W	I04[7:0]
#define WRHYSTE_I05_H	0x5708U				// W	I05[15:8]
#define WRHYSTE_I05_L	0x5709U				// W	I05[7:0]
#define WRHYSTE_I06_H	0x570AU				// W	I06[15:8]
#define WRHYSTE_I06_L	0x570BU				// W	I06[7:0]
#define WRHYSTE_I07_H	0x570CU				// W	I07[15:8]
#define WRHYSTE_I07_L	0x570DU				// W	I07[7:0]
#define WRHYSTE_I08_H	0x570EU				// W	I08[15:8]
#define WRHYSTE_I08_L	0x570FU				// W	I08[7:0]
#define WRHYSTE_I09_H	0x5710U				// W	I09[15:8]
#define WRHYSTE_I09_L	0x5711U				// W	I09[7:0]
#define WRHYSTE_I10_H	0x5712U				// W	I10[15:8]
#define WRHYSTE_I10_L	0x5713U				// W	I10[7:0]
#define WRHYSTE_I11_H	0x5714U				// W	I11[15:8]
#define WRHYSTE_I11_L	0x5715U				// W	I11[7:0]
#define WRHYSTE_I12_H	0x5716U				// W	I12[15:8]
#define WRHYSTE_I12_L	0x5717U				// W	I12[7:0]
#define WRHYSTE_I13_H	0x5718U				// W	I13[15:8]
#define WRHYSTE_I13_L	0x5719U				// W	I13[7:0]
#define WRHYSTE_I14_H	0x571AU				// W	I14[15:8]
#define WRHYSTE_I14_L	0x571BU				// W	I14[7:0]
#define WRHYSTE_I15_H	0x571CU				// W	I15[15:8]
#define WRHYSTE_I15_L	0x571DU				// W	I15[7:0]
#define WRHYSTE_I16_H	0x571EU				// W	I16[15:8]
#define WRHYSTE_I16_L	0x571FU				// W	I16[7:0]

#define WRHYSTE_D01_H	0x5720U				// W	D01[15:8]
#define WRHYSTE_D01_L	0x5721U				// W	D01[7:0]
#define WRHYSTE_D02_H	0x5722U				// W	D02[15:8]
#define WRHYSTE_D02_L	0x5723U				// W	D02[7:0]
#define WRHYSTE_D03_H	0x5724U				// W	D03[15:8]
#define WRHYSTE_D03_L	0x5725U				// W	D03[7:0]
#define WRHYSTE_D04_H	0x5726U				// W	D04[15:8]
#define WRHYSTE_D04_L	0x5727U				// W	D04[7:0]
#define WRHYSTE_D05_H	0x5728U				// W	D05[15:8]
#define WRHYSTE_D05_L	0x5729U				// W	D05[7:0]
#define WRHYSTE_D06_H	0x572AU				// W	D06[15:8]
#define WRHYSTE_D06_L	0x572BU				// W	D06[7:0]
#define WRHYSTE_D07_H	0x572CU				// W	D07[15:8]
#define WRHYSTE_D07_L	0x572DU				// W	D07[7:0]
#define WRHYSTE_D08_H	0x572EU				// W	D08[15:8]
#define WRHYSTE_D08_L	0x572FU				// W	D08[7:0]
#define WRHYSTE_D09_H	0x5730U				// W	D09[15:8]
#define WRHYSTE_D09_L	0x5731U				// W	D09[7:0]
#define WRHYSTE_D10_H	0x5732U				// W	D10[15:8]
#define WRHYSTE_D10_L	0x5733U				// W	D10[7:0]
#define WRHYSTE_D11_H	0x5734U				// W	D11[15:8]
#define WRHYSTE_D11_L	0x5735U				// W	D11[7:0]
#define WRHYSTE_D12_H	0x5736U				// W	D12[15:8]
#define WRHYSTE_D12_L	0x5737U				// W	D12[7:0]
#define WRHYSTE_D13_H	0x5738U				// W	D13[15:8]
#define WRHYSTE_D13_L	0x5739U				// W	D13[7:0]
#define WRHYSTE_D14_H	0x573AU				// W	D14[15:8]
#define WRHYSTE_D14_L	0x573BU				// W	D14[7:0]
#define WRHYSTE_D15_H	0x573CU				// W	D15[15:8]
#define WRHYSTE_D15_L	0x573DU				// W	D15[7:0]
#define WRHYSTE_D16_H	0x573EU				// W	D16[15:8]
#define WRHYSTE_D16_L	0x573FU				// W	D16[7:0]

// Write Gamma Setting.
#define WRGAMMSET_01_02	0x5800U				// W	G01[3:0] G02[3:0]
#define WRGAMMSET_03_04	0x5801U				// W	G03[3:0] G04[3:0]
#define WRGAMMSET_05_06	0x5802U				// W	G05[3:0] G06[3:0]
#define WRGAMMSET_07_08	0x5803U				// W	G07[3:0] G08[3:0]
#define WRGAMMSET_09_10	0x5804U				// W	G09[3:0] G10[3:0]
#define WRGAMMSET_11_12	0x5805U				// W	G11[3:0] G12[3:0]
#define WRGAMMSET_13_14	0x5806U				// W	G13[3:0] G14[3:0]
#define WRGAMMSET_15_16	0x5807U				// W	G15[3:0] G16[3:0]

#define RDFSVM		0x5A00U				// R  	Read FS Value MSBs
#define RDFSVL		0x5B00U				// R  	Read FS Value LSBs
#define RDMFFSVM	0x5C00U				// R  	Read Median Filter FS Value MSBs
#define RDMFFSVL	0x5D00U				// R  	Read Median Filter FS Value LSBs
#define WRCABCMB	0x5E00U				// W  	Write CABC minimum brightness
#define RDCABCMB	0x5F00U				// R  	Read CABC minimum brightness

// Write Light Sensor Compensation Coefficient Value.
#define WRLSCC_H	0x6500U				// W  	CC[15:8]
#define WRLSCC_L	0x6501U				// W  	CC[7:0]

// Read Light Sensor Compensation Coefficient Value.
#define RDLSCCM		0x6600U				// R  	CC[15:8]
#define RDLSCCL		0x6700U				// R  	CC[7:0]

// Read Black/White Color Characteristic. 10-bit values.
#define RDBWLB		0x7000U				// R  	Bkx[1:0] Bky[1:0] Wx[1:0] Wy[1:0]
#define RDBkx 		0x7100U				// R  	Bkx[9:2]
#define RDBky 		0x7200U				// R  	Bky[9:2]
#define RDWx  		0x7300U				// R  	Wx[9:2]
#define RDWy  		0x7400U				// R  	Wy[9:2]

// Read Red/Green Color Characteristic. 10-bit values.
#define RDRGLB		0x7500U				// R  	Rx[1:0] Ry[1:0] Gx[1:0] Gy[1:0]
#define RDRx		0x7600U				// R  	Rx[9:2]
#define RDRy		0x7700U				// R  	Ry[9:2]
#define RDGx		0x7800U				// R  	Gx[9:2]
#define RDGy		0x7900U				// R  	Gy[9:2]

// Read Blue/A Color Characteristic. 10-bit values.
#define RDBALB		0x7A00U				// R  	Bx[1:0] By[1:0] Ax[1:0] Ay[1:0]
#define RDBx		0x7B00U				// R  	Bx[9:2]
#define RDBy		0x7C00U				// R  	By[9:2]
#define RDAx		0x7D00U				// R  	Ax[9:2]
#define RDAy		0x7E00U				// R  	Ay[9:2]

// Read DDB Start.
#define RDDDBS_SID_L	0xA100U				// R  	SID[7:0]
#define RDDDBS_SID_H	0xA101U				// R  	SID[15:8]
#define RDDDBS_MID_L	0xA102U				// R  	MID[7:0]
#define RDDDBS_MID_H	0xA103U				// R  	MID[15:8]
#define RDDDBS_EXIT	0xA104U				// R  	0b11111111

// Read DDB Continue.
#define RDDDBC_SID_L	0xA800U				// R  	SID[7:0]
#define RDDDBC_SID_H	0xA801U				// R  	SID[15:8]
#define RDDDBC_MID_L	0xA802U				// R  	MID[7:0]
#define RDDDBC_MID_H	0xA803U				// R  	MID[15:8]
#define RDDDBC_EXIT	0xA804U				// R  	0b11111111

#define RDFCS		0xAA00U				// R	Read First Checksum
#define RDCCS		0xAF00U				// R	Read Continue Checksum
#define RDID1		0xDA00U				// R	Read ID1 Value
#define RDID2		0xDB00U				// R	Read ID2 Value
#define	RDID3		0xDC00U				// R	Read ID3 Value




//****************************************************************************************************
// Manufacture Command Set Selection.
//****************************************************************************************************

#define	MAUCCTR_0	0xF000U				// W	0x55
#define	MAUCCTR_1	0xF001U				// W	0xAA
#define	MAUCCTR_2	0xF002U				// W	0x52
#define	MAUCCTR_3	0xF003U				// W	Manufacture Command Set enable/disable
#define	MAUCCTR_4	0xF004U				// W	Manufacture Command Set selection






//****************************************************************************************************
// Manufacture Command Set – Page 0.
//****************************************************************************************************

// RGB Interface Signals Control. Set delay, polarity and porch for RGB I/F.
#define	RGBCTR_0	0xB000U				// RW	CRCM VSDL HSDL DEDL PCKP DEP HSP VSP
#define	RGBCTR_1	0xB001U				// RW	VBP[7:0]
#define	RGBCTR_2	0xB002U       			// RW	VFP[7:0]
#define	RGBCTR_3	0xB003U       			// RW	HBP[7:0]
#define	RGBCTR_4	0xB004U       			// RW	HFP[7:0]

// Display Option Control.
#define	DOPCTR_0	0xB100U				// RW	RAMKP DSITE DSIG DSIM DIS_Eo/TP_HS N565 ERR1 ERR0
#define	DOPCTR_1	0xB101U       			// RW	- - - TE_PW/R_SEL CRGB CTB CRL -

#define	DPCKRGB_MCS	0xB300U				// W 	Display Clock in RGB Interface
#define	VIVIDCTR	0xB400U				// RW	Vivid Color Function Control
#define	DPRSLCTR	0xB500U				// RW	Display Resolution Control CGM[7:0]
#define	SDHDTCTR	0xB600U				// RW	Source Output Data Hold Time Control SDT[5:0]

// EQ Control Function for Gate Signals.
#define	GSEQCTR_ST	0xB700U				// RW	GREQ_ST[3:0] GFEQ_ST[3:0]
#define	GSEQCTR_CK	0xB701U				// RW	GREQ_CK[3:0] GFEQ_CK[3:0]

// EQ Control Function for Source Driver.
#define	SDEQCTR_MOD 	0xB800U				// RW	EQMOD
#define	SDEQCTR_EQS1	0xB801U				// RW	EQS1[3:0]
#define	SDEQCTR_EQS2	0xB802U				// RW	EQS2[3:0]
#define	SDEQCTR_EQS3	0xB803U				// RW	EQS3[3:0]

// Source Control in Non-Display Area of Partial Display-
#define	SDNDACTR_0	0xB900U				// RW	ISCI[3:0]
#define	SDNDACTR_1	0xB901U				// RW	- GOAX PTD1 PTD0 - - PT1 PT0

#define	SDVPCTR     	0xBA00U				// RW	Source Control in Vertical Porch Time

// Source Driver Control.
#define	SGOPCTR_0	0xBB00U				// RW	ISOPA[3:0] IGOPA[3:0]
#define	SGOPCTR_1	0xBB01U				// RW	IGOPB[3:0]
#define	SGOPCTR_2	0xBB02U				// RW	ISOPC[3:0] IGOPC[3:0]

// Inversion Driving Control.
#define	INVCTR_NORM	0xBC00U				// RW	NLA[2:0]
#define	INVCTR_IDLE	0xBC01U				// RW	NLB[2:0]
#define	INVCTR_PART	0xBC02U				// RW	NLC[2:0]

// Display Timing Control in Normal / Idle Off Mode.
#define	DPFRCTR1_0	0xBD00U				// RW	T1A[9:8]
#define	DPFRCTR1_1	0xBD01U				// RW	T1A[7:0]
#define	DPFRCTR1_2	0xBD02U				// RW	VBPDA[7:0]
#define	DPFRCTR1_3	0xBD03U				// RW	VFPDA[7:0]
#define	DPFRCTR1_4	0xBD04U				// RW	PSELA[1:0]

// Display Timing Control in Idle On Mode
#define	DPFRCTR2_0	0xBE00U				// RW	T1B[9:8]
#define	DPFRCTR2_1	0xBE01U				// RW	T1B[7:0]
#define	DPFRCTR2_2	0xBE02U				// RW	VBPDB[7:0]
#define	DPFRCTR2_3	0xBE03U				// RW	VFPDB[7:0]
#define	DPFRCTR2_4	0xBE04U				// RW	PSELB[1:0]

// Display Timing Control in Partial / Idle Off Mode
#define	DPFRCTR3_0	0xBF00U				// RW	T1C[9:8]
#define	DPFRCTR3_1	0xBF01U				// RW	T1C[7:0]
#define	DPFRCTR3_2	0xBF02U				// RW	VBPDC[7:0]
#define	DPFRCTR3_3	0xBF03U				// RW	VFPDC[7:0]
#define	DPFRCTR3_4	0xBF04U				// RW	PSELC[1:0]

// Display Timing Control 12.
#define	DPTMCTR12_0	0xCC00U				// RW	- - - LVGL_SEL_H - - FHN LR_H
#define	DPTMCTR12_1	0xCC01U				// RW	CLW_H[7:0]
#define	DPTMCTR12_2	0xCC02U				// RW	FTI_H[7:0]

#define	LEDCTRDP	0xD000U				// RW	Control for LEDPWM/LEDON Pins
#define	DIMCTR		0xD200U				// RW	Dimming Control for LABC and CABC

// Display Brightness Dimming Control 1,2&3 for LABC and CABC
#define	DIMCTRDP1	0xD300U				// RW	DM_IN[3:0] DM_DE[3:0]
#define	DIMCTRDP2	0xD400U				// RW	DMSTP_L[2:0]
#define	DIMCTRDP3	0xD500U				// RW	STEP_IN[3:0] STEP_DE[3:0]


#define	DIMCTRCB2	0xDD00U				// RW	Display Brightness Control 1 for LABC and CABC


#define	PWMOFFDP	0xDE00U				// RW	Offset Compensation for LEDPWM Pin

// PWM Frequency Control for LEDPWM Pin.
#define	PWMFRCTR_0	0xE000U				// RW	PWMF
#define	PWMFRCTR_1	0xE001U				// RW	PWMDIV[7:0]

// Force Display Brightness for CABC.
#define	FCBRTCB_0	0xE100U				// RW	FORCE_CABC_PWM
#define	FCBRTCB_1	0xE101U				// RW	FORCE_CABC_DUTY[7:0]

// Display Brightness Control for CABC UI-Mode.
#define	BRTCBUI_0	0xE200U				// RW	CABC_UI_PWM0[7:0]
#define	BRTCBUI_1	0xE201U				// RW	CABC_UI_PWM1[7:0]
#define	BRTCBUI_2	0xE202U				// RW	CABC_UI_PWM2[7:0]
#define	BRTCBUI_3	0xE203U				// RW	CABC_UI_PWM3[7:0]

// Display Brightness Control for CABC Still-Mode.
#define	BRTCBSTL_0	0xE300U				// RW	CABC_PWM0[7:0]
#define	BRTCBSTL_1	0xE301U				// RW	CABC_PWM1[7:0]
#define	BRTCBSTL_2	0xE302U				// RW	CABC_PWM2[7:0]
#define	BRTCBSTL_3	0xE303U				// RW	CABC_PWM3[7:0]
#define	BRTCBSTL_4	0xE304U				// RW	CABC_PWM4[7:0]
#define	BRTCBSTL_5	0xE305U				// RW	CABC_PWM5[7:0]
#define	BRTCBSTL_6	0xE306U				// RW	CABC_PWM6[7:0]
#define	BRTCBSTL_7	0xE307U				// RW	CABC_PWM7[7:0]
#define	BRTCBSTL_8	0xE308U				// RW	CABC_PWM8[7:0]
#define	BRTCBSTL_9	0xE309U				// RW	CABC_PWM9[7:0]

// Display Brightness Control for CABC Moving-Mode
#define	BRTCBMOV_0	0xE400U				// RW	CABC_MOV_PWM0[7:0]
#define	BRTCBMOV_1	0xE401U				// RW	CABC_MOV_PWM1[7:0]
#define	BRTCBMOV_2	0xE402U				// RW	CABC_MOV_PWM2[7:0]
#define	BRTCBMOV_3	0xE403U				// RW	CABC_MOV_PWM3[7:0]
#define	BRTCBMOV_4	0xE404U				// RW	CABC_MOV_PWM4[7:0]
#define	BRTCBMOV_5	0xE405U				// RW	CABC_MOV_PWM5[7:0]
#define	BRTCBMOV_6	0xE406U				// RW	CABC_MOV_PWM6[7:0]
#define	BRTCBMOV_7	0xE407U				// RW	CABC_MOV_PWM7[7:0]
#define	BRTCBMOV_8	0xE408U				// RW	CABC_MOV_PWM8[7:0]
#define	BRTCBMOV_9	0xE409U				// RW	CABC_MOV_PWM9[7:0]

// Automatic Moving-Mode Detection Control.
#define	AMOVCTR_0	0xE500U				// RW	MOVDET[6:0]
#define	AMOVCTR_1	0xE501U				// RW	MOVSC[4:0]

#define	FHYSTCTR	0xE600U				// RW	Final Hsyteresis Result Control
#define	HYSTCTR		0xE700U				// RW	Internal Hsyteresis Function Control
#define	FLTRCTR		0xE800U				// RW	Median Filter and Flicker Filter Control

// Write Ambient Light Information
#define	WRALSV_0	0xE900U				// RW	LS[7:0]
#define	WRALSV_1	0xE901U       			// RW	LS[15:8]
#define	WRALSV_2	0xE902U       			// RW	ALS_W

#define	RDBRTDPL	0xEA00U				// R	Read Display Brightness from LABC
#define	RDBRTDPC	0xEB00U				// R	Read Display Brightness from CABC
#define	RDHYST		0xED00U				// R	Read Hysteresis Result
#define	RDGMA		0xEE00U				// R	Read Gamma Curve

// Read Ambient Light Information.
#define	RDALSV_0	0xEF00U				// R	ALSV[7:0]
#define	RDALSV_1	0xEF01U				// R	ALSV[15:8]




//****************************************************************************************************
// Manufacture Command Set – Page 1.
//****************************************************************************************************

// Setting AVDD Voltage.
#define SETAVDD_NORM	0xB000U				// RW	VBPA[4:0]
#define SETAVDD_IDLE	0xB001U				// RW	VBPB[4:0]
#define SETAVDD_PART	0xB002U				// RW	VBPC[4:0]

// Setting AVEE Voltage.
#define SETAVEE_NORM	0xB100U				// RW	VBNA[4:0]
#define SETAVEE_IDLE	0xB101U				// RW	VBNB[4:0]
#define SETAVEE_PART	0xB102U				// RW	VBNC[4:0]

// Setting VCL Voltage.
#define SETVCL_NORM	0xB200U				// RW	VBCLA[1:0]
#define SETVCL_IDLE	0xB201U				// RW	VBCLB[1:0]
#define SETVCL_PART	0xB202U				// RW	VBCLC[1:0]

// Setting VGH Voltage.
#define SETVGH_NORM	0xB300U				// RW	VBHA[3:0]
#define SETVGH_IDLE	0xB301U				// RW	VBHB[3:0]
#define SETVGH_PART	0xB302U				// RW	VBHC[3:0]

// Setting VRGH Voltage.
#define SETVRGH_NORM	0xB400U				// RW	VRGHA[5:0]
#define SETVRGH_IDLE	0xB401U				// RW	VRGHB[5:0]
#define SETVRGH_PART	0xB402U				// RW	VRGHC[5:0]

// Setting VGL_REG Voltage
#define SETVGL_NORM	0xB500U				// RW	VBLA[3:0]
#define SETVGL_IDLE	0xB501U				// RW	VBLB[3:0]
#define SETVGL_PART	0xB502U				// RW	VBLC[3:0]

// BT1 Power Control for AVDD.
#define BT1CTR_NORM	0xB600U				// RW	BTPA[2:0] PCKA[2:0]
#define BT1CTR_IDLE	0xB601U				// RW	BTPB[2:0] PCKB[2:0]
#define BT1CTR_PART	0xB602U				// RW	BTPC[2:0] PCKC[2:0]

// BT2 Power Control for AVEE.
#define BT2CTR_NORM	0xB700U				// RW	BTNA[2:0] NCKA[2:0]
#define BT2CTR_IDLE	0xB701U				// RW	BTNB[2:0] NCKB[2:0]
#define BT2CTR_PART	0xB702U				// RW	BTNC[2:0] NCKC[2:0]

// BT3 Power Control for VCL.
#define BT3CTR_NORM	0xB800U				// RW	BTCLA[1:0] CLCKA[2:0]
#define BT3CTR_IDLE	0xB801U				// RW	BTCLB[1:0] CLCKB[2:0]
#define BT3CTR_PART	0xB802U				// RW	BTCLC[1:0] CLCKC[2:0]

// BT4 Power Control for VGH.
#define BT4CTR_NORM	0xB900U				// RW	BTHA[1:0] HCKA[2:0] 
#define BT4CTR_IDLE	0xB901U				// RW	BTHB[1:0] HCKB[2:0] 
#define BT4CTR_PART	0xB902U				// RW	BTHC[1:0] HCKC[2:0] 

// BT5 Power Control for VGLX.
#define BT5CTR_NORM	0xBA00U				// RW	BTLA[1:0] LCKA[2:0]
#define BT5CTR_IDLE	0xBA01U				// RW	BTLB[1:0] LCKB[2:0]
#define BT5CTR_PART	0xBA02U				// RW	BTLC[1:0] LCKC[2:0]


#define PFMCTR		0xBB00U				// RW	Current Limit Control for PFM DC/DC Converter

// Setting VGMP and VGSP Voltage. 9-bit value.
#define SETVGP_0	0xBC00U				// RW	VGMP_8 VGSP_8
#define SETVGP_1	0xBC01U				// RW	VGMP[7:0]
#define SETVGP_2	0xBC02U				// RW	VGSP[7:0]

// Setting VGMN and VGSN Voltage. 9-bit value.
#define SETVGN_0	0xBD00U				// RW	VGMN_8 VGSN_8
#define SETVGN_1	0xBD01U				// RW	VGMN[7:0]
#define SETVGN_2	0xBD02U				// RW	VGSN[7:0]

// Setting VCOM Offset Voltage.
#define SETVCMOFF_0	0xBE00U				// RW	VCMOF VCM_8
#define SETVCMOFF_1	0xBE01U				// RW	VCM[7:0]

#define VGHCTR		0xBF00U				// RW	VGH Output Voltage

// Read ID for IC Vender Code.
#define RDIDIC_0	0xD500U				// R	ID41[7:0]
#define RDIDIC_1	0xD501U				// R	ID42[7:0]
#define RDIDIC_2	0xD502U				// R	ID43[3:0]

// Read ID for IC Production.
#define RDIDPRD_0	0xC600U				// R	ID51[5:0]
#define RDIDPRD_1	0xC601U				// R	ID52[5:0]
#define RDIDPRD_2	0xC602U				// R	ID53[5:0]
#define RDIDPRD_3	0xC603U				// R	ID54[4:0]
#define RDIDPRD_4	0xC604U				// R	ID55[9:8]
#define RDIDPRD_5	0xC605U				// R	ID55[7:0]
#define RDIDPRD_6	0xC606U				// R	ID56[3:0]

// Write Display ID.
#define WRDID_0		0xC700U				// RW 	ID1[7:0]
#define WRDID_1		0xC701U				// RW 	ID2[7:0]
#define WRDID_2		0xC702U				// RW 	ID3[7:0]


#define WRPCLRC_00	0xC800U				// R	Bkx[1:0] Bky[1:0] Wx[1:0] Wy[1:0]
#define WRPCLRC_01	0xC801U				// R	Bkx[9:2]
#define WRPCLRC_02	0xC802U				// R	Bky[9:2]
#define WRPCLRC_03	0xC803U				// R	Wx[9:2]
#define WRPCLRC_04	0xC804U				// R	Wy[9:2]
#define WRPCLRC_05	0xC805U				// R	Rx[1:0] Ry[1:0] Gx[1:0] Gy[1:0]
#define WRPCLRC_06	0xC806U				// R	Rx[9:2]
#define WRPCLRC_07	0xC807U				// R	Ry[9:2]
#define WRPCLRC_08	0xC808U				// R	Gx[9:2]
#define WRPCLRC_09	0xC809U				// R	Gy[9:2]
#define WRPCLRC_10	0xC80AU				// R	Bx[1:0] By[1:0] Ax[1:0] Ay[1:0]
#define WRPCLRC_11	0xC80BU				// R	Bx[9:2]
#define WRPCLRC_12	0xC80CU				// R	By[9:2]
#define WRPCLRC_13	0xC80DU				// R	Ax[9:2]
#define WRPCLRC_14	0xC80EU				// R	Ay[9:2]

// Write DDB.
#define WRDDB_0		0xC900U				// RW 	SID[7:0]
#define WRDDB_1		0xC901U				// RW 	SID[15:8]
#define WRDDB_2		0xC902U				// RW 	MID[7:0]
#define WRDDB_3		0xC903U				// RW	MID[15:8]

// Gradient Control for Gamma Voltage.
#define GMGRDCTR_0	0xD000U				// RW 	VGP1IN[5:0]
#define GMGRDCTR_1	0xD001U				// RW 	VGP1OUT[5:0]
#define GMGRDCTR_2	0xD002U				// RW 	VGP2IN[5:0]
#define GMGRDCTR_3	0xD003U				// RW	VGP2OUT[5:0]

// Setting Gamma 2.2 Correction (52 REGISTERS PER BASE!!!)
#define GMRCTR1_BASE	0xD100U				// RW	V0R1 [9:8]
#define GMGCTR1_BASE	0xD200U				// RW	V0G1 [9:8]
#define GMBCTR1_BASE	0xD300U				// RW	V0B1 [9:8]
#define GMRCTR2_BASE	0xD400U				// RW	V0R2 [9:8]
#define GMGCTR2_BASE	0xD500U				// RW	V0G2 [9:8]
#define GMBCTR2_BASE	0xD600U				// RW	V0B2 [9:8]

#define MTPDET		0xEC00U				// R	MTP Power Detection
#define MTPEN		0xED00U				// RW	MTP Enable Control

// MTP Write.
#define MTPWR_0		0xEE00U				// W	0xA5
#define MTPWR_1		0xEE01U				// W	0x5A
#define MTPWR_2		0xEE02U				// W	0x3C

// Read MTP Status.
#define RDMTP_0		0xEF00U				// R	MTP_STUS1[7:0]
#define RDMTP_1		0xEF01U				// R	MTP_STUS2[7:0]

/************************************************************************************************
* name       :ASCIItable
* date       :
* function   :
* parameters :
* retvalue   :
************************************************************************************************/


static const uint8_t  ASCIItable[128][8] = 
{
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //  0	NUL  null
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //  1	SOH  start of heading
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //  2	STX  start of text
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //  3	ETX  end of transmission
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //  4 	EOT  enquiry
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //  5	ENQ  enquiry
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //  6	ACK  acknowledge
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //  7	BEL  bell
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //  8	BS   backspace
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //  9	TAB  horizontal tab
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 10	LF   LINE FEED feed new line
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 11	VT   vertical tab
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 12	FF   FORM FEED feed new page
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 13	CR   carrige return
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 14	SO   shift out
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 15	SI   shift in
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 16	DLE  data link escape
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 17	DC1  devce controll
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 18	DC2  devce controll
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 19	DC3  devce controll
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 20	DC4  devce controll
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 21	NAK  not acknowledge
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 22	SYN  synchronous idle
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 23	ETB  end of trans} Block
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 24	CAN  cancle
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 25	EM   end of medium
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 26	SUB  substitude
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 27	ESC  escape
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 28	FS   file separator
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 29	GS   group separator
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 30	RS   record separator
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 31	US   unit separator


{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 // 32	     space
{0x04,0x04,0x04,0x04,0x00,0x04,0x00,0x00},	 // 33	!	
{0x0A,0x0A,0x0A,0x00,0x00,0x00,0x00,0x00},	 // 34	"	
{0x0A,0x0A,0x1F,0x0A,0x1F,0x0A,0x0A,0x00},	 // 35	#	
{0x04,0x0F,0x14,0x0E,0x05,0x1E,0x04,0x00},	 // 36	$	
{0x18,0x19,0x02,0x04,0x08,0x13,0x03,0x00},	 // 37	%	
{0x0C,0x12,0x14,0x08,0x14,0x12,0x0D,0x00},	 // 38	&	
{0x0C,0x04,0x08,0x00,0x00,0x00,0x00,0x00},	 // 39		
{0x02,0x04,0x08,0x08,0x08,0x04,0x02,0x00},	 // 40	(	
{0x08,0x04,0x02,0x02,0x02,0x04,0x08,0x00},	 // 41	)	
{0x00,0x04,0x15,0x0E,0x15,0x04,0x00,0x00},	 // 42	*	
{0x00,0x04,0x04,0x1F,0x04,0x04,0x00,0x00},	 // 43	+	
{0x00,0x00,0x00,0x00,0x0C,0x04,0x08,0x00},	 // 44	,	
{0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00},	 // 45	-	
{0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00},	 // 46	.	
{0x00,0x01,0x02,0x04,0x08,0x10,0x00,0x00},	 // 47	/	


{0x0E,0x11,0x13,0x15,0x19,0x11,0x0E,0x00},	 // 48	0	
{0x04,0x0C,0x04,0x04,0x04,0x04,0x0E,0x00},	 // 49	1	
{0x0E,0x11,0x01,0x02,0x04,0x08,0x1F,0x00},	 // 50	2	
{0x1F,0x02,0x04,0x02,0x01,0x11,0x0E,0x00},	 // 51	3	
{0x02,0x06,0x0A,0x12,0x1F,0x02,0x02,0x00},	 // 52	4	
{0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E,0x00},	 // 53	5	
{0x06,0x08,0x10,0x1E,0x11,0x11,0x0E,0x00},	 // 54	6	
{0x1F,0x01,0x02,0x04,0x08,0x08,0x08,0x00},	 // 55	7	
{0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E,0x00},	 // 56	8	
{0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C,0x00},	 // 57	9	


{0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x00,0x00},	 // 58	:	
{0x00,0x0C,0x0C,0x00,0x0C,0x04,0x08,0x00},	 // 59	;	
{0x02,0x04,0x08,0x10,0x08,0x04,0x02,0x00},	 // 60	<	
{0x00,0x00,0x1F,0x00,0x1F,0x00,0x00,0x00},	 // 61	=	
{0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x00},	 // 62	>	
{0x0E,0x11,0x01,0x02,0x04,0x00,0x04,0x00},	 // 63	?	
{0x0E,0x11,0x01,0x0D,0x15,0x15,0x0E,0x00},	 // 64	@	


{0x0E,0x11,0x11,0x11,0x1F,0x11,0x11,0x00},	 // 65	A	
{0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E,0x00},	 // 66	B	
{0x0E,0x11,0x10,0x10,0x10,0x11,0x0E,0x00},	 // 67	C	
{0x1C,0x12,0x11,0x11,0x11,0x12,0x1C,0x00},	 // 68	D	
{0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F,0x00},	 // 69	E	
{0x1F,0x10,0x10,0x1E,0x10,0x10,0x10,0x00},	 // 70	F	
{0x0E,0x11,0x10,0x17,0x11,0x11,0x0E,0x00},	 // 71	G	
{0x11,0x11,0x11,0x1F,0x11,0x11,0x11,0x00},	 // 72	H	
{0x0E,0x04,0x04,0x04,0x04,0x04,0x0E,0x00},	 // 73	I	
{0x07,0x02,0x02,0x02,0x02,0x12,0x0C,0x00},	 // 74	J	
{0x11,0x12,0x14,0x18,0x14,0x12,0x11,0x00},	 // 75	K	
{0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0x00},	 // 76	L	
{0x11,0x1B,0x15,0x15,0x11,0x11,0x11,0x00},	 // 77	M	
{0x11,0x11,0x19,0x15,0x13,0x11,0x11,0x00},	 // 78	N	
{0x0E,0x11,0x11,0x11,0x11,0x11,0x0E,0x00},	 // 79	O	
{0x1E,0x11,0x11,0x1E,0x10,0x10,0x10,0x00},	 // 80	P	
{0x0E,0x11,0x11,0x11,0x15,0x12,0x0D,0x00},	 // 81	Q	
{0x1E,0x11,0x11,0x1E,0x14,0x12,0x11,0x00},	 // 82	R	
{0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E,0x00},	 // 83	S	
{0x1F,0x04,0x04,0x04,0x04,0x04,0x04,0x00},	 // 84	T	
{0x11,0x11,0x11,0x11,0x11,0x11,0x0E,0x00},	 // 85	U	
{0x11,0x11,0x11,0x11,0x11,0x0A,0x04,0x00},	 // 86	V	
{0x11,0x11,0x11,0x11,0x15,0x15,0x0E,0x00},	 // 87	W	
{0x11,0x11,0x0A,0x04,0x0A,0x11,0x11,0x00},	 // 88	X	
{0x11,0x11,0x11,0x0A,0x04,0x04,0x04,0x00},	 // 89	Y	
{0x1F,0x01,0x02,0x04,0x08,0x10,0x1F,0x00},	 // 90	Z	


{0x0E,0x08,0x08,0x08,0x08,0x08,0x0E,0x00},	 // 91	[	
{0x11,0x0A,0x1F,0x04,0x1F,0x04,0x04,0x00},	 /* 92	\	*/
{0x0E,0x02,0x02,0x02,0x02,0x02,0x0E,0x00},	 // 93	]	
{0x04,0x0A,0x11,0x00,0x00,0x00,0x00,0x00},	 // 94	^	
{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00},	 // 95	_	
{0x08,0x04,0x00,0x00,0x00,0x00,0x00,0x00},	 // 96	`	


{0x00,0x00,0x0E,0x01,0x0F,0x11,0x0F,0x00},	 // 97	a	
{0x10,0x10,0x1E,0x11,0x11,0x11,0x1E,0x00},	 // 98	b	
{0x00,0x00,0x0E,0x10,0x10,0x11,0x0E,0x00},	 // 99	c	
{0x01,0x01,0x0D,0x13,0x11,0x11,0x0F,0x00},	 //100	d	
{0x00,0x00,0x0E,0x11,0x1F,0x10,0x0E,0x00},	 //101	e	
{0x06,0x09,0x08,0x1C,0x08,0x08,0x08,0x00},	 //102	f	
{0x00,0x0F,0x11,0x11,0x0F,0x01,0x0E,0x00},	 //103	g	
{0x10,0x10,0x16,0x19,0x11,0x11,0x11,0x00},	 //104	h	
{0x04,0x00,0x0C,0x04,0x04,0x04,0x0E,0x00},	 //105	i	
{0x02,0x00,0x06,0x02,0x02,0x12,0x0C,0x00},	 //106	j	
{0x10,0x10,0x12,0x14,0x18,0x14,0x12,0x00},	 //107	k	
{0x18,0x08,0x08,0x08,0x08,0x08,0x1C,0x00},	 //108	l	
{0x00,0x00,0x1A,0x15,0x15,0x11,0x11,0x00},	 //109	m	
{0x00,0x00,0x16,0x19,0x11,0x11,0x11,0x00},	 //110	n	
{0x00,0x00,0x0E,0x11,0x11,0x11,0x0E,0x00},	 //111	o	
{0x00,0x00,0x1E,0x11,0x1E,0x10,0x10,0x00},	 //112	p	
{0x00,0x00,0x0F,0x11,0x0F,0x01,0x01,0x00},	 //113	q	
{0x00,0x00,0x16,0x19,0x10,0x10,0x10,0x00},	 //114	r	
{0x00,0x00,0x0E,0x10,0x0E,0x01,0x1E,0x00},	 //115	s	
{0x08,0x08,0x1C,0x08,0x08,0x09,0x06,0x00},	 //116	t	
{0x00,0x00,0x11,0x11,0x11,0x13,0x0D,0x00},	 //117	u	
{0x00,0x00,0x11,0x11,0x11,0x0A,0x04,0x00},	 //118	v	
{0x00,0x00,0x11,0x11,0x11,0x15,0x0A,0x00},	 //119	w	
{0x00,0x00,0x11,0x0A,0x04,0x0A,0x11,0x00},	 //120	x	
{0x00,0x00,0x11,0x11,0x0F,0x01,0x0E,0x00},	 //121	y	
{0x00,0x00,0x1F,0x02,0x04,0x08,0x1F,0x00},	 //122	z	


{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //123	{	
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //124	|	
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //125	}	
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	 //126	~	
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} 	 //127	DEL	
};
//********************************************************************************End of ASCII Table//

#endif	//__FSMC_NT35510_H__

