#include <iostream>
#include <iomanip>
#include <stdio.h>
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
        	
	//std::cout << "Read debug registers" << std::endl;
	
	//std::cout << "Device select = 0x" << std::hex << std::setw(8) << std::setfill('0')  << * device_select << std::endl;
	//std::cout << "IOReg         = 0x" << std::hex << std::setw(8) << std::setfill('0')  << *ioreg << std::endl;
	
	uint8_t dmaDev_select = * device_select & 0x3;	

	
	std::cout << "==============================================" << std::endl;
	std::cout << "DMA Wishbone Component selection" << std::endl;
	std::cout << "==============================================" << std::endl;
	
	std::cout << std::endl << std::endl;

	std::cout << "Component previously selected: ";
	switch(dmaDev_select)
	{
		case 0   : std::cout << "Dummy RAM" << std::endl;break;
		case 1   : std::cout << "DDR3 RAM" << std::endl;break;
		case 2   : std::cout << "Dummy address to data" << std::endl;break;
		case 3   : std::cout << "Dummy deadbeef data" << std::endl;break;
		default : std::cout << "WTF !!" << std::endl;break;
	}
	
	std::cout << std::endl << std::endl;
		
	std::cout << "Select the DMA Wishbone component" << std::endl;
	std::cout << "0: Dummy RAM selected" << std::endl;
	std::cout << "1: DDR3 RAM selected" << std::endl;
	std::cout << "2: Dummy address to data" << std::endl;
	std::cout << "3: Dummy deadbeef data" << std::endl;
	
	char key = getchar();
	key = key - 0x30;
	if(key >= 0 && key <= 3)
	{
		*device_select = (*device_select & 0x3) + key;
		std::cout << "DMA wishbone bus connected the component : ";
	}

	
	switch(key)
	{
		case 0   : std::cout << "Dummy RAM" << std::endl;break;
		case 1   : std::cout << "DDR3 RAM" << std::endl;break;
		case 2   : std::cout << "Dummy address to data" << std::endl;break;
		case 3   : std::cout << "Dummy deadbeef data" << std::endl;break;
		default : std::cout << "WTF !!" << std::endl;break;
	}
	
	return 0;
}
