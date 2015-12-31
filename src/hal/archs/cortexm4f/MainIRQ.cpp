#include "MainIRQ.hpp"
#include "common/Task.hpp"
#include "rtos/Core.hpp"

extern void schedule(Task** currTask, Task** nextTask);

void mainInterruptHandler(void) {
	register int contextOffset asm("r2") = offsetof(Task, context);
	register int stackStartOffset asm("r3") = offsetof(Task, memHigh);
	register void* kernelStackPtr asm("r12") = Core::KernelStackPtr;

	asm volatile (
	"SUB 		SP,SP,#8\n\t" // Step 2: Allocate two pointers worth of space on the stack
	"ADD 		R0,SP,#4\n\t" // Step 2: Assign first argument into schedule function
	"ADD 		R1,SP,#0\n\t" // Step 2: Assign second argument into schedule function
	"PUSH 		{R4}\n\t" // Step 3: Pushing old value of R4 onto stack
	"MOV 		R4,SP\n\t" // Step 3: Saving the stack pointer into R4
	"MOV 		SP, %[kptr]\n\t" // Step 3: Setting the Stack pointer to point to location of Kernel stack
	"PUSH 		{R2,R3}\n\t" // Step 4: Pushing caller save registers
	"BL 		schedule\n\t" // Step 4 and 5: Call scheduler
	"POP 		{R2,R3}\n\t\n\t" // Step 5: Popping caller save registers
	"MOV 		SP,R4\n\t" // Step 6: Move stack pointer to point at Task stack again
	"POP 		{R4}\n\t" // Step 6: Pop old value of R4 back into R4
	"POP 		{R1}\n\t" // Step 7: Popping value of NewTask*
	"POP 		{R0}\n\t" // Step 7: Popping value of CurrTask*
	"CMP 		R0,R1\n\t" // Step 7: Comparing the two pointers
	"MRS 		R12,CONTROL\n\t" // Reading in Control Register to see if FPU Regs are stacked
	"AND 		R12,R12,#4\n\t"
	"LSR		R12,R12,#2\n\t"
	// if the two tasks are the same, pop context and continue execution
	"BEQ 		main_interrupt_pop_context\n\t"
	// Save context
	"ADD 		R0,R0,%[contextOffset]\n\t" // apply context offset
	"STR 		R12,[R0,#4]\n\t" // save whether we are using FPU context
	"CMP 		R12,#1\n\t" // checking to see if we are using FPU context 
	"MOV 		R12,#1\n\t"
	"STR 		R12,[R0,#0]\n\t" // set context to valid
	"ADD 		R0,R0,#8\n\t"
	"BEQ 		main_interrupt_store_fpu\n\t"

	// storing data registers
"main_interrupt_store_normal:\n\t"
	"ADD 		R0,R0,#68\n\t"
	"POP 		{R12}\n\t" // pop R0 into R12
	"STR 		R12,[R0],#4\n\t" // saving R0 context
	"POP 		{R12}\n\t" // pop R1 into R12
	"STR 		R12,[R0],#4\n\t" // saving R1 context
	"POP 		{R12}\n\t" // pop R2 into R12
	"STR 		R12,[R0],#4\n\t" // saving R2 context
	"POP 		{R12}\n\t" // pop R3 into R12
	"STR 		R12,[R0],#4\n\t" // saving R3 context
	"POP 		{R12}\n\t" // pop R12 into R12
	"STMIA 		R0!,{R4-R12}\n\t" // saving R4-R12 context
	"POP 		{R12}\n\t" // pop LR into R12
	"STR 		R12,[R0],#4\n\t" // saving LR context
	"POP 		{R4}\n\t" // pop PC into R4
	"POP 		{R12}\n\t" // pop APSR into R12
	"STR 		R12,[R0],#4\n\t" // saving APSR context
	"STR 		SP,[R0],#4\n\t" // saving SP context
	"STR 		R4,[R0],#4\n\t" // saving PC context
	"BEQ 		main_interrupt_fpu_stack_pop\n\t" // if we saved FPU, subtract the extra stack space we were using
	// load context (at this point we can use R0, R4-R12 freely)
"main_interrupt_load_context:\n\t" 
	"ADD 		R1,R1,%[contextOffset]\n\t" // apply context offset
	// if context is not valid, simply load stack pointer and call the function
	"LDR 		R5,[R1],#4\n\t"
	"CMP 		R5,#1\n\t"
	"BEQ		main_interrupt_load_start\n\t"
	// load context registers
"main_interrupt_load_registers:\n\t"
	// is we used FPU, load the FPU registers first
	"LDR 		R5,[R1],#4\n\t"
	"CMP 		R5,#1\n\t"
	"BEQ 		main_interrupt_load_fpu\n\t"
"main_interrupt_load_core:\n\t"
	"ADD 		R1,R1,#68\n\t"
	"MOV 		SP,R1\n\t" // using SP to keep track of where we are in the context
	"LDMIA 		SP!,{R0-R11}\n\t" // loading R0-R11
	// getting APSR
	"LDR 		R12,[SP,#8]\n\t"
	"MSR 		APSR_nzcvq,R12\n\t" // loading APSR
	"POP 		{R12}\n\t" // loading R12
	"POP 		{LR}\n\t" // loading LR
	"ADD 		SP,SP,#4\n\t" // popping APSR off stack
	"PUSH 		{R0,R1}\n\t" // push R0 and R1s's value onto stack so we can use them for calculations
	"MOV 		R0,SP\n\t"
	"LDR 		SP,[R0,#8]\n\t" // loading SP
	"LDR 		R1,[R0,#12]\n\t" // move PC's value on stack into R1
	"PUSH 		{R1}\n\t" // move PC onto Task Stack
	"LDR 		R1,[R0,#4]\n\t" // move R1's value on stack into R1
	"PUSH 		{R1}\n\t" // move R1 onto Task Stack
	"LDR 		R1,[R0,#0]\n\t" // move R0's value on stack into R1
	"PUSH 		{R1}\n\t" // move R0 onto Task Stack
	"POP 		{R0-R1}\n\t"
	"POP 		{PC}\n\t"

// stores fpu registers to context
"main_interrupt_store_fpu:\n\t"
	"ADD 		R12,SP,#32\n\t"
	"VLDMIA 	R12!,{S0-S15}\n\t"
	// saving fpu data registers
	"VSTMIA		R0,{S0-S15}\n\t"
	// saving FPSRC register
	"LDR 		R12,[R12]\n\t"
	"STR 		R12,[R0,#64]\n\t"
	"B 			main_interrupt_store_normal\n\t"
// pops off all the fpu register from stack
"main_interrupt_fpu_stack_pop:\n\t" 
	"ADD 		SP,SP,#68\n\t"
	"B 			main_interrupt_load_context\n\t"
"main_interrupt_load_start:\n\t"
	"SUB		R1,R1,%[contextOffset]\n\t"
	"LDR 		SP,[R1,%[stackStartOffset]]\n\t"
	"B 			main_interrupt_load_registers\n\t"
"main_interrupt_load_fpu:\n\t"
	"VLDMIA 	R1,{S0-S15}\n\t"
	"LDR 		R12,[R1,#64]\n\t"
	"VMSR 		FPSCR,R12\n\t"
	"B 			main_interrupt_load_core\n\t"
	:
	: [kptr] "r" (kernelStackPtr),
		[contextOffset] "r" (contextOffset),
		[stackStartOffset] "r" (stackStartOffset)
	);
	
	// Input: R12 is set to 1, if stacked context contains FPU registers
	// Ouput: none
	// Modifier: R12 register, will pop the context from the stack
	asm volatile (
"main_interrupt_pop_context:\n\t"
	"CMP 		R12,#1\n\t"
	"BEQ 		main_interrupt_pop_context_2\n\t"
"main_interrupt_pop_context_1:\n\t"
	"POP 		{R0-R3}\n\t" 
	"ADD 		R12,SP,#12\n\t"
	"LDR 		R12,[R12,#0]\n\t"
	"MSR 		APSR_nzcvq,R12\n\t"
	"POP 		{R12}\n\t"
	"POP 		{LR}\n\t"
	"BEQ 		main_interrupt_pop_context_4\n\t"
	"ADD 		SP,SP,#8\n\t"
	"LDR 		PC,[SP,#-8]\n\t"
"main_interrupt_pop_context_2:\n\t"
	"ADD 		R12,SP,#32\n\t"
	"VLDMIA		R12!,{S0-S15}\n\t"
	"LDR 		R12,[R12,#0]\n\t"
	"VMSR 		FPSCR,R12\n\t"
	"B 			main_interrupt_pop_context_1\n\t"
// pop FPU and Normal regs off stack
"main_interrupt_pop_context_4:\n\t"
	"ADD 		SP,SP,#76\n\t"
	"LDR 		PC,[SP,#-76]\n\t"
	);
}