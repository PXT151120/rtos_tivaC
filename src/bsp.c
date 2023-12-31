
#include "bsp.h"
#include "driverlib/sysctl.h"
static uint32_t volatile l_tickCtr;


void BSP_Init()
{
	SYSCTL->RCGCGPIO |= (1 << 5);
	SYSCTL->GPIOHBCTL |= (1 << 5);
	GPIOF_AHB->DIR |= (LED_BLUE | LED_RED | LED_GREEN | TEST_PIN);
	GPIOF_AHB->DEN |= (LED_BLUE | LED_RED | LED_GREEN | TEST_PIN);

}

void BSP_ledGreenOn()
{
	GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
}

void BSP_ledBlueOn()
{
	GPIOF_AHB->DATA_Bits[LED_BLUE] = LED_BLUE;
}

void BSP_ledRedOn()
{
	GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED;
}

void BSP_ledGreenOff()
{
	GPIOF_AHB->DATA_Bits[LED_GREEN] = 0;
}

void BSP_ledBlueOff()
{
	GPIOF_AHB->DATA_Bits[LED_BLUE] = 0;
}

void BSP_ledRedOff()
{
	GPIOF_AHB->DATA_Bits[LED_RED] = 0;
}

void SysTick_Handler()
{
	GPIOF_AHB->DATA_Bits[TEST_PIN] = TEST_PIN;
	++l_tickCtr;

	__asm volatile ("cpsid i" : : : "memory");
	OS_Schedule();
	__asm volatile ("cpsie i" : : : "memory");
	GPIOF_AHB->DATA_Bits[TEST_PIN] = 0;
}


uint32_t BSP_tickCtr()
{
	uint32_t tick_Ctr;

	__asm volatile ("cpsid i" : : : "memory");
	tick_Ctr = l_tickCtr;
	__asm volatile ("cpsie i" : : : "memory");

	return tick_Ctr;
}

void BSP_delay(uint32_t ticks)
{
	uint32_t start = BSP_tickCtr();
	while((BSP_tickCtr() - start) <= ticks);
}

void OS_onStartup()
{
	SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_2_5);
	SysTick->CTRL = 0x07;
	SysTick->LOAD = (uint32_t)(SysCtlClockGet() / SYSTICKS_TIME) - 1;

	NVIC_SetPriority(SysTick_IRQn, 0);
}



void assert_failed(char const *module, int loc) {
    /* TBD: damage control */
	(void)(*module);
    (void)loc;    /* avoid the "unused parameter" compiler warning */
    NVIC_SystemReset();
}
