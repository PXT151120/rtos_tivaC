
#include "bsp.h"
#include "os.h"

uint32_t stack_blinky1[STACK_SIZE];
OsThread_st blinky1;
void main_blinky1()
{
	while(TRUE)
	{
		BSP_ledGreenOn();
		// BSP_delay(100);
		BSP_ledGreenOff();
		// BSP_delay(100);
	}

}

uint32_t stack_blinky2[STACK_SIZE];
OsThread_st blinky2;
void main_blinky2()
{
	while (TRUE)
	{
		BSP_ledRedOn();
		// BSP_delay(200);
		BSP_ledRedOff();
		// BSP_delay(200);
	}

}


int main(void)
{

	BSP_Init();
	OS_Init();
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

