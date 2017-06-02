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
    size_t size = 512;
    //const size_t sizeMax = 16384;
    //const size_t sizeMax = 16777216;
    const size_t sizeMax = 16777216;
    const uint32_t iterationsNb = 1000;
    

    uint32_t *resp;// = new uint32_t[size];
    uint32_t *data;// = new uint32_t[size];

    data = new uint32_t[sizeMax];
    resp = new uint32_t[sizeMax];
    memset(data, sizeMax*4, 0xA5);
    memset(resp, sizeMax*4, 0x5A);

    std::cout << "Starting DMA read test ..." << std::endl;

    //uint32_t i = 0;
    int error = 0;
    int errorIteration = 0;
    /*while(i < iterationsNb and error == 0){
	//std::cout << i << " ";
        mySpec.readDma(i*2*size, resp, size);
        i=i+1;
    }*/
    for (uint32_t j = size;j <= sizeMax;j=j+2) {
	//std::cout << "Size: " << j << std::endl;
    	for(uint32_t i = 0;i < iterationsNb;i++){
		if(error != 0) {
	    		error = mySpec.writeDma(0x0/*i*2*j*/, data, (size_t)j);
                        //error = mySpec.readDma(0x0/*i*2*j*/, resp, (size_t)j);
        	}
    	}
    }

    for (uint32_t j = size;j <= sizeMax;j=j+2) {
	//std::cout << "Size: " << j << std::endl;
    	for(uint32_t i = 0;i < iterationsNb;i++){
		if(error != 0) {
	    		//error = mySpec.writeDma(0x0/*i*2*j*/, data, (size_t)j);
                        error = mySpec.readDma(0x0/*i*2*j*/, resp, (size_t)j);
        	}
    	}
    }

    
    if(error != 0) {
		std::cout << "ERROR iteration nb : " << errorIteration << "" << std::endl;
	        //i=iterationsNb;
    }


    
    
    delete resp;
    delete data;

    return 0;
}
