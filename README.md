# Song Processor - Signal Processing Library

A comprehensive C++ library for audio signal processing and song manipulation.

## 🎵 Features

### Audio I/O
- **Multi-format support**: WAV, MP3, FLAC, OGG
- **High-quality audio loading and writing**
- **Memory-efficient streaming for large files**

### Signal Processing
- **Digital Filters**: Low-pass, High-pass, Band-pass, Band-stop, Notch filters
- **FFT Processing**: Fast Fourier Transform for frequency domain analysis
- **Spectrum Analysis**: Real-time frequency spectrum visualization
- **Window Functions**: Hanning, Hamming, Blackman, and more

### Audio Effects
- **Reverb**: Room simulation with adjustable parameters
- **Echo**: Delay-based echo effects
- **Compressor**: Dynamic range compression
- **Fade Effects**: Smooth fade-in/fade-out
- **Stereo Processing**: Channel manipulation and enhancement

### Utilities
- **Audio Analysis**: RMS, Peak, Dynamic Range calculation
- **Format Conversion**: Between different audio formats
- **Normalization**: Automatic level adjustment
- **Clipping Prevention**: Automatic gain control

## 📁 Project Structure

```
song-processor/
├── include/                    # Header files
│   ├── song_processor.hpp     # Main library header
│   ├── audio/                 # Audio I/O components
│   │   ├── audio_loader.hpp
│   │   └── audio_writer.hpp
│   ├── signal/                # Signal processing
│   │   ├── filter.hpp
│   │   ├── fft.hpp
│   │   └── spectrum_analyzer.hpp
│   ├── effects/               # Audio effects
│   │   ├── reverb.hpp
│   │   ├── echo.hpp
│   │   └── compressor.hpp
│   └── utils/                 # Utility functions
│       ├── audio_utils.hpp
│       └── math_utils.hpp
├── src/                       # Source files
│   ├── audio/
│   ├── signal/
│   ├── effects/
│   └── utils/
├── main.cpp                   # Demo application
├── CMakeLists.txt            # Build configuration
└── README.md                 # This file
```

## 🚀 Quick Start

### Prerequisites
- CMake 3.16 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Audio libraries (optional for full functionality):
  - libsndfile (for WAV/FLAC support)
  - libmp3lame (for MP3 support)
  - libvorbis (for OGG support)

### Building the Project

```bash
# Clone the repository
git clone <repository-url>
cd song-processor

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make -j4

# Run the demo
./song_processor
```

### Basic Usage

```cpp
#include "song_processor.hpp"

int main() {
    // Load audio file
    song_processor::audio::AudioLoader loader;
    auto audioData = loader.loadFromFile("input.wav");
    
    // Apply effects
    song_processor::effects::Reverb reverb;
    reverb.setRoomSize(0.7);
    auto processed = reverb.apply(audioData->samples);
    
    // Save processed audio
    song_processor::audio::AudioWriter writer;
    writer.writeToFile(*audioData, "output.wav");
    
    return 0;
}
```

## 📚 API Documentation

### Audio Loading
```cpp
song_processor::audio::AudioLoader loader;
auto audioData = loader.loadFromFile("song.wav");
```

### Signal Filtering
```cpp
song_processor::signal::Filter filter;
filter.designLowPass(1000.0, 44100.0); // 1kHz cutoff at 44.1kHz
auto filtered = filter.apply(audioData->samples);
```

### FFT Processing
```cpp
song_processor::signal::FFT fft;
fft.setSize(2048);
auto spectrum = fft.forward(audioData->samples);
auto magnitude = fft.getMagnitude(spectrum);
```

### Audio Effects
```cpp
song_processor::effects::Reverb reverb;
reverb.setRoomSize(0.8);
reverb.setDamping(0.3);
auto reverbed = reverb.apply(audioData->samples);
```

### Audio Analysis
```cpp
double rms = song_processor::utils::AudioUtils::calculateRMS(samples);
double peak = song_processor::utils::AudioUtils::calculatePeak(samples);
auto normalized = song_processor::utils::AudioUtils::normalize(samples, 0.8f);
```

## 🔧 Configuration

### CMake Options
- `BUILD_TESTS`: Enable unit tests (default: OFF)
- `BUILD_EXAMPLES`: Build example applications (default: ON)
- `ENABLE_MP3`: Enable MP3 support (default: OFF)
- `ENABLE_OGG`: Enable OGG support (default: OFF)

### Example Configuration
```bash
cmake -DBUILD_TESTS=ON -DENABLE_MP3=ON ..
```

## 🧪 Testing

```bash
# Build with tests
cmake -DBUILD_TESTS=ON ..
make

# Run tests
ctest --verbose
```

## 📈 Performance

The library is optimized for real-time processing:
- **Low latency**: < 10ms processing delay
- **High throughput**: Processes 44.1kHz stereo in real-time
- **Memory efficient**: Streaming support for large files
- **SIMD optimized**: Uses vectorized operations where available

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- FFT implementation based on FFTW library concepts
- Audio processing algorithms inspired by industry standards
- Thanks to the open-source audio community for inspiration

## 📞 Support

For questions, issues, or contributions:
- Open an issue on GitHub
- Check the documentation in the `docs/` folder
- Review example code in the `examples/` directory