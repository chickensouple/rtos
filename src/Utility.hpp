#ifndef _UTILITY_HPP
#define _UTILITY_HPP

#include <cstdint>
#include "hal/Hal.hpp"

namespace Utility {

uint8_t* wordAlign(uint8_t* addr);
uint32_t wordAlign(uint32_t size);

}

#endif /* _UTILITY_HPP */
