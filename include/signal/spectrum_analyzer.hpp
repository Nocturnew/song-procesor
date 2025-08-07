#pragma once

#include <vector>
#include <complex>
#include <string>

namespace song_processor {
namespace signal {

struct SpectrumData {
    std::vector<double> frequencies;
    std::vector<double> magnitudes;
    std::vector<double> phases;
    double sampleRate;
    int fftSize;
};

class SpectrumAnalyzer {
public:
    SpectrumAnalyzer();
    ~SpectrumAnalyzer();
    
    // Analyze audio spectrum
    SpectrumData analyze(const std::vector<float>& input);
    
    // Real-time spectrum analysis
    void update(const std::vector<float>& input);
    SpectrumData getCurrentSpectrum() const;
    
    // Configuration
    void setFFTSize(int size);
    void setWindowType(const std::string& windowType);
    void setOverlap(double overlap); // 0.0 to 1.0
    
    // Get analysis parameters
    int getFFTSize() const;
    std::string getWindowType() const;
    double getOverlap() const;
    
    // Spectrum processing
    std::vector<double> getFrequencyBands(const std::vector<double>& frequencies, int numBands = 10);
    std::vector<double> getSpectralCentroid(const SpectrumData& spectrum);
    std::vector<double> getSpectralRolloff(const SpectrumData& spectrum, double percentile = 0.85);
    
    // Peak detection
    std::vector<int> findSpectralPeaks(const SpectrumData& spectrum, double threshold = 0.1);
    std::vector<double> getPeakFrequencies(const SpectrumData& spectrum, const std::vector<int>& peakIndices);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace signal
} // namespace song_processor 