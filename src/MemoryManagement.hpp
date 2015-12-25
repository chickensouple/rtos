#ifndef _MEMORY_MANAGEMENT_HPP
#define _MEMORY_MANAGEMENT_HPP

#include <cstdint>
#include "hal/Hal.hpp"
#include "Utility.hpp"

namespace MemoryManagement {

void* talloc(uint32_t size);

void* kmalloc(uint32_t size);



}

#endif /* _MEMORY_MANAGEMENT_HPP */
