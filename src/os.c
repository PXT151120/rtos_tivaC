#include "os.h"



OsThread_st * volatile OS_curr_ptr;
OsThread_st * volatile OS_next_ptr;

OsThread_st *OS_Threads[MAX_THREADS];
uint8_t threadsCnt_gu8 = 0;
uint8_t currIdx_gu8 = 0;

static uint16_t stackTime_Cnt;

void OSThread_Start(OsThread_st *me,
                    OsThreadHandler threadHandler,
                    void *stkSto,
                    uint32_t stkSize)
{
    uint32_t *stkPtr_u32 = (uint32_t*)((((uint32_t)stkSto + stkSize) / 8) * 8);


    *(--stkPtr_u32) = (1 << 24);
	*(--stkPtr_u32) = (uint32_t)(threadHandler);
	*(--stkPtr_u32) = 0x0000000Eu;
	*(--stkPtr_u32) = 0x0000000Cu;
	*(--stkPtr_u32) = 0x00000003u;
	*(--stkPtr_u32) = 0x00000002u;
	*(--stkPtr_u32) = 0x00000001u;
	*(--stkPtr_u32) = 0x00000000u;

    *(--stkPtr_u32) = 0x0000000Bu;
	*(--stkPtr_u32) = 0x0000000Au;
	*(--stkPtr_u32) = 0x00000009u;
	*(--stkPtr_u32) = 0x00000008u;
	*(--stkPtr_u32) = 0x00000007u;
	*(--stkPtr_u32) = 0x00000006u;
    *(--stkPtr_u32) = 0x00000005u;
    *(--stkPtr_u32) = 0x00000004u;

    /* Me pointer should be place here to serve pop and push instruction when using returning stack frame from SysTick_Handler */
    me->sp = stkPtr_u32;


    while((uint32_t)stkPtr_u32 > (uint32_t)stkSto)
    {
        *(--stkPtr_u32) = 0xDEADBEEFu;
    }

    if (threadsCnt_gu8 <= MAX_THREADS)
    {
        OS_Threads[threadsCnt_gu8] = me;
        ++threadsCnt_gu8;
    }
    else
    {
        assert_failed("os.c", 52);
    }


    
}

void OS_Init()
{
    *(uint32_t volatile*)0xE000ED20UL |= (0xFF << 16);
}

void OS_Schedule()
{
    uint8_t contextSwitch = 0;

    if (OS_curr_ptr == (void*)0)
    {
        OS_next_ptr = OS_Threads[currIdx_gu8];
    }

    OS_Threads[currIdx_gu8]->time++;
    if (OS_Threads[currIdx_gu8] == &blinky1)
    {
        if (OS_Threads[currIdx_gu8]->time > 200)
        {
            contextSwitch = 1;
        }
    }
    else if (OS_Threads[currIdx_gu8] == &blinky2)
    {
        if (OS_Threads[currIdx_gu8]->time > 1000)
        {
            contextSwitch = 1;
        }
    }
    else
    {

    }

    if (contextSwitch == 1)
    {
        OS_Threads[currIdx_gu8]->time = 0;
        ++currIdx_gu8;
        if (currIdx_gu8 == threadsCnt_gu8)
        {
            currIdx_gu8 = 0;
        }
        OS_next_ptr = OS_Threads[currIdx_gu8];
        
    }
    

    /* Trigger PendSV_Handler*/
    *(uint32_t volatile*)0xE000ED04UL |= (1 << 28);
}

void OS_Run()
{
    OS_onStartup();
    __asm volatile ("cpsid i" : : : "memory");
	OS_Schedule();
	__asm volatile ("cpsie i" : : : "memory");

}

__attribute__ ((naked, optimize("-fno-stack-protector")))
void PendSV_Handler(void) {
__asm volatile (

    /*
        __disable_irq();
        if (OS_curr_ptr != (OSThread *)0)
        {
            PUSH R4-R11 to stack
            OS_curr_ptr->sp = sp;
        } 
        sp = OS_next_ptr->sp;
        POP R4-R11 from stack
        __enable_irq();

    */

    /* __disable_irq(); */
    "  CPSID         I                 \n"

    /* if (OS_curr_ptr != (OSThread *)0) { */
    "  LDR           r1,=OS_curr_ptr       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  CBZ           r1,PendSV_restore \n"

    /*     push registers r4-r11 on the stack */
    "  PUSH          {r4-r11}          \n"

    /*     OS_curr_ptr->sp = sp; */
    "  LDR           r1,=OS_curr_ptr       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  STR           sp,[r1,#0x00]     \n"
    /* } */

    "PendSV_restore:                   \n"
    /* sp = OS_next_ptr->sp; */
    "  LDR           r1,=OS_next_ptr       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  LDR           sp,[r1,#0x00]     \n"

    /* OS_curr_ptr = OS_next_ptr; */
    "  LDR           r1,=OS_next_ptr       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  LDR           r2,=OS_curr_ptr       \n"
    "  STR           r1,[r2,#0x00]     \n"

    /* pop registers r4-r11, pop instruction will reduce/increase stack pointer */
    "  POP           {r4-r11}          \n"

    /* __enable_irq(); */
    "  CPSIE         I                 \n"

    /* return to the next thread */
    "  BX            lr                \n"
    );
}


