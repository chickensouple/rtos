#include "Scheduler.hpp"

#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/can.h"
#include "uartstdio.h"
#include "driverlib/systick.h"


namespace Scheduler {

static Task _tasks[SCHEDULER_NUM_TASKS];
static uint32_t _taskIdx;
static bool _running;

void idleTask(void*);
void irq(void);

void init() {
	_taskIdx = 0;
	_running = false;

	addTask(idleTask,
		0,
		20,
		0,
		nullptr);
}

bool addTask(void (*fn)(void*), 
	uint8_t priority,
	uint32_t stackSize, 
	uint32_t heapSize, 
	void* var) {

	if (_running) {
		return false;
	}

	if (_taskIdx >= SCHEDULER_NUM_TASKS) {
		return false;
	}

	stackSize = Utility::wordAlign(stackSize);
	heapSize = Utility::wordAlign(heapSize);

	void* memoryBorderLower = MemoryManagement::talloc(stackSize + heapSize);

	if (memoryBorderLower == nullptr) {
		return false;
	}

	void* memoryBorderHigher = (void*) (((uint8_t*) memoryBorderLower) + stackSize + heapSize);

	_tasks[_taskIdx++] = { Task::READY, 
		fn, 
		memoryBorderLower, 
		memoryBorderHigher, 
		stackSize, 
		heapSize, 
		priority };

	return true;
}


void run() {
	_running = true;

	// setup timer
	schedulerTimerSet(irq, 100000);

	schedulerTimerEnable();

	while (1);
}

void idleTask(void*) {
	while (1) { };
}


void irq(void) {

}


}


