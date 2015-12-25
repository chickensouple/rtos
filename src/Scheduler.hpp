#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include <cstdint>
#include "Task.hpp"
#include "MemoryManagement.hpp"

template <uint32_t N>
class Scheduler {
public:
	Scheduler();

	bool addTask(void (*fn)(void*), 
		uint32_t stackSize, 
		uint32_t heapSize, 
		void* var);

	void run();

protected:
	Task _tasks[N];
	uint32_t _taskIdx;
	bool _running;
};

#include "SchedulerImplementation.hpp"

#endif /* _SCHEDULER_HPP */
