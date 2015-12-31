#include "MainIRQ.hpp"
#include "common/Task.hpp"
#include "rtos/Core.hpp"

extern void schedule(Task** currTask, Task** nextTask);

void mainInterruptHandler(void) {
	register int context asm("r2") = offsetof(Task, context);
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
	"POP 		{R2, R3}\n\t\n\t" // Step 5: Popping caller save registers
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
	"ADD 		R0,R0,%[context]\n\t" // apply context offset
	"STR 		R12,[R0,#4]\n\t" // save whether we are using FPU context
	"CMP 		R12,#1\n\t" // checking to see if we are using FPU context 
	"MOV 		R12,#1\n\t"
	"STR 		R12,[R0,#0]\n\t" // set context to valid
	"ADD 		R0,R0,#8\n\t"
	"BEQ 		main_interrupt_store_fpu\n\t"
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
	"STR 		SP,[R0],#4\n\t" // asving SP context
	"STR 		R4,[R0],#4\n\t" // saving PC context


"main_interrupt_store_fpu:\n\t"
	// saving fpu data registers
	"VSTMIA		R0,{S0-S15}\n\t"
	// saving FPSRC register
	"VMSR 		FPSCR,R12\n\t"
	"STR 		R12,[R0,#64]\n\t"
	"B 			main_interrupt_store_normal\n\t"
	:
	: [kptr] "r" (kernelStackPtr),
		[context] "r" (context)
	);


	
	// Input: R12 is set to 1, if stacked context contains FPU registers
	// Ouput: none
	// Modifier: R12 register, will pop the context from the stack
	asm volatile (
"main_interrupt_pop_context:\n\t"
	// if (R12 == 1), pop FPU registers
	"CMP 		R12,#1\n\t"
	"BEQ 		main_interrupt_pop_context_2\n\t"
	// POP normal registers
"main_interrupt_pop_context_1:\n\t"
	// POP data registers except R12
	"POP 		{R4-R11,R0-R3}\n\t"
	// POP APSR
	"ADD 		R12,SP,#12\n\t"
	"LDR 		R12,[R12,#0]\n\t"
	"MSR 		APSR_nzcvq,R12\n\t"
	"MOV 		R12,#16\n\t"
	"BEQ 		main_interrupt_pop_context_3\n\t"
"main_interrupt_pop_context_4:\n\t"
	// Move SP to correct location
	"ADD 		SP,SP,R12\n\t"
	"SUB 		R12,SP,R12\n\t"
	// Load PC into LR for temp storage
	"LDR 		LR,[R12,#8]\n\t"
	// Push PC onto actual stack top
	"PUSH 		{LR}\n\t"
	// Load LR and R12
	"LDR 		LR,[R12,#4]\n\t"
	"LDR 		R12,[R12,#0]\n\t"
	// Pop of PC
	"POP 		{PC}\n\t"

// Finish popping off all registers
"main_interrupt_pop_context_3:\n\t"
	"ADD 		R12,R12,#68\n\t"
	"B 			main_interrupt_pop_context_3\n\t"
// pop off FPU registers
"main_interrupt_pop_context_2:\n\t"
	"ADD 		R12,SP,#64\n\t"
	"VLDMIA 	R12!,{S0-S15}\n\t"
	"LDR 		R12,[R12,#0]\n\t"
	"VMSR 		FPSCR,R12\n\t"
	"B 			main_interrupt_pop_context_1\n\t"
	);
}