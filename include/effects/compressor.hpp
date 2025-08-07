#pragma once

#include <vector>
#include <string>

namespace song_processor {
namespace effects {

struct CompressorParameters {
    double threshold = -20.0;   // Threshold in dB
    double ratio = 4.0;        // Compression ratio
    double attack = 10.0;      // Attack time in ms
    double release = 100.0;    // Release time in ms
    double knee = 6.0;         // Knee width in dB
    double makeup = 0.0;       // Makeup gain in dB
    int sampleRate = 44100;
};

class Compressor {
public:
    Compressor();
    ~Compressor();
    
    // Apply compression
    std::vector<float> apply(const std::vector<float>& input);
    
    // Set compressor parameters
    void setParameters(const CompressorParameters& params);
    void setThreshold(double threshold);
    void setRatio(double ratio);
    void setAttack(double attack);
    void setRelease(double release);
    void setKnee(double knee);
    void setMakeupGain(double makeup);
    void setSampleRate(int sampleRate);
    
    // Get current parameters
    CompressorParameters getParameters() const;
    
    // Preset compressor types
    void setPreset(const std::string& presetName);
    std::vector<std::string> getAvailablePresets() const;
    
    // Reset compressor state
    void reset();
    
    // Side-chain compression
    void setSideChain(const std::vector<float>& sideChain);
    void enableSideChain(bool enable);
    bool isSideChainEnabled() const;
    
    // Compression metering
    double getCurrentGainReduction() const;
    double getAverageGainReduction() const;
    std::vector<double> getGainReductionHistory() const;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace effects
} // namespace song_processor 