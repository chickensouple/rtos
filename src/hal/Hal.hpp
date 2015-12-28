#ifndef _HAL_HPP
#define _HAL_HPP

#include <cstdint>

#include "Context.hpp"

const uint32_t KernelTaskMemorySize = 15360;
const uint32_t KernelHeapSize = 5120;
const uint32_t WordSize = 4; // in bytes
const uint32_t WordSizeLog2 = 2;

extern "C" {

void saveContext(Context* context);

void loadContext(Context* context);

}

#endif /* _HAL_HPP */
