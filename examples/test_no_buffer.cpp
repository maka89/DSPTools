#include "../dsptools/dsptools_no_buffer.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip> 
using namespace std;
using namespace dsptools_nobuf;
int main() {

	unsigned int N = 10000;
	
	double fs = 48000.0;
	double window = 100.0;

	size_t n = msToSamples(window, fs) * 10;
	boost::circular_buffer<double> buf(n);
	for (size_t i = 0; i < n; i++)
		buf.push_back(0.0);
	MovingAverage m;
	m.setup(fs, window,0.0);
	ofstream myfile;
	myfile.open("example.txt");
	
	
	
	for(unsigned int i=0;i<N;i++) {
		double x = 2.0*((double)rand() )/ RAND_MAX - 1.0;
		buf.push_back(x);
		double val1 = m.process(buf);
		myfile << (float)i << ", " << setprecision(12)<< x << ", " << val1 << endl;

	}
	myfile.close();
}

