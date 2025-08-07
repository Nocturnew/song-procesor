#pragma once

#include <string>
#include <vector>
#include <memory>

namespace song_processor {
namespace audio {

struct AudioData {
    std::vector<float> samples;
    int sampleRate;
    int channels;
    int bitsPerSample;
};

class AudioLoader {
public:
    AudioLoader();
    ~AudioLoader();
    
    // Load audio from file
    std::unique_ptr<AudioData> loadFromFile(const std::string& filename);
    
    // Load audio from memory
    std::unique_ptr<AudioData> loadFromMemory(const std::vector<uint8_t>& data);
    
    // Get supported formats
    std::vector<std::string> getSupportedFormats() const;
    
    // Check if format is supported
    bool isFormatSupported(const std::string& filename) const;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace audio
} // namespace song_processor 