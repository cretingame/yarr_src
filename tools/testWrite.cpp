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
    
    uint32_t *data = new uint32_t[size];
    for(unsigned i=0; i<size;i++)
        data[i] = 0xCACA0000 + i/2;


    std::cout << "Starting DMA write test ..." << std::endl;
    
    mySpec.writeDma(0x0, data, size); 
    std::cout << "... writing " << size * 4 << " byte." << std::endl;
    
    for (unsigned i=0; i<size; i++) {
            std::cout << "[" << i << "] " << std::hex << data[i]  << std::endl << std::dec;
    }
    delete[] data;

    return 0;
}
