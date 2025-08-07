#pragma once

#include <vector>
#include <string>

namespace song_processor {
namespace effects {

struct EchoParameters {
    double delay = 0.5;        // Delay time in seconds
    double feedback = 0.3;     // Feedback amount (0.0 to 0.9)
    double wetLevel = 0.5;     // Wet signal level (0.0 to 1.0)
    double dryLevel = 0.7;     // Dry signal level (0.0 to 1.0)
    int sampleRate = 44100;
};

class Echo {
public:
    Echo();
    ~Echo();
    
    // Apply echo effect
    std::vector<float> apply(const std::vector<float>& input);
    
    // Set echo parameters
    void setParameters(const EchoParameters& params);
    void setDelay(double delay);
    void setFeedback(double feedback);
    void setWetLevel(double wetLevel);
    void setDryLevel(double dryLevel);
    void setSampleRate(int sampleRate);
    
    // Get current parameters
    EchoParameters getParameters() const;
    
    // Preset echo types
    void setPreset(const std::string& presetName);
    std::vector<std::string> getAvailablePresets() const;
    
    // Reset echo state
    void reset();
    
    // Multi-tap echo
    void addTap(double delay, double level);
    void clearTaps();
    std::vector<std::pair<double, double>> getTaps() const;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace effects
} // namespace song_processor 