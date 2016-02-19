#include "Scheduler.hpp"
#include "Core.hpp"
#include "hal/Hal.hpp"

extern void redLedTask(void*);
extern void blueLedTask(void*);

namespace Scheduler {

static int currTask = 0;

void init(void) {
	Task& task1 = Core::TaskArr[0];
	task1.state = Task::READY;
	task1.fn = redLedTask;
	task1.stackSize = 200;
	task1.priority = 0;
	task1.memHigh = (void*) 0x20005000;

	Task& task2 = Core::TaskArr[1];
	task2.state = Task::READY;
	task2.fn = blueLedTask;
	task2.stackSize = 800;
	task2.priority = 1;
	task2.memHigh = (void*) 0x20003000;
}

void run(void) {
	osTimerSet(SysTickHandler, 100000);

	osTimerEnable();

	while (1);
}

Task* getCurrentTask(void) {
	return &Core::TaskArr[currTask];
}

Task* getNextTask(void) {
	currTask = 1 - currTask;
	return &Core::TaskArr[currTask];
}

void addTask(taskFunc task, void* args) {
	Core::TaskArr[currTask].fn = task;
}

void idle(void*) {
	while (1) { }
}


}


