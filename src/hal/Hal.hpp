#ifndef _HAL_HPP
#define _HAL_HPP

#include <cstdint>

#define CORTEX_M4F

#ifdef CORTEX_M4F
#include "cortexm4f/Defines.hpp"
#include "cortexm4f/Timer.hpp"
#include "cortexm4f/IRQHandlers.hpp"
#include "cortexm4f/Context.hpp"

#endif

#endif /* _HAL_HPP */
