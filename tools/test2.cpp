#include <iostream>
#include "SpecDevice.h"
#include <Exception.h>

using namespace specDriver;

int main(void) {

	SpecDevice *spec;	
	try {
		spec = new SpecDevice(0);
	} catch (Exception &e) {
		std::cerr << __PRETTY_FUNCTION__ << " -> " << e.toString() << std::endl;
		throw Exception(Exception::INIT_FAILED);
		return -1;
	}
	spec->open();
	
	void *bar0, *bar2, *bar4;
	try {
		bar0 = spec->mapBAR(0);
		std::cout << __PRETTY_FUNCTION__ << " -> Mapped BAR0 at 0x" << std::hex << bar0 
			<< " with size 0x" << spec->getBARsize(0) << std::dec << std::endl;
		bar2 = spec->mapBAR(2);
		std::cout << __PRETTY_FUNCTION__ << " -> Mapped BAR0 at 0x" << std::hex << bar0 
			<< " with size 0x" << spec->getBARsize(0) << std::dec << std::endl;
		//bar2 = spec->mapBAR(2);
		//std::cout << __PRETTY_FUNCTION__ << " -> Mapped BAR2 at 0x" << std::hex << bar2 
		//	<< " with size 0x" << spec->getBARsize(2) << std::dec << std::endl;
		//bar4 = spec->mapBAR(3);
		//std::cout << __PRETTY_FUNCTION__ << " -> Mapped BAR2 at 0x" << std::hex << bar2 
		//	<< " with size 0x" << spec->getBARsize(3) << std::dec << std::endl;
	} catch (Exception &e) {
		std::cerr << __PRETTY_FUNCTION__ << " -> " << e.toString() << std::endl;
		throw Exception(Exception::INIT_FAILED);
		return -1;
	}
	

	for (unsigned int i=0; i<32; i++) {
		*((uint32_t*) bar0+i) = 0xA5 + i;
		//std::cout << "[" << i << "] " << std::hex << (unsigned)spec->readConfigByte(i) << std::dec << std::endl;
	}
	
	
	for (unsigned int i=0; i<32; i++) {
		std::cout << "[" << i << "] " << std::hex << *((uint32_t*) bar0+i) << std::dec << std::endl;
		//std::cout << "[" << std::hex << i << "] " << std::hex << (unsigned)spec->readConfigByte(i) << std::dec << std::endl;
	}

	return 0;
}
