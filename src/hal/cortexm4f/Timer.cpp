#include "Timer.hpp"
#include "inc/hw_memmap.h"
#include "driverlib/systick.h"

void osTimerSet(void (*fn)(void), uint32_t timeMicros) {
	uint32_t numCycles = timeMicros * 80;

	SysTickPeriodSet(numCycles);
	SysTickIntRegister(fn);
}

void osTimerEnable() {
	SysTickEnable();
}

void osTimerDisable() {
	SysTickDisable();
}
