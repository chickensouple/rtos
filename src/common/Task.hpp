#ifndef _TASK_HPP
#define _TASK_HPP

#include <cstdint>
#include <cstddef>
#include "hal/Hal.hpp"

struct Task {
	enum State : size_t { READY, RUNNING, BLOCKED };

	State state;
	void (*fn)(void*);
	size_t stackSize;
	size_t heapSize;
	void* memLow;
	void* memHigh;
	void* memSeparator;
	uint8_t priority;


	Context context;
};

#endif /* _TASK_HPP */
