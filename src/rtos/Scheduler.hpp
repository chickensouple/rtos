#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include "common/Task.hpp"

namespace Scheduler {

void init(void);

void run(void);

Task* getCurrentTask(void);

Task* getNextTask(void);

void idle(void*);

}

#endif /* _SCHEDULER_HPP */
