
#include "bsp.h"
#include "os.h"

uint32_t stack_blinky1[STACK_SIZE];
OsThread_st blinky1;
void main_blinky1()
{
	while(TRUE)
	{
		BSP_ledGreenOn();
		OS_delay(200);
		BSP_ledGreenOff();
		OS_delay(200);
	}

}

uint32_t stack_blinky2[STACK_SIZE];
OsThread_st blinky2;
void main_blinky2()
{
	while (TRUE)
	{
		BSP_ledRedOn();
		OS_delay(500);
		BSP_ledRedOff();
		OS_delay(500);
	}

}

uint32_t stack_idleThread[40];

int main(void)
{

	BSP_Init();
	OS_Init(stack_idleThread, sizeof(stack_idleThread));
	OSThread_Start(	&blinky1,
					&main_blinky1,
					stack_blinky1,
					sizeof(stack_blinky1));

	OSThread_Start(	&blinky2,
					&main_blinky2,
					stack_blinky2,
					sizeof(stack_blinky2));

	OS_Run();

	while(TRUE);

	return 0;
}

