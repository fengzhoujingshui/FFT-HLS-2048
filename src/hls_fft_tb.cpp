#include <iostream>
#include <fstream>
#include <vector>
#include "hls_fft.h"

int main() {
    // Preparation of FFT sample data
    std::fstream fin("wave.txt");
    std::vector<float> vec_data;
    float num;
    int freq=0;
    int nfft = 11;
    int data_size = 1 << nfft; // Perform 32-point FFT
    for (int i = 0; i < data_size; i++) {
        fin >> num;
        vec_data.push_back(num);
    }

    // Writing FFT sample data to the stream
    fft_stream input_data, output_data;
    for (int i = 0; i < data_size; i++) {
        data_t in_data;
        in_data.data = vec_data[i];
        in_data.last = (i == data_size - 1);
        input_data.write(in_data);
    }

    // FFT Execution
    hls_fft(input_data, output_data, nfft);

    // Reading FFT results from a stream
    data_t dout;
    do {
        dout = output_data.read();
        float out = abs(dout.data)/2048;
        if(out>0.5 && freq<=1024){
        	std::cout <<"振幅为：" << out << "，频率为：" << freq << "\n";
        }
        freq += 1;
//        std::cout << out << ", ";

    } while (!dout.last);


}
