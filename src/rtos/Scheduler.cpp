#include "Scheduler.hpp"
#include "Task.hpp"
#include <cstdlib>
#include <vector>

namespace Scheduler {

const int READY_QUEUE_SIZE = 10;
int readyQueueIdx;

Task* readyQueue[READY_QUEUE_SIZE];
Task* currentTask = nullptr;

void init(void) {
	
}

void run(void) {

}

Context::Context* getCurrentContext(void) {

}

Context::Context* getNextContext(void) {

}

void addTask(taskFunc task, 
	void* args, 
	uint8_t priority, 
	uint32_t stackSize) {

	Task* newTask = (Task*) malloc(sizeof(Task));
	newTask->fn = task;
	newTask->stackStart = malloc(stackSize);
	newTask->stackSize = stackSize;
	newTask->priority = priority;
	readyQueue[readyQueueIdx++] = newTask;
	setupContext(&newTask->context, (void*)newTask->stackStart);
}

}
