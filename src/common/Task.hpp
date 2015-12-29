#ifndef _TASK_HPP
#define _TASK_HPP

#include <cstdint>
#include <cstddef>

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


	uint8_t contextStacked;
	uint8_t usingFpu;
};

#endif /* _TASK_HPP */
