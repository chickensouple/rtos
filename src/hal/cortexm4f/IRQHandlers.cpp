#include "IRQHandlers.hpp"
#include "Context.hpp"
#include <cstdint>

extern "C" {
namespace Scheduler {
	extern Context::Context* getCurrentContext(void);
	extern Context::Context* getNextContext(void);
}
}

void PendSVHandler(void) {
	__asm__(
		"bl getCurrentContext"
		);
	saveContext
	__asm__(
		"bl getNextContext"
		);
	loadContext
}

void SysTickHandler(void) {
	SetPendSV();
}

void SetPendSV(void) {
	uint32_t* NVIC_INT_CTRL = (uint32_t*) (0xE000ED04);
	uint32_t PendSVSet = 0x10000000;

	*NVIC_INT_CTRL |= PendSVSet;
	// 0x10000000 pendsv set
	// 0x08000000 pendsv clear
}
