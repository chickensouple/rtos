#include "Core.hpp"

namespace Core {

void* KernelStackPtr = (void*) KERNEL_STACK_BORDER;

Task TaskArr[NUM_TASKS];


}