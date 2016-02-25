#ifndef _CONTEXT_HPP
#define _CONTEXT_HPP

#include <cstdint>
#include <cstddef>

namespace Context {

struct Context {
	void* stackPtr;
};

const int stackPtrOffset = offsetof(Context, stackPtr);

#define saveContext \
	__asm__ ( \
		/* check if floating point is used */ \
		"mrs 		r1,CONTROL\n\t" \
		"tst		r1,#4\n\t" \
		/* floating point */ \
		"it 		eq\n\t" \
		"vstmdbeq 	sp!,{s16-s31}\n\t" \
		"push 		{r4-r11,lr}\n\t" \
		"str 		sp,[r0, %[stackPtrOffset]]\n\t" \
		: \
		: [stackPtrOffset] "i" (stackPtrOffset) \
		);

#define loadContext \
	__asm__ ( \
		"ldr 		sp,[r0, %[stackPtrOffset]]\n\t" \
		"pop 		{r4-r11,lr}\n\t" \
		/* TODO: disable floating point context */ \
		/* check if floating point is used */ \
		"tst		lr,#(1 << 4)\n\t" \
		"it 		eq\n\t" \
		"vldmiaeq 	sp!,{s16-s31}\n\t" \
		/* TODO: need to reenable floating point context */ \
		"bx			lr\n\t"	\
		: \
		: [stackPtrOffset] "i" (stackPtrOffset) \
		);

void setupContext(Context* context, void* stackStart);

void setContext(Context* context);

}

#endif /* _CONTEXT_HPP */
