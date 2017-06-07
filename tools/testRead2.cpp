#include <SpecController.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv) {
    int specNum = 0;
    if (argc == 2)
        specNum = atoi(argv[1]);
    SpecController mySpec(specNum);
    //const size_t size = 16777216;
    //const size_t size = 2097152;
    //const size_t size = 1048576;
    //const size_t size = 524288;
    //const size_t size = 262144;
    //const size_t size = 131072;
    //const size_t size = 65536; // may crash
    //const size_t size = 32768; // ok
    //const size_t size = 16384; // ok
    //const size_t size = 512;
    //const size_t size = 256;
    const size_t size = 128;
    //const size_t size = 8000;
    const unsigned testIterationsNb = 64;

    uint32_t offset = 0x00000000;
    
    std::cout << "Read Write test program" << std::endl;
	 
    uint32_t *data = new uint32_t[size];
    for(unsigned i=0; i<size;i=i+2)
    {
        data[i]   = 0xDEAD0000 + i/2;
	data[i+1] = 0xBEEF0000 + i/2;
    }

    std::string fileName = "testRead";
    std::ofstream * myfile[testIterationsNb];
    uint32_t *resp[testIterationsNb];
    for (unsigned i=0; i<testIterationsNb;i++) {
      resp[i] = new uint32_t[size];
      memset(resp[i], size*4, 0x5A);
      myfile[i] = new std::ofstream();
      fileName = "testRead_" + std::to_string(i) + ".out";
      myfile[i]->open(fileName);
    }



    std::cout << "Starting DMA write/read test ..." << std::endl;
    
    mySpec.writeDma(offset, data, size); 
    std::cout << "... writing " << size * 4 << " byte." << std::endl;

    unsigned i = 0;
    int error = 0;
    while(i < testIterationsNb) {
      error = mySpec.readDma(offset, resp[i], size);
      std::cout << i << ": ... read " << size * 4 << " byte." << std::endl;
      if (error != 0 ) i = testIterationsNb;
      i++;
    }

    

    for (unsigned j=0; j<testIterationsNb; j++) {
      for (unsigned i=0; i<size; i=i+2) {
        *myfile[j] << "[" << i/2 + offset/2 << "] " << std::hex  << resp[j][i];
        *myfile[j] << std::hex  << resp[j][i+1] << "\t";
        if ((i/2 - 1)%4 == 0) *myfile[j] << std::endl;
      }
    }
    

    
    delete[] data;
    //delete[] resp;
    for (unsigned i=0; i<testIterationsNb;i++) {
       delete[] resp[i];
       myfile[i]->close();
    }

    
    

    return 0;
}
