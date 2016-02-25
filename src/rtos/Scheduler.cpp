#include "Scheduler.hpp"
#include "hal/Hal.hpp"
#include "Task.hpp"
#include <cstdlib>
#include <vector>

namespace Scheduler {

const int READY_QUEUE_SIZE = 10;
int readyQueueIdx;

// Task* readyQueue[READY_QUEUE_SIZE];
Task readyQueue[READY_QUEUE_SIZE];
Task* currentTask = nullptr;
uint8_t stacks[2][3000];

void init(void) {
	currentTask = &readyQueue[0];
}

void run(void) {

	// Context::setContext(&currentTask->context);
	yield();
}

void yield(void) {
	SetPendSV();
}

Context::Context* getCurrentContext(void) {
	return &currentTask->context;
}

Context::Context* getNextContext(void) {
	static int task = 0;
	Task* nextTask = &readyQueue[task++];
	if (task >= 2) {
		task = 0;
	}
	return &nextTask->context;
}

void addTask(taskFunc task, 
	void* args, 
	uint8_t priority, 
	uint32_t stackSize) {
	static int i = 0;

	// Task* newTask = (Task*) malloc(sizeof(Task));
	Task* newTask = &readyQueue[i];
	newTask->fn = task;
	// newTask->stackStart = malloc(stackSize);
	newTask->stackStart = stacks[i];
	newTask->stackSize = stackSize;
	newTask->priority = priority;
	// readyQueue[readyQueueIdx++] = newTask;
	setupContext(&newTask->context, (void*)newTask->stackStart);

	i++;
}

}
