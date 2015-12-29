#ifndef _HAL_HPP
#define _HAL_HPP

#include <cstdint>

#define CORTEX_M4F

#ifdef CORTEX_M4F
#include "archs/cortexm4f/Defines.hpp"
#include "archs/cortexm4f/Timer.hpp"
#include "archs/cortexm4f/MainIRQ.hpp"

#endif

#endif /* _HAL_HPP */
