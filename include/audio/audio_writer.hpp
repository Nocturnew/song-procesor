#pragma once

#include "audio_loader.hpp"
#include <string>

namespace song_processor {
namespace audio {

class AudioWriter {
public:
    AudioWriter();
    ~AudioWriter();
    
    // Write audio to file
    bool writeToFile(const AudioData& audioData, const std::string& filename);
    
    // Write audio to memory
    std::vector<uint8_t> writeToMemory(const AudioData& audioData, const std::string& format);
    
    // Get supported output formats
    std::vector<std::string> getSupportedFormats() const;
    
    // Check if output format is supported
    bool isFormatSupported(const std::string& format) const;
    
    // Set quality settings
    void setQuality(int quality); // 0-100
    void setBitrate(int bitrate); // kbps

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace audio
} // namespace song_processor 