#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include <cstdint>
#include "Task.hpp"
#include "MemoryManagement.hpp"
#include "hal/Timer.h"
#include "hal/Context.hpp"

#define SCHEDULER_NUM_TASKS 10

#ifdef __cplusplus 
extern "C" {
#endif

namespace Scheduler {

void init();

bool addTask(void (*fn)(void*), 
	uint8_t priority,
	uint32_t stackSize, 
	uint32_t heapSize, 
	void* var);

void run();

void schedule(Context**, Context**);
}


#ifdef __cplusplus 
}
#endif

#endif /* _SCHEDULER_HPP */
