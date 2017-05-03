# Simple-FIR-filters
This repository stores the C++ and python implementation of some simple FIR filters. 

The filter convolves a sinc function with the signal to do the filtering. The sinc function are truncated by different windowing functions for a finite impulse response. Five windowing functions are avaliable in the program:
  1. Rectangular window: w[n] = 1, 0 < n <= N
  2. Hanning window: w[n] = 0.5 - 0.5cos(2*pi*n/(N-1)), 0 < n <= N 
  3. Hamming window: w[n] = 0.54 - 0.46cos(2*pi*n/(N-1)), 0 < n <= N 
  4. Gaussian window: w[n] = exp(-(5n/(N-1))^2/2), 0 < n <= N
  5. Blackman window: w[n] = 0.42 - 0.5cos(2*pi*n/(N-1)) - 0.08cos(2*pi*n/(N-1)), 0 < n <= N
The program will prompt the user to choose a window. Enter the name of the window in lower case, e.g. "gaussian". The rectangular window is chosen by default.

The program will then ask the user for the value of the cut-off frequency and width of transition band. Here, the cut-off frequency would be the -6 dB point in the frequency response where the gain is 0.5. It is supposed to be a normalized frequency value in (0,1). The width of transition band is lso in normalized frequency from 0 to 1. The program will calculate the best kernel size according to the desired width of transition band.

The program will also ask for the number of samples in the signal. Then, the program will read the data fro a file called "signal.txt" and do the filtering. The output signal is written to a file called "output.txt".
