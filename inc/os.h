
#ifndef INC_OS_H_
#define INC_OS_H_
#include <stdint.h>
#include "bsp.h"

#define STACK_SIZE	    40
#define MAX_THREADS     (30 + 1)

extern void assert_failed(const char *module, int loc);


typedef struct 
{   
    void *sp;
    uint32_t timeOut;
}OsThread_st;

extern OsThread_st blinky1;
extern OsThread_st blinky2;


typedef void (*OsThreadHandler)();

void PendSV_Handler(void);
void main_IdleThread(void);

void OSThread_Start(OsThread_st *me,
                    OsThreadHandler threadHandler,
                    void *stkSto,
                    uint32_t stkSize);

void OS_Init(void *stkSto, uint32_t stkSize);
void OS_Schedule(void);
void OS_Run(void);
void OS_onStartup(void);
void OS_onIdle(void);
void OS_delay(uint32_t ticks);
void OS_tick(void);

#endif /* INC_OS_H_ */
