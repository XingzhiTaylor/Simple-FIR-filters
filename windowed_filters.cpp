#define _USE_MATH_DEFINES
#include<iostream>
#include<fstream>
#include<math.h>

double sinc(double x){
	if(x == 0) return 1;
	return sin(M_PI*x)/(M_PI*x);
}

int main(){
	int kernel_length;
	std::cin >> kernel_length;

	if(kernel_length%2 != 1){
		std::cerr << "The kernel length should be an odd number!" << std::endl;
		return -1;
	}

	//The kernel length should be odd

	double Wc;
	std::cin >> Wc;
	int data_length;
	std::cin >> data_length;
	
	std::cout << "What window do you need? " << std::endl;
	std::cout << "1 for Rectangular window " << std::endl;
	std::cout << "2 for Hanning window " << std::endl;
	std::cout << "3 for Hamming window " << std::endl;
	std::cout << "4 for Gaussian window " << std::endl;
	std::cout << "5 for Blackman window " << std::endl;
	
	int filter_type;
	std::cin >> filter_type;

	//Tell the program the date length and the window size

	double test_data[data_length];
	double* kernel = new double[kernel_length];

	//Dynamically allocate an array for the input

	int boundary = (kernel_length-1)/2;

	for(int i = 0; i < kernel_length; i++){
		//To be modified
		double x = i - (double)boundary;
		double window;
		switch (filter_type){
			case 1 : window = 0.5 + 0.5 * cos(2*M_PI*x/(kernel_length-1));
			case 2 : window = 0.54 + 0.46 * cos(2*M_PI*x/(kernel_length-1));
			case 3 : window = exp(-pow(x/stdev,2)/2);
			case 4 : window = 0.42 + 0.5 * cos(2*M_PI*x/(kernel_length-1)) + 0.08 * cos(4*M_PI*x/(kernel_length-1));
		}	
    	double sinc_kernel = sinc(x*Wc)*Wc;
    	kernel[i] = hamming*sinc_kernel;
	}

	//Calculate the kernel

	for(int i = 0; i < data_length; i++){
		std::cin >> test_data[i];
	}

	//Input data

	double* extended_data = new double[data_length+2*(kernel_length-1)];
	for(int i = 0; i < kernel_length-1; i++){
		extended_data[i] = 0.0;
	}
	for(int i = kernel_length-1; i < kernel_length -1 + data_length; i++){
		extended_data[i] = test_data[i - kernel_length + 1];
	}
	for(int i = kernel_length - 1 + data_length; i < data_length+2*(kernel_length-1); i++){
		extended_data[i] = 0.0;
	}

	//Pad zeros to both ends of the array for convolution

	double* filtered = new double[data_length+kernel_length-1];
	for(int i = 0; i < data_length+kernel_length-1; i++){
		double conv = 0.0;
		for(int j = 0; j < kernel_length; j++){
			conv += extended_data[j+i] * kernel[j];
		}
		filtered[i] = conv;
	}

	//Convolve the kernel and the data

	double filtered_data[data_length];
	for(int i = 0; i < data_length; i++){
		filtered_data[i] = filtered[i+(kernel_length-1)/2];
	}

	//We take only the middle part of the convolution output

	std::ofstream myfile ("/Users/xingzhizhang/Documents/MATLAB/SKA project Perth/output.txt");

    if (myfile.is_open()){
        for(int i = 0; i < data_length; i++){
        	 myfile << std::fixed << filtered_data[i] << std::endl;
        }
        myfile.close();
    }   

    //Output the filtered data into a txt file. Ths is unnecessary in real practice

	return 0;
}