// -------------------- customOS.c ------------------------
//                 Author: Macovei Tudor
//               Project: _Preh_Voltmeter
//            Functionality: Task Scheduler
// --------------------------------------------------------

// Includes
#include "customOS.h"

// Defines
#define taskNumber 2

// Variables
volatile uint32_t myTicks = 0;
uint32_t taskTime = 0;


// Definitions
extern void readVoltsHandler(void);
extern void screenHandler(void);
typedef void (*leFunction)(void);
typedef struct
{
	leFunction func;
	uint32_t nowPeriod;
	uint32_t lastRun;
}leTask;
leTask scheduler[taskNumber];

// Function Definitions
// Delay
void delayMe(uint8_t ms)
{
	uint32_t start = myTicks;
	while((myTicks - start) < ms);
}

// IRQ Tick
void SysTick_Handler(void)
{
	myTicks++;
}

// Initializing the Task Scheduler
void initOS()
{
	scheduler[0] = (leTask)
	{
		readVoltsHandler,           // Task name
		5,                          // Task execution time in Ticks, rounded up for safety
		0                           // Last tick task was executed, updates as program runs
	};
	scheduler[1] = (leTask)
	{
		screenHandler,
		46,
		0
	};
}

void runOS()
{
	while(1)
	{
		uint32_t now = myTicks;
		if(myTicks)
	    {
			if((now - scheduler[0].lastRun) >= scheduler[0].nowPeriod)          // Task 0 is ran twice consecutively
		    {
	    		scheduler[0].lastRun = now;
	    		scheduler[0].func();
		    }
	    	if((now - scheduler[1].lastRun) >= scheduler[1].nowPeriod)                                                                                    // Task 1 is ran once
	    	{
	    		scheduler[1].lastRun = now;
	    		scheduler[1].func();

	    	}
	    }
		__WFI();                                                                                            // Ticks left to 30 are left for sleep
    }
}
