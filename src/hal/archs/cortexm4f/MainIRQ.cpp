#include "MainIRQ.hpp"
#include "common/Task.hpp"
#include "rtos/Core.hpp"

namespace Scheduler {

extern Task* getCurrentTask(void);
extern Task* getNextTask(void);

}

void PendSVHandler(void) {
	// need to write in ASM to make sure we are using right registers
	Task* currTask = Scheduler::getCurrentTask();
	Task* nextTask = Scheduler::getNextTask();

	saveContext(&currTask->context);
	loadContext(&nextTask->context);
}

void SysTickHandler(void) {
	SetPendSV();
}

void SetPendSV(void) {
	uint32_t* NVIC_INT_CTRL = (uint32_t*) (0xE000ED04);
	uint32_t PendSVSet = 0x10000000;

	*NVIC_INT_CTRL |= PendSVSet;
	// 0x10000000 pendsv set
	// 0x08000000 pendsv clear

}
