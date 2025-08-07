#include "utils/audio_utils.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>

namespace song_processor {
namespace utils {

std::vector<float> AudioUtils::convertToFloat(const std::vector<int16_t>& input) {
    std::vector<float> output(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = static_cast<float>(input[i]) / 32768.0f;
    }
    return output;
}

std::vector<float> AudioUtils::convertToFloat(const std::vector<int32_t>& input) {
    std::vector<float> output(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = static_cast<float>(input[i]) / 2147483648.0f;
    }
    return output;
}

std::vector<int16_t> AudioUtils::convertToInt16(const std::vector<float>& input) {
    std::vector<int16_t> output(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        float clamped = std::max(-1.0f, std::min(1.0f, input[i]));
        output[i] = static_cast<int16_t>(clamped * 32767.0f);
    }
    return output;
}

std::vector<int32_t> AudioUtils::convertToInt32(const std::vector<float>& input) {
    std::vector<int32_t> output(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        float clamped = std::max(-1.0f, std::min(1.0f, input[i]));
        output[i] = static_cast<int32_t>(clamped * 2147483647.0f);
    }
    return output;
}

std::vector<float> AudioUtils::normalize(const std::vector<float>& input, float targetLevel) {
    if (input.empty()) return input;
    
    double peak = calculatePeak(input);
    if (peak <= 0.0) return input;
    
    float scale = targetLevel / static_cast<float>(peak);
    std::vector<float> output(input.size());
    
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] * scale;
    }
    
    return output;
}

std::vector<float> AudioUtils::fadeIn(const std::vector<float>& input, double durationMs) {
    std::vector<float> output = input;
    int fadeSamples = msToSamples(static_cast<int>(durationMs), 44100); // Assuming 44.1kHz
    
    for (int i = 0; i < std::min(fadeSamples, static_cast<int>(input.size())); ++i) {
        float fade = static_cast<float>(i) / fadeSamples;
        output[i] *= fade;
    }
    
    return output;
}

std::vector<float> AudioUtils::fadeOut(const std::vector<float>& input, double durationMs) {
    std::vector<float> output = input;
    int fadeSamples = msToSamples(static_cast<int>(durationMs), 44100); // Assuming 44.1kHz
    
    for (int i = 0; i < std::min(fadeSamples, static_cast<int>(input.size())); ++i) {
        float fade = static_cast<float>(fadeSamples - i) / fadeSamples;
        output[output.size() - 1 - i] *= fade;
    }
    
    return output;
}

std::pair<std::vector<float>, std::vector<float>> AudioUtils::splitStereo(const std::vector<float>& stereo) {
    std::vector<float> left, right;
    left.reserve(stereo.size() / 2);
    right.reserve(stereo.size() / 2);
    
    for (size_t i = 0; i < stereo.size(); i += 2) {
        left.push_back(stereo[i]);
        if (i + 1 < stereo.size()) {
            right.push_back(stereo[i + 1]);
        }
    }
    
    return {left, right};
}

std::vector<float> AudioUtils::mergeStereo(const std::vector<float>& left, const std::vector<float>& right) {
    std::vector<float> stereo;
    stereo.reserve(left.size() + right.size());
    
    size_t maxSize = std::max(left.size(), right.size());
    for (size_t i = 0; i < maxSize; ++i) {
        stereo.push_back(i < left.size() ? left[i] : 0.0f);
        stereo.push_back(i < right.size() ? right[i] : 0.0f);
    }
    
    return stereo;
}

std::vector<float> AudioUtils::monoToStereo(const std::vector<float>& mono) {
    std::vector<float> stereo;
    stereo.reserve(mono.size() * 2);
    
    for (float sample : mono) {
        stereo.push_back(sample); // Left channel
        stereo.push_back(sample); // Right channel
    }
    
    return stereo;
}

std::vector<float> AudioUtils::stereoToMono(const std::vector<float>& stereo) {
    std::vector<float> mono;
    mono.reserve(stereo.size() / 2);
    
    for (size_t i = 0; i < stereo.size(); i += 2) {
        float left = stereo[i];
        float right = (i + 1 < stereo.size()) ? stereo[i + 1] : 0.0f;
        mono.push_back((left + right) * 0.5f);
    }
    
    return mono;
}

double AudioUtils::calculateRMS(const std::vector<float>& input) {
    if (input.empty()) return 0.0;
    
    double sum = 0.0;
    for (float sample : input) {
        sum += sample * sample;
    }
    
    return sqrt(sum / input.size());
}

double AudioUtils::calculatePeak(const std::vector<float>& input) {
    if (input.empty()) return 0.0;
    
    double peak = 0.0;
    for (float sample : input) {
        peak = std::max(peak, static_cast<double>(std::abs(sample)));
    }
    
    return peak;
}

double AudioUtils::calculateDynamicRange(const std::vector<float>& input) {
    if (input.empty()) return 0.0;
    
    double peak = calculatePeak(input);
    double rms = calculateRMS(input);
    
    return (peak > 0.0) ? 20.0 * log10(peak / rms) : 0.0;
}

std::vector<double> AudioUtils::calculateSpectrum(const std::vector<float>& input, int fftSize) {
    // TODO: Implement actual FFT-based spectrum calculation
    // This is a placeholder that returns a simple frequency response
    std::vector<double> spectrum(fftSize / 2);
    for (int i = 0; i < fftSize / 2; ++i) {
        spectrum[i] = 0.1 * exp(-static_cast<double>(i) / 100.0);
    }
    return spectrum;
}

int AudioUtils::samplesToMs(int samples, int sampleRate) {
    return static_cast<int>((static_cast<double>(samples) / sampleRate) * 1000.0);
}

int AudioUtils::msToSamples(int ms, int sampleRate) {
    return static_cast<int>((static_cast<double>(ms) / 1000.0) * sampleRate);
}

double AudioUtils::samplesToSeconds(int samples, int sampleRate) {
    return static_cast<double>(samples) / sampleRate;
}

int AudioUtils::secondsToSamples(double seconds, int sampleRate) {
    return static_cast<int>(seconds * sampleRate);
}

bool AudioUtils::isValidAudioData(const std::vector<float>& input) {
    if (input.empty()) return false;
    
    for (float sample : input) {
        if (std::isnan(sample) || std::isinf(sample)) {
            return false;
        }
    }
    
    return true;
}

bool AudioUtils::isClipping(const std::vector<float>& input) {
    for (float sample : input) {
        if (std::abs(sample) > 1.0f) {
            return true;
        }
    }
    return false;
}

std::vector<float> AudioUtils::preventClipping(const std::vector<float>& input, float threshold) {
    std::vector<float> output = input;
    float maxSample = 0.0f;
    
    for (float sample : input) {
        maxSample = std::max(maxSample, std::abs(sample));
    }
    
    if (maxSample > threshold) {
        float scale = threshold / maxSample;
        for (float& sample : output) {
            sample *= scale;
        }
    }
    
    return output;
}

} // namespace utils
} // namespace song_processor 