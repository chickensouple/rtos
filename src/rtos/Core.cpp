#include "Core.hpp"

namespace Core {

uint8_t KernelStack[KERNEL_STACK_SIZE];
void* KernelStackPtr = &(KernelStack[KERNEL_STACK_SIZE - 1]);

Task TaskArr[NUM_TASKS];


}