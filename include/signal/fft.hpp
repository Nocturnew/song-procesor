#pragma once

#include <vector>
#include <complex>

namespace song_processor {
namespace signal {

class FFT {
public:
    FFT();
    ~FFT();
    
    // Forward FFT (time domain to frequency domain)
    std::vector<std::complex<double>> forward(const std::vector<float>& input);
    
    // Inverse FFT (frequency domain to time domain)
    std::vector<float> inverse(const std::vector<std::complex<double>>& input);
    
    // Set FFT size
    void setSize(int size);
    int getSize() const;
    
    // Get magnitude spectrum
    std::vector<double> getMagnitude(const std::vector<std::complex<double>>& spectrum);
    
    // Get phase spectrum
    std::vector<double> getPhase(const std::vector<std::complex<double>>& spectrum);
    
    // Window functions
    std::vector<float> applyWindow(const std::vector<float>& input, const std::string& windowType = "hanning");
    
    // Get available window types
    std::vector<std::string> getAvailableWindows() const;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace signal
} // namespace song_processor 