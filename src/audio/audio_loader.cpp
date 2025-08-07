#include "audio/audio_loader.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

namespace song_processor {
namespace audio {

struct AudioLoader::Impl {
    std::vector<std::string> supportedFormats = {"wav", "mp3", "flac", "ogg"};
};

AudioLoader::AudioLoader() : pImpl(std::make_unique<Impl>()) {}

AudioLoader::~AudioLoader() = default;

std::unique_ptr<AudioData> AudioLoader::loadFromFile(const std::string& filename) {
    // TODO: Implement actual audio file loading
    // This is a placeholder implementation
    auto audioData = std::make_unique<AudioData>();
    audioData->sampleRate = 44100;
    audioData->channels = 2;
    audioData->bitsPerSample = 16;
    
    // Generate a simple test tone
    const int numSamples = 44100; // 1 second at 44.1kHz
    audioData->samples.resize(numSamples * audioData->channels);
    
    for (int i = 0; i < numSamples; ++i) {
        float sample = 0.1f * sin(2.0f * M_PI * 440.0f * i / audioData->sampleRate); // 440 Hz tone
        audioData->samples[i * 2] = sample;     // Left channel
        audioData->samples[i * 2 + 1] = sample; // Right channel
    }
    
    std::cout << "Loaded audio file: " << filename << std::endl;
    return audioData;
}

std::unique_ptr<AudioData> AudioLoader::loadFromMemory(const std::vector<uint8_t>& data) {
    // TODO: Implement memory-based loading
    throw std::runtime_error("Memory-based loading not implemented yet");
}

std::vector<std::string> AudioLoader::getSupportedFormats() const {
    return pImpl->supportedFormats;
}

bool AudioLoader::isFormatSupported(const std::string& filename) const {
    // Extract file extension
    size_t dotPos = filename.find_last_of('.');
    if (dotPos == std::string::npos) return false;
    
    std::string extension = filename.substr(dotPos + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    return std::find(pImpl->supportedFormats.begin(), pImpl->supportedFormats.end(), extension) != pImpl->supportedFormats.end();
}

} // namespace audio
} // namespace song_processor 