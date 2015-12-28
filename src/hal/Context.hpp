#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <stdint.h>

extern "C" {

struct Context {
	int32_t a;
	// // normal registers
	// int32_t r0;
	// int32_t r1;
	// int32_t r2;
	// int32_t r3;
	// int32_t r4;
	// int32_t r5;
	// int32_t r6;
	// int32_t r7;
	// int32_t r8;
	// int32_t r9;
	// int32_t r10;
	// int32_t r11;
	// int32_t r12;
	// int32_t lr;
	// int32_t pc;
	// int32_t xpsr;
	// int32_t stackPtr;
	// // floating point registers
	// int32_t s0;
	// int32_t s1;
	// int32_t s2;
	// int32_t s3;
	// int32_t s4;
	// int32_t s5;
	// int32_t s6;
	// int32_t s7;
	// int32_t s8;
	// int32_t s9;
	// int32_t s10;
	// int32_t s11;
	// int32_t s12;
	// int32_t s13;
	// int32_t s14;
	// int32_t s15;
};


void interruptHandler(void) __attribute__ (( naked ));

void switchContext(Context* oldContest, Context* newContext, int32_t* stackPtr);


}

#endif /* _CONTEXT_H */
