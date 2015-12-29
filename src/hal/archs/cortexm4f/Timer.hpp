#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <cstdint>

void osTimerSet(void (*fn)(void), uint32_t timeMicros);

void osTimerEnable();

void osTimerDisable();

#endif /* _TIMER_HPP */
