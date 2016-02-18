#include "Context.hpp"
#include <cstdint>
#include <cstddef>

void saveContext(Context* context) {
	// this assumes that the following is on the stack

	// (OPTIONAL if fpu is enabled)
	// FPSCR
	// S15
	// S14
	// ...
	// S0
	// (MANDATORY)
	// xPSR
	// PC
	// LR
	// R12
	// R3
	// R2
	// R1
	// R0
	
	register Context* contextPtr asm("r1") = context;
	register int stackPtrOffset asm("r2") = offsetof(Context, stackPtr);

	asm volatile(
		// check if floating point is used
		"mrs 		r0,CONTROL\n\t"
		"tst		r0,#4\n\t"
		
		// floating point
		"it 		eq\n\t"
		"vstmdbeq 	sp!,{s16-s31}\n\t"

		"push 		{r4-r11,lr}\n\t"

		"str 		sp,[%[contextPtr], %[stackPtrOffset]]\n\t"
		"bx			lr\n\t"
		:
		: [contextPtr] "r" (contextPtr),
			[stackPtrOffset] "r" (stackPtrOffset)
		);
}

void loadContext(Context* context) {
	register Context* contextPtr asm("r1") = context;
	register int stackPtrOffset asm("r2") = offsetof(Context, stackPtr);

	asm volatile(
		"ldr 		sp,[%[contextPtr], %[stackPtrOffset]]\n\t"

		"pop 		{r4-r11,lr}\n\t"

		// check if floating point is used
		"mrs 		r0,CONTROL\n\t"
		"tst		r0,#4\n\t"

		"it 		eq\n\t"
		"vldmiaeq 	sp!,{s16-s31}\n\t"

		"bx			lr\n\t"
		:
		: [contextPtr] "r" (contextPtr),
			[stackPtrOffset] "r" (stackPtrOffset)
		);
}



