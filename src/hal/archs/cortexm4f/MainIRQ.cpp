#include "MainIRQ.hpp"
#include "common/Task.hpp"
#include "rtos/Core.hpp"

extern void schedule(Task** currTask, Task** nextTask);

void mainInterruptHandler(void) {
	register int usingFpu asm("r2") = offsetof(Task, usingFpu);
	register int contextStacked asm("r3") = offsetof(Task, contextStacked);
	asm volatile (
	"MOV		R0,SP\n\t" // read current stack ptr
	"SUB		SP,SP,#12\n\t" // allocate a space to store current stack pointer
	"STR		R0,[SP,#8]\n\t"  // store current stack pointer
	"ADD		R0,SP,#4\n\t" // give first operand into schedule function
	"ADD		R1,SP,#0\n\t" // give second operand into schedule function
	"PUSH		{R4}\n\t" // save caller save reg so we can use R4
	"MOV		R4,SP\n\t" // save stack pointer
	"PUSH		{R2,R3}\n\t" // save callee save registers
	"MOV		SP,%[kptr]\n\t" // change stack pointer to kernel stack pointer
	"BL			schedule\n\t" // call scheduler
	"MOV 		SP,R4\n\t" // change stack pointer back to task stack pointer
	"POP 		{R2,R3}\n\t" // pop calle save register
	"POP		{R4}\n\t" // popping caller save register
	// compare task addresses
	"LDR		R0,[SP,#4]\n\t" // currTask*
	"LDR		R1,[SP,#0]\n\t" // nextTask*
	"CMP 		R0,R1\n\t"
	"BEQ		main_interrupt_end\n\t"
	// save current context
	"ADD 		SP,SP,#12\n\t" // pop off temporary variables
	"PUSH		{R4-R11}\n\t"
	"MRS		R4,CONTROL\n\t"
	"AND 		R4,R4,#4\n\t" // get just the fpu stack bit
	"CMP 		R4,#0\n\t" // if equal to 0, then we don't need to worry about floating point stack
	"MOV		R5,#32\n\t"
	"BEQ		main_interrupt_save_stack_ptr\n\t"
	"ADD		R5,R5,#68\n\t"
"main_interrupt_save_stack_ptr:\n\t"
	""
	: 
	: [kptr] "r" (Core::KernelStackPtr), 
		[usingFpu] "r" (usingFpu),
		[contextStacked] "r" (contextStacked)
	);


	// uint32_t 
	asm volatile (
	"main_interrupt_end:\n\t"
	"BX			LR"
	);
}