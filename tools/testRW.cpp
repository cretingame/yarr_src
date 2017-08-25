#include <SpecController.h>
#include <iostream>
#include <iomanip>
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
 
    //const size_t size = 131072;
    //const size_t size = 65536;
    const size_t size = 4096;
    //const size_t size = 2048;
    //const size_t size = 8550;
    uint32_t offset = 0x0;
    //const unsigned testIterationsNb = 65533;
    const unsigned testIterationsNb = 200000;
    const bool errorOnly = true;

    unsigned err_count = 0;
    std::string respColorString;
   
    uint32_t *data = new uint32_t[size];
    for(unsigned i=0; i<size;i=i+2)
    {
        data[i]   = 0xDEAD0000 + i/2;
        data[i+1] = 0xBABE0000 + i/2;
    }

    

    
    
    std::cout << "Starting DMA read test ..." << std::endl;

    uint32_t * resp = new uint32_t[size];
    unsigned j = 0;
    int error = 0;
    while(j < testIterationsNb) {   
      delete resp;
      resp = new uint32_t[size];
      memset(resp, size*4, 0x5A);
      mySpec.writeDma(offset, data, size);
      error = mySpec.readDma(offset, resp, size); 
      //std::cout << "\r" << j << ": ... write and read " << size * 4 << " byte.";
      //std::cout.flush();
	    for (unsigned i=0; i<size; i++) {
		if (data[i] != resp[i]) {
		    err_count++;
		    respColorString = "\e[31m";
		    if(errorOnly) {
			std::cout << "\e[7m[" << std::setw(4)  << i << "]\e[2m " << std::setw(8) << std::hex << data[i] 
                        << " \e[0m " << std::setw(8) << resp[i] << " "; // error only
			if(err_count%4 == 0) std::cout << std::endl; //error only
		    }
		}
		else {
		   respColorString = "\e[0m";
		}
		if(!errorOnly) {
		   std::cout << "\e[7m[" << std::setw(4)  << i << "]\e[2m " << std::setw(8) << std::hex << data[i] 
                   << " \e[0m" << respColorString << std::setw(8)  << resp[i] << "\e[0m ";
		   if((i+1)%4 == 0) std::cout << std::endl; // all the data
		}
	    }


      if (error != 0 or err_count != 0) { 
        std::cout << "Error at iteration number:" << j << std::endl;
        j = testIterationsNb;
      }
      j++;
      //std::this_thread::sleep_for(std::chrono::seconds(15));
    }
    

   
    
      for (unsigned i=0; i<size; i=i+2) { 
        myfile << "[" << i/2 + offset/2 << "] " << std::hex  << resp[i];
        myfile << std::hex  << resp[i+1] << "\t"; 
        if ((i/2 - 1)%4 == 0) myfile << std::endl;
      }
    std::cout << "FINISH !!" << (j - 1) << std::endl;

    myfile.close();
    delete resp;
    delete data;
    return 0;
}
