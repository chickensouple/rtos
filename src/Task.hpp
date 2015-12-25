#ifndef _TASK_HPP
#define _TASK_HPP

#include <cstdint>

struct Task {
	enum State { READY, RUNNING, BLOCKED };

	State state;
	void (*fn)(void*);
	void* memoryBorder;
	uint32_t stackSize;
	uint32_t heapSize;

};

#endif /* _TASK_HPP */
