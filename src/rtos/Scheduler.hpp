#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include "Task.hpp"
#include "hal/Hal.hpp"

extern "C" {

namespace Scheduler {

typedef void(*taskFunc)(void*);

void init(void);

void run(void);

Context::Context* getCurrentContext(void);

Context::Context* getNextContext(void);

void addTask(taskFunc task, 
	void* args, 
	uint8_t priority, 
	uint32_t stackSize);

}

}

#endif /* _SCHEDULER_HPP */
