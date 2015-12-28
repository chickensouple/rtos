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

void init() {
	_taskIdx = 0;
	_running = false;

	addTask(idleTask,
		0,
		200,
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

	void* memoryBorderHigher = (void*) (((uint8_t*) memoryBorderLower) + stackSize + 
		heapSize);

	Task& task = _tasks[_taskIdx++];
	task.state = Task::READY;
	task.fn = fn;
	task.memoryBorderLower = memoryBorderLower;
	task.memoryBorderHigher = memoryBorderHigher;
	task.stackSize = stackSize;
	task.heapSize = heapSize;
	task.priority = priority;
	// _tasks[_taskIdx++] = { Task::READY, 
	// 	fn, 
	// 	memoryBorderLower, 
	// 	memoryBorderHigher, 
	// 	stackSize, 
	// 	heapSize, 
	// 	priority,
	// 	{0, 1, 2}};

	return true;
}


void run() {
	_running = true;

	// setup timer
	schedulerTimerSet(interruptHandler, 100000);

	schedulerTimerEnable();

	while (1);
}

void idleTask(void*) {
	while (1) { };
}

void schedule(Context** oldContext, Context** newContext) {
	static int i = 0;
	int nextI = i + 1;
	if (nextI > 1) {
		nextI = 0;
	}
	*oldContext = &(_tasks[i].context);
	*newContext = &(_tasks[nextI].context);
	i = nextI;
}


}


