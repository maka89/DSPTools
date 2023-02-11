#include <boost/circular_buffer.hpp>

//Simple moving average
class MovingAverage {
public:
	MovingAverage() { setup(48000.0, 1.0); }

	// fs - sample rate[Hz]
	// window - window size[ms]
	void setup(double fs, double window,double default_value=0.0) {
		this->fs = fs;
		this->window = window;
		buffer_size = (unsigned int)round(window * fs / 1000.0);
		buf = boost::circular_buffer<double>(buffer_size);
		reset();
	}
	//Reset buffers
	void reset() {
		for (unsigned int i = 0; i < buffer_size; i++)
			buf.push_back(0.0);
		val = this->default_value;
	}
	double process(const double& inp) {
		val = val + (inp - buf[0]) / buffer_size;
		buf.push_back(inp);
		return (double)val;
	}
private:
	double fs, window, default_value;
	double val;
	unsigned int buffer_size;
	boost::circular_buffer<double> buf;
};

//Delay
class SingleDelay {
public:
	SingleDelay() { setup(48000.0, 1.0); }

	// fs - sample rate [Hz].
	// delay -  delay [ms].
	void setup(double fs, double delay) { 
		this->fs = fs;
		this->delay = delay;
		buffer_size = (unsigned int)round(delay * fs / 1000.0);

		buf = boost::circular_buffer<double>(buffer_size);
		reset();
	}
	//Reset buffers
	void reset(){ 
		for (unsigned int i = 0; i < buffer_size; i++)
			buf.push_back(0.0);
	}

	double process(const double& inp) {
		double ret = buf[0];
		buf.push_back(inp);
		return ret;
	}


private:
	double fs, delay;
	unsigned int buffer_size;
	boost::circular_buffer<double> buf;
};