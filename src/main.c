
#include "bsp.h"
#include "os.h"

uint32_t stack_blinky1[STACK_SIZE];
OsThread_st blinky1;
void main_blinky1()
{
	uint16_t index_ldu16;
	while(TRUE)
	{
		for (index_ldu16 = 500; index_ldu16 > 0; index_ldu16--)
		{
			BSP_ledGreenOn();
			BSP_ledGreenOff();
		}
		OS_delay(1);
	}

}

uint32_t stack_blinky2[STACK_SIZE];
OsThread_st blinky2;
void main_blinky2()
{
	uint16_t index_ldu16;
	while(TRUE)
	{
		for (index_ldu16 = 3*1100; index_ldu16 > 0; index_ldu16--)
		{
			BSP_ledRedOn();
			BSP_ledRedOff();
		}
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
					5,
					stack_blinky1,
					sizeof(stack_blinky1));

	OSThread_Start(	&blinky2,
					&main_blinky2,
					2,
					stack_blinky2,
					sizeof(stack_blinky2));

	OS_Run();

	while(TRUE);

	return 0;
}

