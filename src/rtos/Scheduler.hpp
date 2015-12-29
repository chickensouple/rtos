#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include "common/Task.hpp"

extern "C" {

namespace Scheduler {

void init(void);

void run(void);

void schedule(Task** currTask, Task**  nextTask);

void idle(void*);

}

}

#endif /* _SCHEDULER_HPP */
