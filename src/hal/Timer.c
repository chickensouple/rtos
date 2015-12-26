#include "Timer.h"
#include "inc/hw_memmap.h"
#include "driverlib/systick.h"

void schedulerTimerSet(void (*fn)(void), uint32_t timeMicros) {
	uint32_t numCycles = timeMicros * 80;

	SysTickPeriodSet(numCycles);
	SysTickIntRegister(fn);
}

void schedulerTimerEnable() {
	SysTickEnable();
}

void schedulerTimerDisable() {
	SysTickDisable();
}
