#include <SpecController.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>
// Sleep
#include <chrono>
#include <thread>

int main(int argc, char **argv) {
    int specNum = 0;
    if (argc == 2)
       specNum = atoi(argv[1]);
    SpecController mySpec(specNum);

    std::ofstream myfile;
    myfile.open("testRead.out");   
 
    const size_t size = 4096;
    //const size_t size = 2048;
    //const size_t size = 8550;
    const uint32_t offset = 0x0;
    const unsigned testIterationsNb = 100000;
   
    uint32_t *data = new uint32_t[size];
    for(unsigned i=0; i<size;i=i+2)
    {
        data[i]   = 0xDEAD0000 + i/2;
        data[i+1] = 0xBEEF0000 + i/2;
    }

    

    uint32_t * resp = new uint32_t[size];
    memset(resp, size*4, 0x5A);
    
    mySpec.writeDma(offset, data, size);
    std::cout << "... writing " << size * 4 << " byte." << std::endl;
    
    std::cout << "Starting DMA read test ..." << std::endl;

    unsigned i = 0;
    int error = 0;
    while(i < testIterationsNb) {  
      error = mySpec.readDma(offset, resp, size); 
      std::cout << i << ": ... read " << size * 4 << " byte." << std::endl;
      if (error != 0 ) i = testIterationsNb;
      i++;
      std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    

   
    
      for (unsigned i=0; i<size; i=i+2) { 
        myfile << "[" << i/2 + offset/2 << "] " << std::hex  << resp[i];
        myfile << std::hex  << resp[i+1] << "\t"; 
        if ((i/2 - 1)%4 == 0) myfile << std::endl;
      }

    myfile.close();
    delete[] resp;
    delete[] data;
    return 0;
}
