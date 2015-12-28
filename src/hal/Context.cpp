#include "Context.hpp"

extern Context* schedule(void);

void interruptHandler(void) {
	asm(
	"MOV		R0,SP\n\t" // read stack pointer
	"SUB		SP,SP,#12\n\t" // allocate a space to store current stack pointer
	"STR		R0,[SP,#8]\n\t"  // store current stack pointer
	"ADD		R0,SP,#4\n\t" // give first operand into schedule function
	"ADD		R1,SP,#0\n\t" // give second operand into schedule function
	"BL			schedule\n\t" // call scheduler, return will be in R0
	// compare context addresses
	"LDR		R0,[SP,#4]\n\t" // old context*
	"LDR		R1,[SP,#0]\n\t" // new context*
	"CMP 		R0,R1\n\t"
	// if same, do nothing
	"BEQ		interrupt_handler_end\n\t"
	// else save and load contexts
	"LDR		R2,[SP,#8]\n\t"
	// save context 
	"LDR		R3,[R2,#0]\n\t" // Save R0
	"STR 		R3,[R0,#0]\n\t"
	"LDR		R3,[R2,#4]\n\t" // Save R1
	"STR 		R3,[R0,#4]\n\t"
	"LDR		R3,[R2,#8]\n\t" // Save R2
	"STR 		R3,[R0,#8]\n\t"
	"LDR		R3,[R2,#12]\n\t" // Save R3
	"STR 		R3,[R0,#12]\n\t"
	"STR 		R4,[R0,#16]\n\t" // Save R4
	"STR 		R5,[R0,#20]\n\t" // Save R5
	"STR 		R6,[R0,#24]\n\t" // Save R6
	"STR 		R7,[R0,#28]\n\t" // Save R7
	"STR 		R8,[R0,#32]\n\t" // Save R8
	"STR 		R9,[R0,#36]\n\t" // Save R9
	"STR 		R10,[R0,#40]\n\t" // Save R10
	"STR 		R11,[R0,#44]\n\t" // Save R11
	"LDR		R3,[R2,#16]\n\t" // Save R12
	"STR 		R3,[R0,#48]\n\t"
	"LDR		R3,[R2,#20]\n\t" // Save LR
	"STR 		R3,[R0,#52]\n\t"
	"LDR		R3,[R2,#24]\n\t" // Save PC
	"STR 		R3,[R0,#56]\n\t"
	"LDR		R3,[R2,#28]\n\t" // Save XPSR
	"STR 		R3,[R0,#60]\n\t"


	"ADD		R3,R2,#32\n\t" // saving SP
	"STR 		R3,[R0,#64]\n\t"
	);


	asm(
	"interrupt_handler_end:\n\t"
	"ADD		SP,SP,#12\n\t"
	"BX			LR\n\t");
}


// void loadContext(Context* context) {

// }


