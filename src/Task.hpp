#ifndef _TASK_HPP
#define _TASK_HPP

#include <cstdint>

struct Task {
	enum State { READY, RUNNING, BLOCKED };

	State state;
	void (*fn)(void*);
	void* memoryBorderLower;
	void* memoryBorderHigher;
	uint32_t stackSize;
	uint32_t heapSize;
	uint8_t priority;

};

#endif /* _TASK_HPP */
