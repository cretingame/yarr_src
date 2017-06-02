#include <SpecController.h>
#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv) {
    int specNum = 0;
    if (argc == 2)
        specNum = atoi(argv[1]);
    SpecController mySpec(specNum);
    std::string tmp;
    //const size_t size = 16777216;
    //const size_t size = 2097152;
    //const size_t size = 1048576;
    //const size_t size = 524288;
    //const size_t size = 262144;
    //const size_t size = 131072;
    const size_t size = 65536; // may crash
    //const size_t size = 32768; // ok
    //const size_t size = 16384; // ok
    //const size_t size = 512;
    //const size_t size = 256;
    //const size_t size = 128;
    //const size_t size = 8000;
    const bool errorOnly = true;    

    unsigned err_count = 0;
    uint32_t address = 0x00000000;
    
    std::cout << "Read Write test program" << std::endl;
	 
    uint32_t *data = new uint32_t[size];
    for(unsigned i=0; i<size;i=i+2)
    {
        data[i]   = 0xDEAD0000 + i/2;
	data[i+1] = 0xBEEF0000 + i/2;
    }

    uint32_t *resp = new uint32_t[size];

    std::cout << "Starting DMA write/read test ..." << std::endl;
    memset(resp, size*4, 0x5A);
    
    mySpec.writeDma(address, data, size); 
    std::cout << "... writing " << size * 4 << " byte." << std::endl;
    mySpec.readDma(address, resp, size); 
    std::cout << "... read " << size * 4 << " byte." << std::endl;
    
    char * respColorString;

    for (unsigned i=0; i<size; i++) {
        if (data[i] != resp[i]) {
            err_count++;
	    respColorString = "\e[31m";
            if(errorOnly) {
		std::cout << "\e[7m[" << std::setw(4)  << i << "]\e[2m " << std::setw(8) << std::hex << data[i] << " \e[0m " << std::setw(8) << resp[i] << " "; // error only
                if(err_count%4 == 0) std::cout << std::endl; //error only
            }
        }
	else {
	   respColorString = "\e[0m";
	}
	if(!errorOnly) {
           std::cout << "\e[7m[" << std::setw(4)  << i << "]\e[2m " << std::setw(8) << std::hex << data[i] << " \e[0m" << respColorString << std::setw(8)  << resp[i] << "\e[0m ";
           if((i+1)%4 == 0) std::cout << std::endl; // all the data
        }
    }

    if (err_count == 0)
        std::cout << "\e[1m\e[32m" << "Success! No errors." << std::endl;
    else
	std::cout << std::endl << "\e[1m\e[31m" << std::dec << err_count << " errors." << std::endl;
    
    delete[] data;
    delete[] resp;
    
    std::cout << "\e[0m";

    return 0;
}
