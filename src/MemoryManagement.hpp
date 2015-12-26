#ifndef _MEMORY_MANAGEMENT_HPP
#define _MEMORY_MANAGEMENT_HPP

#include <cstdint>
#include "hal/Hal.hpp"
#include "Utility.hpp"

namespace MemoryManagement {

/**
 * @brief Allocates memory for a task
 * @details will return nullptr if there is no space to allocate
 * @param size size of memory to allocate
 * @return pointer to start of memory
 */
void* talloc(uint32_t size);

void* kmalloc(uint32_t size);



}

#endif /* _MEMORY_MANAGEMENT_HPP */
