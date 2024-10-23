#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <cmath> 
#include <chrono>
#include <fstream>
#include <cstdlib>
#include "FT.h"

using namespace std;
using namespace chrono;

double epsilon = 1e-8; // Порог для округления к нулю

void save_to_file(vector<complex<double>> original_data, vector<complex<double>> filtered_data, string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Index,Original Data,Filtered Data\n"; 
        for (int i = 0; i < original_data.size(); i++) {
            file << i << "," << original_data[i].real() << "," << filtered_data[i].real() << "\n";
        }
        file.close();
        cout << "Data saved to " << filename << endl;
    }
    else {
        cout << "Unable to open file!" << endl;
    }
}


double format_value(double value) {
    return (fabs(value) < epsilon) ? 0.0 : value;
}

double calculate_amplitude(complex<double> z) {
    return sqrt(pow(z.real(), 2) + pow(z.imag(), 2));
}

double calculate_phase(complex<double> z) {
    double x = z.real();
    double y = z.imag();
    if (x > 0) {
        return atan(y / x);
    }
    else if (x < 0 && y >= 0) {
        return PI + atan(y / x);
    }
    else if (x < 0 && y < 0) {
        return atan(y / x) - PI;
    }
    else if (x == 0) {
        if (y < 0) {
            return -PI / 2;
        }
        else {
            return PI / 2;
        }
    }

}

void analyze_spectrum(vector<complex<double>> spectrum) {
    cout << "Frequency\tAmplitude\tPhase" << endl;
    for (int i = 0; i < spectrum.size(); i++) { 
        double amplitude = calculate_amplitude(spectrum[i]);
        double phase = calculate_phase(spectrum[i]);
        cout << i << "\t\t" << format_value(amplitude) << "\t\t" << format_value(phase) << endl;
    }
}

void analyze_signal(vector<complex<double>> spectrum) {
    int N = spectrum.size();
    int significant_frequencies = 0;
    double threshold = 1e-3; // Порог для значимой амплитуды

    cout << "Frequency\tAmplitude" << endl;
    for (int i = 0; i < N; i++) {
        double amplitude = calculate_amplitude(spectrum[i]);
        if (amplitude > threshold) {
            significant_frequencies++;
            cout << i << "\t\t" << amplitude << endl;
        }
    }

    cout << "\nTotal significant frequencies: " << significant_frequencies << endl;

    if (significant_frequencies < N / 4) {
        cout << "The signal is likely low-frequency." << endl;
    }
    else {
        cout << "The signal is likely high-frequency." << endl;
    }
}

int main() {
    int N = 512;
    double a, b,omega,phi;
    a = -87;
    b = 0.12;
    omega = 196;
    phi = PI/3;
    vector<complex<double>> data(N);

    for (int i = 0; i < N; i++) {
        data[i]._Val[0] = a + b * cos((2 * PI * omega * i)/N + phi);
        data[i]._Val[1] = 0;
    }

    FourierTransform transformator(data);

    auto start_dft = high_resolution_clock::now();
    vector<complex<double>> DFT_res = transformator.DFT();
    auto end_dft = high_resolution_clock::now();
    auto duration_dft = duration_cast<microseconds>(end_dft - start_dft);

    auto start_fft = high_resolution_clock::now();
    vector<complex<double>> FFT_res = transformator.FFT();
    auto end_fft = high_resolution_clock::now();
    auto duration_fft = duration_cast<microseconds>(end_fft - start_fft);

    int SETW = 15;
    cout << left << setw(SETW) << "Number"
        << left << setw(SETW) << "Re(data)"
        << left << setw(SETW) << "Re(DFT_res)"
        << left << setw(SETW) << "Im(DFT_res)"
        << left << setw(SETW) << "Amplitude"
        << left << setw(SETW) << "Phase (radians)" << endl;

    for (int i = 0; i < N; i++) {
        if (format_value(DFT_res[i].real()) != 0 || format_value(DFT_res[i].imag()) != 0) {
            cout << left << setw(SETW) << i
                << left << setw(SETW) << format_value(data[i].real())
                << left << setw(SETW) << format_value(DFT_res[i].real())
                << left << setw(SETW) << format_value(DFT_res[i].imag())
                << left << setw(SETW) << format_value(calculate_amplitude(DFT_res[i]))
                << left << setw(SETW) << format_value(calculate_phase(DFT_res[i])) << endl;
        }
    }

    cout << endl;

    cout << left << setw(SETW) << "Number"
        << left << setw(SETW) << "Re(data)"
        << left << setw(SETW) << "Re(FFT_res)"
        << left << setw(SETW) << "Im(FFT_res)"
        << left << setw(SETW) << "Amplitude"
        << left << setw(SETW) << "Phase (radians)" << endl;

    for (int i = 0; i < N; i++) {
        if (format_value(FFT_res[i].real()) != 0 || format_value(FFT_res[i].imag()) != 0) {
            cout << left << setw(SETW) << i
                << left << setw(SETW) << format_value(data[i].real())
                << left << setw(SETW) << format_value(FFT_res[i].real())
                << left << setw(SETW) << format_value(FFT_res[i].imag())
                << left << setw(SETW) << format_value(calculate_amplitude(FFT_res[i]))
                << left << setw(SETW) << format_value(calculate_phase(FFT_res[i])) << endl;
        }
    }

    cout << "Analyzing DFT spectrum..." << endl;
    analyze_signal(DFT_res);

    cout << "\nAnalyzing FFT spectrum..." << endl;
    analyze_signal(FFT_res);

    cout << "DFT time: " << duration_dft.count() << " microseconds" << endl;
    cout << "FFT time: " << duration_fft.count() << " microseconds" << endl;

    cout << "---------------------------" << endl;

    for (int i = 0; i < N; i++) {
        data[i]._Val[0] = cos((2 * PI * i) / N) + 0.01 * cos((2 * PI * omega * i) / N);
        data[i]._Val[1] = 0;
    }

    transformator.change_data(data);
    DFT_res = transformator.DFT();

    cout << "Analyzing DFT spectrum..." << endl;
    analyze_signal(DFT_res);
    DFT_res[196] = { 0, 0};
    DFT_res[316] = { 0, 0};
    transformator.change_data(DFT_res);
    vector<complex<double>> IDFT_res = transformator.IDFT();

    cout << "\nOriginal data vs filtered data (first 10 samples):" << endl;
    cout << setw(SETW) << "Index" << setw(SETW) << "Original Data" << setw(SETW) << "Filtered Data" << endl;
    for (int i = 0; i < 10; i++) {
        cout << setw(SETW) << i << setw(SETW) << format_value(data[i].real()) << setw(SETW) << format_value(IDFT_res[i].real()) << endl;
    }
    save_to_file(data, IDFT_res, "data.csv");
    system("python3 plot.py");
}
