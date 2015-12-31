#ifndef _CONTEXT_HPP
#define _CONTEXT_HPP

struct Context {
	// flags
	int32_t valid; // whether the context stored is valid or not
	int32_t usingFpu; // whether the context stored is using the FPU
	// FPU registers
	int32_t S0;
	int32_t S1;
	int32_t S2;
	int32_t S3;
	int32_t S4;
	int32_t S5;
	int32_t S6;
	int32_t S7;
	int32_t S8;
	int32_t S9;
	int32_t S10;
	int32_t S11;
	int32_t S12;
	int32_t S13;
	int32_t S14;
	int32_t S15;
	int32_t FPSRC;
	// normal registers
	int32_t R0;
	int32_t R1;
	int32_t R2;
	int32_t R3;
	int32_t R4;
	int32_t R5;
	int32_t R6;
	int32_t R7;
	int32_t R8;
	int32_t R9;
	int32_t R10;
	int32_t R11;
	int32_t R12;
	int32_t LR;
	int32_t APSR;
	int32_t SP;
	int32_t PC;

	Context() :
		valid(false),
		usingFpu(false) {}
};

#endif /* _CONTEXT_HPP */
