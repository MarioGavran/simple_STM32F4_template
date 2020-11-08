#ifndef	__STM32F413_SYSTEM_H__
#define __STM32F413_SYSTEM_H__

#include "./Include/stm32f4xx.h"                  // Device header
#include <stdint.h>			// Standard integers header file.

extern void PLL_Config(void);
extern void SCO_config(void);
extern void Delay_m(uint32_t ms);

#endif		// __STM32F413_SYSTEM_H__

