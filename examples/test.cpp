#include "../dsptools/dsptools.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip> 
using namespace std;
int main() {

	unsigned int N = 10000;
	
	double fs = 48000.0;
	double window = 100.0;
	MovingAverage m;
	m.setup(fs, window,1.0);
	ofstream myfile;
	myfile.open("example.txt");
	
	
	
	for(unsigned int i=0;i<N;i++) {
		double x = 2.0*((double)rand() )/ RAND_MAX - 1.0;
		double val1 = m.process(x);
		myfile << (float)i << ", " << setprecision(12)<< x << ", " << val1 << endl;

	}
	myfile.close();
}