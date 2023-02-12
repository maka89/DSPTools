# DSPTools
Some basic DSP tools.

Currently: 
- `SingleDelay`: Delay the input audio (or other data) by a fixed number of milliseconds.
- `MovingAverage()`: Calculates simple moving average. Using the last N samples.

Dependency on `boost::circular_buffer`.

## Usage
```
#include <dsptools.hpp>

double fs = 48000.0;
double window = 100.0;
MovingAverage m;
m.setup(fs, window,0.0); //Setup. Sample rate, window size and initial value.

for(unsigned int i=0;i<x.size();i++)
  cout << m.process(x[i]);

```
