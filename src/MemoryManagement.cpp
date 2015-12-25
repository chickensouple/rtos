#include "MemoryManagement.hpp"

namespace MemoryManagement {

uint8_t kernelTaskMemory[KernelTaskMemorySize];
uint8_t* kernelTaskMemoryPtr = kernelTaskMemory;
uint8_t kernelHeap[KernelHeapSize];

void* talloc(uint32_t size) {
	void* ret = kernelTaskMemoryPtr;


	uint8_t* newTaskMemoryPtr = kernelTaskMemoryPtr + size;
	if (newTaskMemoryPtr - kernelTaskMemoryPtr >= KernelTaskMemorySize) {
		return nullptr;
	}
	
	kernelTaskMemoryPtr = Utility::wordAlign(newTaskMemoryPtr);

	return ret;
}

void* kmalloc(uint32_t size) {
	return nullptr;
}


} // MemoryManagement
