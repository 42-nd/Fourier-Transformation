#pragma once
#ifndef FT_H
#define FT_H

#include <iomanip>
#include <vector>
#include <complex>
#include <functional>

#define PI 3.1415926535897932

using namespace std;

class FourierTransform {
public:
    FourierTransform(vector<complex<double>> data) : data(data), N(data.size()) {}

    vector<complex<double>> DFT();
    vector<complex<double>> IDFT();
    vector<complex<double>> FFT();
    vector<complex<double>> IFFT();

    void change_data(vector<complex<double>> new_data);

private:
	vector<complex<double>> data;
    int N;
};



#endif