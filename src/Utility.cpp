#include "Utility.hpp"

namespace Utility {

uint8_t* wordAlign(uint8_t* addr) {
	uintptr_t addrPtr = (uintptr_t) addr;
	uintptr_t alignedAddr = (addrPtr >> WordSizeLog2) << WordSizeLog2;
	if (alignedAddr < addrPtr) {
		alignedAddr += WordSize;
	}
	return (uint8_t*) alignedAddr;
}


uint32_t wordAlign(uint32_t size) {
	uint32_t alignedSize = (size >> WordSizeLog2) << WordSizeLog2;
	if (alignedSize < size) {
		alignedSize += WordSize;
	}
	return alignedSize;
}


}
