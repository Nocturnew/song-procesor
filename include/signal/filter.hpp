#pragma once

#include <vector>
#include <complex>

namespace song_processor {
namespace signal {

enum class FilterType {
    LOW_PASS,
    HIGH_PASS,
    BAND_PASS,
    BAND_STOP,
    NOTCH
};

class Filter {
public:
    Filter();
    ~Filter();
    
    // Design filters
    void designLowPass(double cutoffFreq, double sampleRate, int order = 4);
    void designHighPass(double cutoffFreq, double sampleRate, int order = 4);
    void designBandPass(double lowFreq, double highFreq, double sampleRate, int order = 4);
    void designBandStop(double lowFreq, double highFreq, double sampleRate, int order = 4);
    void designNotch(double frequency, double sampleRate, double Q = 10.0);
    
    // Apply filter to audio data
    std::vector<float> apply(const std::vector<float>& input);
    
    // Get frequency response
    std::vector<std::complex<double>> getFrequencyResponse(int numPoints = 1024);
    
    // Filter parameters
    void setCutoffFrequency(double freq);
    void setQ(double q);
    void setOrder(int order);
    
    // Get filter info
    FilterType getType() const;
    double getCutoffFrequency() const;
    double getQ() const;
    int getOrder() const;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace signal
} // namespace song_processor 