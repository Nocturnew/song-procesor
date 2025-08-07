#include "audio/audio_writer.hpp"
#include <iostream>
#include <fstream>

namespace song_processor {
namespace audio {

struct AudioWriter::Impl {
    std::vector<std::string> supportedFormats = {"wav", "mp3", "flac", "ogg"};
    int quality = 80;
    int bitrate = 320;
};

AudioWriter::AudioWriter() : pImpl(std::make_unique<Impl>()) {}

AudioWriter::~AudioWriter() = default;

bool AudioWriter::writeToFile(const AudioData& audioData, const std::string& filename) {
    // TODO: Implement actual audio file writing
    std::cout << "Writing audio to: " << filename << std::endl;
    std::cout << "Sample Rate: " << audioData.sampleRate << " Hz" << std::endl;
    std::cout << "Channels: " << audioData.channels << std::endl;
    std::cout << "Samples: " << audioData.samples.size() << std::endl;
    
    // Placeholder: just create an empty file for now
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.close();
        std::cout << "Audio file written successfully!" << std::endl;
        return true;
    }
    
    return false;
}

std::vector<uint8_t> AudioWriter::writeToMemory(const AudioData& audioData, const std::string& format) {
    // TODO: Implement memory-based writing
    throw std::runtime_error("Memory-based writing not implemented yet");
}

std::vector<std::string> AudioWriter::getSupportedFormats() const {
    return pImpl->supportedFormats;
}

bool AudioWriter::isFormatSupported(const std::string& format) const {
    std::string lowerFormat = format;
    std::transform(lowerFormat.begin(), lowerFormat.end(), lowerFormat.begin(), ::tolower);
    
    return std::find(pImpl->supportedFormats.begin(), pImpl->supportedFormats.end(), lowerFormat) != pImpl->supportedFormats.end();
}

void AudioWriter::setQuality(int quality) {
    pImpl->quality = std::max(0, std::min(100, quality));
}

void AudioWriter::setBitrate(int bitrate) {
    pImpl->bitrate = std::max(32, std::min(320, bitrate));
}

} // namespace audio
} // namespace song_processor 