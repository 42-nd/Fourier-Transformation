#include "FT.h"

void FourierTransform::change_data(const vector<complex<double>>& new_data) {
    data = new_data;
	N = new_data.size();
}

vector<complex<double>> FourierTransform::DFT() {
	vector<complex<double>> result(N);
	for (int k = 0; k < N; ++k) {
		complex<double> sum(0.0, 0.0);
		for (int n = 0; n < N; ++n) {
			double angle = -2.0 * PI * k * n / N;
			sum += data[n] * polar(1.0, angle); // e^{-j*angle}
		}
		result[k] = sum;
	}
	return result;
}

vector<complex<double>> FourierTransform::IDFT() {
	vector<complex<double>> result(N);
	for (int n = 0; n < N; ++n) {
		complex<double> sum(0.0, 0.0);
		for (int k = 0; k < N; ++k) {
			double angle = 2.0 * PI * k * n / N;
			sum += data[k] * polar(1.0, angle); // e^{j*angle}
		}
		result[n] = sum / double(N);
	}
	return result;
}

vector<complex<double>> FourierTransform::FFT(){
	int M = N / 2;
	vector<complex<double>> result(N); 
	complex<double> exp, U, V;

	for (int m = 0; m < M; m++){
		U._Val[0] = 0.0; U._Val[1] = 0.0;
		V._Val[0] = 0.0; V._Val[1] = 0.0;
		for (int n = 0; n < M; n++){
			exp._Val[0] = cos(-2.0 * PI * m * n / M);
			exp._Val[1] = sin(-2.0 * PI * m * n / M);
			U += data[2 * n] * exp;
			V += data[2 * n + 1] * exp;
		}

		exp._Val[0] = cos(-2.0 * PI * m / N);
		exp._Val[1] = sin(-2.0 * PI * m / N);
		result[m] = U + exp * V;
		result[m + M] = U - exp * V;
	}
	return result;
}



vector<complex<double>> FourierTransform::IFFT(){;
	vector<complex<double>> fft_res = FFT();
	complex<double> val;
	for (int i = 1; i <= N / 2; i++){
		val = fft_res[i];
		fft_res[i] = fft_res[N - i] / double(N);
		fft_res[N - i] = val / double(N);
	}

	fft_res[0] /= double(N);
	return fft_res;
}