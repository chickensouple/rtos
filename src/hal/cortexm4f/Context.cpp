#include "Context.hpp"
#include <cstdint>
#include <cstddef>

namespace Context {

void setupContext(Context* context, void* stackStart) {
	register int stackPtrOffset asm("r2") = offsetof(Context, stackPtr);

	asm volatile(
		"mov		r3,#0\n\t"
		// pushing initial registers of xPSR, PC, LR, R12, R3-R0
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		// pushing initial registers of R11-R4
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		"stmdb		r1!,{r3}\n\t"
		// pushing link register
		// EXEC_RETURN using non floating point and MSP
		"mov 		r3,#0xFFFFFFF9\n\t"
		"stmdb		r1!,{r3}\n\t"
		"str 		r1,[r0, %[stackPtrOffset]]\n\t"
		:
		: [stackPtrOffset] "r" (stackPtrOffset)
		);
}

}
