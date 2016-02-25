#include "IRQHandlers.hpp"
#include "Context.hpp"
#include <cstdint>

using namespace Context;

extern "C" {
namespace Scheduler {
	extern Context::Context* getCurrentContext(void);
	extern Context::Context* getNextContext(void);
}
}

void PendSVHandler(void) {
	__asm__(
		// "mov	r0,#0xE000ED04\n\t"
		"movw	r0,#0xED04\n\t"
		"movt	r0,#0xE000\n\t"
		"mov	r1,#0x08000000\n\t"
		"str 	r1,[r0]\n\t"
		);
	__asm__(
		"bl 	getCurrentContext\n\t"
		);
	saveContext
	__asm__(
		"bl 	getNextContext\n\t"
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
