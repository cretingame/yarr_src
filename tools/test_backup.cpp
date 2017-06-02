#include <SpecController.h>
#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <string.h>

using namespace std;

int main(int argc, char **argv) {
    int specNum = 0;
    if (argc == 2)
        specNum = atoi(argv[1]);
    SpecController mySpec(specNum);
    std::string tmp;
    const size_t size = 0x800;
    unsigned int err_count = 0;
   
    unsigned int address=0;
    unsigned int offset = 0x00;
 
    uint32_t *data = new uint32_t[size];
    uint32_t *resp = new uint32_t[size];

    cout << "Starting DMA write/read test ..." << std::endl;
    memset(data,0x5A,size*4);
    memset(resp,0xA5,size*4);
    
    cout << "memset Ok !" << endl;

    //mySpec.write32(0xC,&data[0]);

    for (unsigned int i=0; i<size; i++) {
	address = offset + i;
        data[i] = 0x5A000000 + i;
	mySpec.write32(address,&data[i]);
	//mySpec.read32(address,&resp[i]);
	//mySpec.read32(address,&resp[i]);
	//cout << "Addr: " << hex << address << endl;
    }

    for (unsigned int i=0; i<size; i++) {
	address = offset + i;
        //data[i] = 0x5A000000 + i;
	//mySpec.write32(address,&data[i]);
	//mySpec.read32(address,&resp[i]);
	mySpec.read32(address,&resp[i]);
	//cout << "Addr: " << hex << address << endl;
    }

    for (unsigned i=0; i<size; i=i+4) {
        address = offset + i;
        std::cout << "[" << dec << address << "] " << "[" << hex << address << "]   " 
          << setfill('0') << setw(8) << hex << resp[i+0] << " "
          << setfill('0') << setw(8) << hex << resp[i+1] << " "
          << setfill('0') << setw(8) << hex << resp[i+2] << " "
          << setfill('0') << setw(8) << hex << resp[i+3]
          <<  endl;
    }

    if (err_count == 0)
        std::cout << "Success! No errors." << std::endl;
    
    delete[] data;
    delete[] resp;

    return 0;
}
