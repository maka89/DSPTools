#include <boost/circular_buffer.hpp>
namespace dsptools_nobuf {
	// Convert milliseconds ->  number of samples.
	static size_t msToSamples(double ms, double sr) { return (size_t)round(ms * sr / 1000.0); }

	// Convert number of samples  ->  milliseconds.
	static double samplesToMs(size_t n_samples, double sr) { return 1000.0 * n_samples / sr; }

	class Abstract {
	public:
		
		void setup(double fs, double ms, double default_value = 0.0) {
			size_t bsize = msToSamples(ms, fs);
			setup(fs, bsize, default_value);

		}

		void setup(double fs, size_t buf_size, double default_value = 0.0) {
			this->fs = fs;
			this->buffer_size = buf_size;
			this->bufsize_ms = samplesToMs(buffer_size, fs);
			reset(default_value);
		}

		//Reset buffers. Buffers are filled with value val.
		void reset(double val = 0.0) {
			this->val = val;
		}

		 template <class T>  T process(const boost::circular_buffer<T> &buf) { return buf[0]; };


	protected:
		Abstract() {  setup(48000.0, 1.0); }
		size_t getBufSize() { return buffer_size; }
		double getBufSizeMs() { return bufsize_ms; }

		double fs, bufsize_ms, val;
		size_t buffer_size;
	};

	//Simple moving average
	class MovingAverage :public Abstract {
	public:

		// fs - sample rate[Hz]
		// window - window size[ms]
		// default value - buffers are initially filled with this value.
		void setup(double fs, double window, double default_value = 0.0) { Abstract::setup(fs, window, default_value); }

		// fs - sample rate[Hz]
		// window - window size [number of samples]
		// default value - buffers are initially filled with this value.
		void setup(double fs, size_t window_size, double default_value = 0.0) { Abstract::setup(fs, window_size, default_value); }

		//Process single sample.
		// Input is reference to a circular_buffer. Size must be greater than window_size.
		// Last element is assumed to be current sample.
		template <class T>  T process(const boost::circular_buffer<T> &buf) {
			size_t n = buf.size() - 1;
			this->val = this->val + (buf[n] - buf[n - getWindowSamples()]) / getWindowSamples();
			return this->val;
		};

		//Averaging window in number of samples
		size_t getWindowSamples() { return getBufSize(); }

		//Averaging window in ms
		double getWindowMs() { return getBufSizeMs(); }

	};

	//Delay
	class SingleDelay : public Abstract {
	public:

		// fs - sample rate [Hz].
		// delay -  delay [ms].
		void setup(double fs, double delay, double default_value = 0.0) { Abstract::setup(fs, delay, default_value); }

		// fs - sample rate [Hz].
		// delay -  delay in samples.
		void setup(double fs, size_t delay_samples, double default_value = 0.0) { Abstract::setup(fs, delay_samples, default_value); }


		//Process single sample.
		// Input is reference to a circular_buffer. Size must be greater than window_size.
		// Last element is assumed to be current sample.
		template <class T>  T process(const boost::circular_buffer<T>& buf) {
			size_t n = buf.size() - 1;
			this->val = buf[n - getDelaySamples()];
			return this->val;
		};

		//Delay in number of samples.
		size_t getDelaySamples() { return getBufSize(); }
		//Delay in milliseconds.
		double getDelay() { return getBufSizeMs(); }

	};
}