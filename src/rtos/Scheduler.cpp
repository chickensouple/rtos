#include "Scheduler.hpp"
#include "Core.hpp"
#include "hal/Hal.hpp"

namespace Scheduler {

void test1(void*) {
	int a = 2;
}

void init(void) {
	Task& idleTask = Core::TaskArr[0];
	idleTask.state = Task::READY;
	idleTask.fn = Scheduler::idle;
	idleTask.stackSize = 200;
	idleTask.heapSize = 0;
	idleTask.priority = 0;
	idleTask.memHigh = (void*) 0x20005000;

	Task& task1 = Core::TaskArr[1];
	task1.state = Task::READY;
	task1.fn = test1;
	task1.stackSize = 800;
	task1.heapSize = 200;
	task1.priority = 1;
	task1.memHigh = (void*) 0x20004500;

}

void run(void) {
	osTimerSet(mainInterruptHandler, 100000);

	osTimerEnable();

	while (1);
}

void schedule(Task** currTask, Task**  nextTask) {
	static int currTaskIdx = 0;
	int nextTaskIdx = currTaskIdx + 1;
	if (nextTaskIdx > 1) {
		nextTaskIdx = 0;
	}

	*currTask = &(Core::TaskArr[currTaskIdx]);
	*nextTask = &(Core::TaskArr[nextTaskIdx]);
	currTaskIdx = nextTaskIdx;
}

void idle(void*) {
	while (1) { }
}


}


