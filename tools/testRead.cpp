#include <SpecController.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv) {
    int specNum = 0;
    if (argc == 2)
       specNum = atoi(argv[1]);
    SpecController mySpec(specNum);
    
    std::ofstream myfile;
    myfile.open("testRead.out");

    const size_t size = 40000;
    //const size_t size = 8550;
    //const size_t offsetNb = 8;
    

    uint32_t * resp = new uint32_t[size];

    std::cout << "Starting DMA read test ..." << std::endl;

    


    mySpec.readDma(0x0, resp, size); 
    std::cout << "... read " << size * 4 << " byte." << std::endl;
   
    
    for (unsigned i=0; i<size; i=i+2) { 
      //std::cout << "[" << i/2 << "] " << std::hex  << resp[i];
      //std::cout << std::hex  << resp[i+1] << std::endl;
      myfile << "[" << i/2 << "] " << std::hex  << resp[i];
      myfile << std::hex  << resp[i+1] << "\t"; 
      if ((i/2 - 1)%4 == 0) myfile << std::endl;
    }
    
    myfile.close();
    delete resp;

    return 0;
}
