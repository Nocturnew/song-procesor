#pragma once

#include <vector>
#include <string>

namespace song_processor {
namespace utils {

class AudioUtils {
public:
    // Audio format conversion
    static std::vector<float> convertToFloat(const std::vector<int16_t>& input);
    static std::vector<float> convertToFloat(const std::vector<int32_t>& input);
    static std::vector<int16_t> convertToInt16(const std::vector<float>& input);
    static std::vector<int32_t> convertToInt32(const std::vector<float>& input);
    
    // Audio manipulation
    static std::vector<float> normalize(const std::vector<float>& input, float targetLevel = 0.0f);
    static std::vector<float> fadeIn(const std::vector<float>& input, double durationMs);
    static std::vector<float> fadeOut(const std::vector<float>& input, double durationMs);
    static std::vector<float> crossfade(const std::vector<float>& input1, const std::vector<float>& input2, double durationMs);
    
    // Stereo processing
    static std::pair<std::vector<float>, std::vector<float>> splitStereo(const std::vector<float>& stereo);
    static std::vector<float> mergeStereo(const std::vector<float>& left, const std::vector<float>& right);
    static std::vector<float> monoToStereo(const std::vector<float>& mono);
    static std::vector<float> stereoToMono(const std::vector<float>& stereo);
    
    // Audio analysis
    static double calculateRMS(const std::vector<float>& input);
    static double calculatePeak(const std::vector<float>& input);
    static double calculateDynamicRange(const std::vector<float>& input);
    static std::vector<double> calculateSpectrum(const std::vector<float>& input, int fftSize = 2048);
    
    // Time utilities
    static int samplesToMs(int samples, int sampleRate);
    static int msToSamples(int ms, int sampleRate);
    static double samplesToSeconds(int samples, int sampleRate);
    static int secondsToSamples(double seconds, int sampleRate);
    
    // Audio validation
    static bool isValidAudioData(const std::vector<float>& input);
    static bool isClipping(const std::vector<float>& input);
    static std::vector<float> preventClipping(const std::vector<float>& input, float threshold = 0.99f);
};

} // namespace utils
} // namespace song_processor 