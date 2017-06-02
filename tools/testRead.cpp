#include <SpecController.h>
#include <iostream>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv) {
    int specNum = 0;
    if (argc == 2)
        specNum = atoi(argv[1]);
    SpecController mySpec(specNum);
    std::string tmp;
    //const size_t size = 8550;
    const size_t size = 32;
    const size_t offsetNb = 8;
    

    uint32_t *resp[offsetNb];// = new uint32_t[size];

    for (unsigned i=0; i<offsetNb;i++) {
    	resp[i] = new uint32_t[size];
        memset(resp[i], size*4, 0x5A);
    }

    std::cout << "Starting DMA read test ..." << std::endl;

    
    for (uint32_t i=0; i<offsetNb;i++) {
        mySpec.readDma(i*2, resp[i], size); 
    }


    //mySpec.readDma(0x0, resp[0], size); 
    std::cout << "... read " << size * 4 << " byte." << std::endl;
    
    for (unsigned j=0; j<offsetNb;j++) {
        std::cout << std::endl << "== Read from the address [64 bit]: " << j << std::endl;
        for (unsigned i=0; i<size; i=i+2) { 
	   std::cout << "[" << i/2 + j << "] " << std::hex  << resp[j][i];
           std::cout << std::hex  << resp[j][i+1] << std::endl;
        }
    }
    
    for (unsigned i=0; i<offsetNb;i++) {
       delete[] resp[i];
    }

    return 0;
}
