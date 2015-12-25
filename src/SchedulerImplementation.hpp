
template <uint32_t N>
Scheduler<N>::Scheduler() :
	_taskIdx(0),
	_running(false) { }

template <uint32_t N>
bool Scheduler<N>::addTask(void (*fn)(void*), 
	uint32_t stackSize, 
	uint32_t heapSize, 
	void* var) {

	if (_running) {
		return false;
	}

	if (_taskIdx >= N) {
		return false;
	}

	stackSize = Utility::wordAlign(stackSize);
	heapSize = Utility::wordAlign(heapSize);

	void* memoryBorder = MemoryManagement::talloc(stackSize + heapSize);

	if (memoryBorder == nullptr) {
		return false;
	}

	_tasks[_taskIdx++] = { Task::READY, fn, memoryBorder, stackSize, heapSize };

	return true;
}

template <uint32_t N>
void Scheduler<N>::run() {
	_running = true;
}


