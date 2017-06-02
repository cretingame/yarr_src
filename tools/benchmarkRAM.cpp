#include <iostream>
#include "SpecDevice.h"
#include <Exception.h>
#include <sys/time.h>
#include <string.h>

using namespace specDriver;
using namespace std;

int main(void) {

        SpecDevice *spec;
	
	//const size_t memorySize = 2^15; // 32k*4 bytes
	//const size_t memorySize = 2^13; // 8k*4 bytes
	const size_t memorySize = 512; // 512*4 bytes
	//const size_t memorySize = 256; // 256*4 bytes
	int maxLoops = memorySize;
	int maxCycles = 50;

	double overall_time = 0;
	double overall_data = 0;

	timeval start, end;
	
	cout << endl << "==========================================" << endl;
	cout << "== Simple RAM benchmark" << endl;
	cout << endl << "==========================================" << endl;
	
        try {
                spec = new SpecDevice(0);
        } catch (Exception &e) {
                std::cerr << __PRETTY_FUNCTION__ << " -> " << e.toString() << std::endl;
                throw Exception(Exception::INIT_FAILED);
                return -1;
        }
        spec->open();
	
	void *bar0;

	try { 
		bar0 = spec->mapBAR(0);
                std::cout << __PRETTY_FUNCTION__ << " -> Mapped BAR0 at 0x" << std::hex << bar0
			<< " with size 0x" << spec->getBARsize(0) << std::dec << std::endl;
	}
	catch (Exception &e){
		std::cerr << __PRETTY_FUNCTION__ << " -> " << e.toString() << std::endl;
                throw Exception(Exception::INIT_FAILED);
                return -1;
	}

	//*((uint32_t*) bar0 ) = 0xA5A5A5A5;
	//*((uint32_t*) bar0+1) = 0x5A5A5A5A;
	cout << endl << "==========================================" << endl;
	cout << "Starting Write Benchmark:" << endl;

	for(int cycles=0;cycles<maxCycles;cycles++)
	{
		// Write to RAM
		gettimeofday(&start, NULL);
		for(int loops=0;loops<maxLoops;loops++)
		{
			*((uint32_t*) bar0+loops) = 0xA5A5A5A5;
		}
		gettimeofday(&end,NULL);

		// Analyze time
		double total_data = memorySize*4/1024.0; // in KiloBytes
		double time = (end.tv_sec - start.tv_sec) * 1000.0; //milliseconds
		time = time + (end.tv_usec - start.tv_usec) / 1000.0; // milliseconds

		overall_time = overall_time + time;
		overall_data = overall_data + total_data;
		cout << "Transfered " << total_data << "KB in " << time << " ms: " 
			<< total_data/time*1000.0/1024.0 << " MB/s" << endl;
	}
	
	cout << "==========================================" << endl;
	cout << " --> Mean Transfer Speed: " << overall_data/overall_time*1000.0/1024.0 << " MB/s" << endl;
	cout << "==========================================" << endl;

	
	cout << endl << "==========================================" << endl;
	cout << "Starting Read Benchmark:" << endl;
	
	overall_time = 0;
        overall_data = 0;
	
	for(int cycles=0;cycles<maxCycles;cycles++)
	{
		uint32_t data[memorySize];
		memset(data,0x5A, memorySize*4);
		// read from RAM
		gettimeofday(&start, NULL);
		for(int loops=0;loops<maxLoops;loops++)
		{
			data[loops] = *((uint32_t*) bar0+loops);
		}
		gettimeofday(&end,NULL);

		// Analyze time
		double total_data = memorySize*4/1024.0; // in KiloBytes
		double time = (end.tv_sec - start.tv_sec) * 1000.0; //milliseconds
		time = time + (end.tv_usec - start.tv_usec) / 1000.0; // milliseconds

		overall_time = overall_time + time;
		overall_data = overall_data + total_data;
		cout << "Transfered " << total_data << "KB in " << time << " ms: " 
			<< total_data/time*1000.0/1024.0 << " MB/s" << endl;
	}
	
	cout << "==========================================" << endl;
	cout << " --> Mean Transfer Speed: " << overall_data/overall_time*1000.0/1024.0 << " MB/s" << endl;
	cout << "==========================================" << endl;

}
