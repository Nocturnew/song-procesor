#include "song_processor.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== Song Processor Library Demo ===" << std::endl;
    
    try {
        // Create audio loader
        song_processor::audio::AudioLoader loader;
        
        // Load a test audio file (generates a test tone)
        std::string filename = "test_audio.wav";
        auto audioData = loader.loadFromFile(filename);
        
        if (audioData) {
            std::cout << "Audio loaded successfully!" << std::endl;
            std::cout << "Sample Rate: " << audioData->sampleRate << " Hz" << std::endl;
            std::cout << "Channels: " << audioData->channels << std::endl;
            std::cout << "Bits per Sample: " << audioData->bitsPerSample << std::endl;
            std::cout << "Number of Samples: " << audioData->samples.size() << std::endl;
            
            // Demonstrate audio utilities
            std::cout << "\n--- Audio Analysis ---" << std::endl;
            double rms = song_processor::utils::AudioUtils::calculateRMS(audioData->samples);
            double peak = song_processor::utils::AudioUtils::calculatePeak(audioData->samples);
            double dynamicRange = song_processor::utils::AudioUtils::calculateDynamicRange(audioData->samples);
            
            std::cout << "RMS Level: " << rms << std::endl;
            std::cout << "Peak Level: " << peak << std::endl;
            std::cout << "Dynamic Range: " << dynamicRange << " dB" << std::endl;
            
            // Check for clipping
            bool isClipping = song_processor::utils::AudioUtils::isClipping(audioData->samples);
            std::cout << "Is Clipping: " << (isClipping ? "Yes" : "No") << std::endl;
            
            // Demonstrate stereo processing
            std::cout << "\n--- Stereo Processing ---" << std::endl;
            auto [left, right] = song_processor::utils::AudioUtils::splitStereo(audioData->samples);
            std::cout << "Split stereo into " << left.size() << " left samples and " << right.size() << " right samples" << std::endl;
            
            // Demonstrate normalization
            std::cout << "\n--- Audio Processing ---" << std::endl;
            auto normalized = song_processor::utils::AudioUtils::normalize(audioData->samples, 0.8f);
            double newPeak = song_processor::utils::AudioUtils::calculatePeak(normalized);
            std::cout << "Normalized peak level: " << newPeak << std::endl;
            
            // Demonstrate fade effects
            auto fadedIn = song_processor::utils::AudioUtils::fadeIn(audioData->samples, 1000.0); // 1 second fade-in
            auto fadedOut = song_processor::utils::AudioUtils::fadeOut(audioData->samples, 1000.0); // 1 second fade-out
            std::cout << "Applied fade-in and fade-out effects" << std::endl;
            
            // Demonstrate filter functionality
            std::cout << "\n--- Filter Processing ---" << std::endl;
            song_processor::signal::Filter filter;
            
            // Test setCutoffFrequency functionality
            std::cout << "Testing setCutoffFrequency..." << std::endl;
            filter.setCutoffFrequency(1000.0); // Set to 1kHz
            std::cout << "Cutoff frequency set to: " << filter.getCutoffFrequency() << " Hz" << std::endl;
            
            // Design and apply a low-pass filter
            filter.designLowPass(2000.0, audioData->sampleRate, 4);
            std::cout << "Designed low-pass filter with cutoff: " << filter.getCutoffFrequency() << " Hz" << std::endl;
            std::cout << "Filter type: " << static_cast<int>(filter.getType()) << std::endl;
            std::cout << "Filter order: " << filter.getOrder() << std::endl;
            
            // Apply the filter
            auto filtered = filter.apply(audioData->samples);
            std::cout << "Applied low-pass filter to " << filtered.size() << " samples" << std::endl;
            
            // Test different filter types
            std::cout << "\n--- Testing Different Filter Types ---" << std::endl;
            
            // High-pass filter
            filter.designHighPass(500.0, audioData->sampleRate, 2);
            std::cout << "High-pass filter cutoff: " << filter.getCutoffFrequency() << " Hz" << std::endl;
            
            // Band-pass filter
            filter.designBandPass(500.0, 2000.0, audioData->sampleRate, 4);
            std::cout << "Band-pass filter: " << filter.getCutoffFrequency() << " Hz to " << (filter.getCutoffFrequency() * 2) << " Hz" << std::endl;
            
            // Notch filter
            filter.designNotch(1000.0, audioData->sampleRate, 10.0);
            std::cout << "Notch filter at: " << filter.getCutoffFrequency() << " Hz with Q: " << filter.getQ() << std::endl;
            
            // Test parameter setting
            std::cout << "\n--- Testing Parameter Setting ---" << std::endl;
            filter.setCutoffFrequency(1500.0);
            std::cout << "Updated cutoff frequency to: " << filter.getCutoffFrequency() << " Hz" << std::endl;
            
            filter.setQ(5.0);
            std::cout << "Updated Q to: " << filter.getQ() << std::endl;
            
            filter.setOrder(6);
            std::cout << "Updated order to: " << filter.getOrder() << std::endl;
            
            std::cout << "\nLibrary demo completed successfully!" << std::endl;
            
        } else {
            std::cout << "Failed to load audio file: " << filename << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 