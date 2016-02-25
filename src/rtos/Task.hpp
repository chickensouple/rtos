#ifndef _TASK_HPP
#define _TASK_HPP

#include <cstdint>
#include <cstddef>
#include "hal/Hal.hpp"

typedef void(*taskFunc)(void*);

struct Task {
	enum State : size_t { READY, RUNNING, BLOCKED };

	taskFunc fn;
	State state;
	size_t stackSize;
	void* stackStart; // start of stack
	uint8_t priority;

	Context::Context context;
};

#endif /* _TASK_HPP */
