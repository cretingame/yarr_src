#include <SpecController.h>
#include <iostream>
#include <stdint.h>
#include <string.h>

using namespace std;

int main(int argc, char **argv) {
    int specNum = 0;
    if (argc == 2)
        specNum = atoi(argv[1]);
    SpecController mySpec(specNum);
    std::string tmp;
    const size_t size = 4*1024;
    unsigned int err_count = 0;
   
    unsigned int offset = 0x0;
    unsigned int address=0;
 
    uint32_t *data = new uint32_t[size];
    uint32_t *resp = new uint32_t[size];

    cout << "Starting DMA write/read test ..." << std::endl;
    //memset(data,0x5A,size*4);
    memset(resp,0xA5,size*4);
    
    cout << "memset Ok !" << endl;

    //mySpec.write32(0xC,&data[0]);

    for (int j=0;j<4;j++) {
	    for (unsigned int i=0; i<size; i++) {
		address = offset + i + j*size;
		//mySpec.write32(address,&data[i]);
		mySpec.read32(address,&resp[i]);
		//cout << "Addr: " << hex << address << endl;
	    }

	    for (unsigned i=0; i<size; i++) {
		if (resp[i] == 0x00811556) {
		    address = offset + i + j*size;
		    std::cout << "[" << address << "] " << "[" << hex << address << "]  \t " << hex << resp[i] << std::endl << std::dec;
		}
	    }
    }

    if (err_count == 0) { 
        std::cout << "Success! No errors." << std::endl;
    }
    else {
        std::cout << err_count  << " errors." << std::endl;
    }
    
    delete[] data;
    delete[] resp;

    return 0;
}
