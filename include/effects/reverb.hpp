#pragma once

#include <vector>
#include <string>

namespace song_processor {
namespace effects {

struct ReverbParameters {
    double roomSize = 0.5;      // 0.0 to 1.0
    double damping = 0.5;       // 0.0 to 1.0
    double wetLevel = 0.33;     // 0.0 to 1.0
    double dryLevel = 0.4;      // 0.0 to 1.0
    double width = 1.0;         // 0.0 to 1.0
    int sampleRate = 44100;
};

class Reverb {
public:
    Reverb();
    ~Reverb();
    
    // Apply reverb effect
    std::vector<float> apply(const std::vector<float>& input);
    
    // Set reverb parameters
    void setParameters(const ReverbParameters& params);
    void setRoomSize(double roomSize);
    void setDamping(double damping);
    void setWetLevel(double wetLevel);
    void setDryLevel(double dryLevel);
    void setWidth(double width);
    void setSampleRate(int sampleRate);
    
    // Get current parameters
    ReverbParameters getParameters() const;
    
    // Preset reverb types
    void setPreset(const std::string& presetName);
    std::vector<std::string> getAvailablePresets() const;
    
    // Reset reverb state
    void reset();

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace effects
} // namespace song_processor 