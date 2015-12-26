#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <cstdint>

struct Context {
	int32_t r0;
	int32_t r1;
	int32_t r2;
	int32_t r3;
	int32_t r4;
	int32_t r5;
	int32_t r6;
	int32_t r7;
	int32_t r8;
	int32_t r9;
	int32_t r10;
	int32_t r11;
	int32_t r12;
	int32_t pc;
	int32_t stackPtr;
	int32_t xpsr;
};

#endif /* _CONTEXT_H */
