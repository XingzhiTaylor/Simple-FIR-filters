#define _USE_MATH_DEFINES
#include<iostream>
#include<fstream>
#include<math.h>
#include<string>

double sinc(double x){
	if(x == 0) return 1;
	return sin(M_PI*x)/(M_PI*x);
}

int main(){
	std::string name = " ";
	std::cout << "Please enter the desired window name: ";
	getline(std::cin,name);
	double Wc;
	std::cout << "Please enter the desired cut-off frequency: ";
	std::cin >> Wc;
	double trans_width;
	std::cout << "Please enter the desired width of the transition band: ";
	std::cin >> trans_width;
	trans_width *= M_PI;
	int data_length;
	std::cout << "Please enter the length of the raw signal: ";
	std::cin >> data_length;

	//Tell the program the date length and the window size

	std::ifstream infile("signal.txt");
	int i = 0;
	double test_data[data_length];
	while(!infile.eof() && i < data_length){
		infile >> test_data[i];
		i++;
	}

	//Dynamically allocate an array for the input

	double x,window,filter;
	int kernel_length,boundary;
	double* kernel;

	if(name == "hanning"){
		kernel_length = int(6.65*M_PI/trans_width);
		if(kernel_length % 2 == 0) kernel_length++;
		boundary = (kernel_length-1)/2;

		kernel = new double[kernel_length];

		for(int i = 0; i < kernel_length; i++){
			x = i - double(boundary);
			window = 0.5 + 0.5 * cos(2*M_PI*x/(kernel_length-1));
			filter = sinc(x*Wc)*Wc;
			kernel[i] = window*filter;
		}	

	}else if(name == "hamming"){
		kernel_length = int(6.22*M_PI/trans_width);
		if(kernel_length % 2 == 0) kernel_length++;
		boundary = (kernel_length-1)/2;

		kernel = new double[kernel_length];

		for(int i = 0; i < kernel_length; i++){
			x = i - double(boundary);
			window = 0.54 + 0.46 * cos(2*M_PI*x/(kernel_length-1));
			filter = sinc(x*Wc)*Wc;
			kernel[i] = window*filter;
		}

	}else if(name == "gaussian"){
		kernel_length = int(8.52*M_PI/trans_width);
		if(kernel_length % 2 == 0) kernel_length++;
		boundary = (kernel_length-1)/2;
		
		kernel = new double[kernel_length];

		for(int i = 0; i < kernel_length; i++){
			x = i - double(boundary);
			window = exp(-pow(x/(((double)kernel_length-1)/5),2)/2);
			filter = sinc(x*Wc)*Wc;
			kernel[i] = window*filter;
		}

	}else if(name == "blackman"){
		kernel_length = int(11.1*M_PI/trans_width);
		if(kernel_length % 2 == 0) kernel_length++;
		boundary = (kernel_length-1)/2;
		
		kernel = new double[kernel_length];

		for(int i = 0; i < kernel_length; i++){
			x = i - double(boundary);
			window = window = 0.42 + 0.5 * cos(2*M_PI*x/(kernel_length-1)) + 0.08 * cos(4*M_PI*x/(kernel_length-1));
			filter = sinc(x*Wc)*Wc;
			kernel[i] = window*filter;
		}
			
	}else{
		std::cerr << "Invalid window name" << std::endl;
		return -1;
	}

	//Calculate the kernel

    double filtered[data_length+kernel_length-1];
    for(int i = 0; i < data_length+kernel_length-1; i++){
    	filtered[i] = 0;
        for(int j = 0; j < kernel_length; j++){
            if(i - j < 0){
                filtered[i] += 0;
            }else if(i - j >= data_length){
                filtered[i] += 0;
            }else{
                filtered[i] += kernel[j] * test_data[i - j];
            }
        }
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