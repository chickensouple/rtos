#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include "common/Task.hpp"

namespace Scheduler {

typedef void (*taskFunc)(void*);

void init(void);

void run(void);

Task* getCurrentTask(void);

Task* getNextTask(void);

void addTask(taskFunc task, void* args);

void idle(void*);

}

#endif /* _SCHEDULER_HPP */
