#ifndef _TASK_HPP
#define _TASK_HPP

#include <cstdint>
#include "hal/Context.hpp"

struct Task {
	enum State { READY, RUNNING, BLOCKED };

	State state;
	void (*fn)(void*);
	void* memoryBorderLower;
	void* memoryBorderHigher;
	uint32_t stackSize;
	uint32_t heapSize;
	uint8_t priority;
	Context context;


	// Task() :
	// 	state(READY),
	// 	fn(nullptr),
	// 	memoryBorderLower(nullptr),
	// 	memoryBorderHigher(nullptr),
	// 	stackSize(0),
	// 	heapSize(0),
	// 	priority(0),
	// 	context() {}
};

#endif /* _TASK_HPP */
