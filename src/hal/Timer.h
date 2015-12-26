#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void schedulerTimerSet(void (*fn)(void), uint32_t timeMicros);

void schedulerTimerEnable();

void schedulerTimerDisable();

#ifdef __cplusplus
}
#endif

#endif /* _TIMER_H */
