#ifndef _CORE_HPP
#define _CORE_HPP

#include "hal/Hal.hpp"
#include "common/Task.hpp"

namespace Core {

extern void* KernelStackPtr;
extern Task TaskArr[NUM_TASKS];


}


#endif /* _CORE_HPP */
