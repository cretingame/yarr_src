#include <iostream>
#include <iomanip>
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
	
	void *bar0;
	try {
		bar0 = spec->mapBAR(0);
		std::cout << __PRETTY_FUNCTION__ << " -> Mapped BAR0 at 0x" << std::hex << bar0 
			<< " with size 0x" << spec->getBARsize(0) << std::dec << std::endl;
	} catch (Exception &e) {
		std::cerr << __PRETTY_FUNCTION__ << " -> " << e.toString() << std::endl;
		throw Exception(Exception::INIT_FAILED);
		return -1;
	}
        
        uint32_t * device_select = (uint32_t*) bar0+0x10;
	uint32_t * ioreg = (uint32_t*) bar0+0x11;
        	
	std::cout << "Read debug registers" << std::endl;
	
	std::cout << "Device select = 0x" << std::hex << std::setw(8) << std::setfill('0')  << * device_select << std::endl;
	std::cout << "IOReg         = 0x" << std::hex << std::setw(8) << std::setfill('0')  << *ioreg << std::endl;
	
	*ioreg = *ioreg xor 0xF;		

	return 0;
}
