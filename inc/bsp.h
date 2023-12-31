
#ifndef INC_BSP_H_
#define INC_BSP_H_

#include <stdbool.h>
#include "system_TM4C123GH6PM.h" /* the TM4C MCU Peripheral Access Layer (TI) */
#include "TM4C123GH6PM.h"
#include "os.h"

#define SYSTICKS_TIME    2e5

#define TRUE 	(1 != 0)
#define FALSE	(1 == 0)

#define LED_RED		(1 << 1)
#define LED_BLUE	(1 << 2)
#define LED_GREEN	(1 << 3)
#define TEST_PIN    (1 << 4)


void BSP_Init(void);

void BSP_ledGreenOn(void);
void BSP_ledBlueOn(void);
void BSP_ledRedOn(void);
void BSP_ledGreenOff(void);
void BSP_ledBlueOff(void);
void BSP_ledRedOff(void);



void SysTick_Handler(void);
uint32_t BSP_tickCtr(void);
void BSP_delay(uint32_t ticks);

#endif /* INC_BSP_H_ */
