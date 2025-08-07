#pragma once

#include <vector>
#include <complex>
#include <cmath>

namespace song_processor {
namespace utils {

class MathUtils {
public:
    // Mathematical constants
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double TWO_PI = 2.0 * PI;
    static constexpr double HALF_PI = PI / 2.0;
    
    // Basic math operations
    static double clamp(double value, double min, double max);
    static float clamp(float value, float min, float max);
    static int clamp(int value, int min, int max);
    
    // Linear interpolation
    static double lerp(double a, double b, double t);
    static float lerp(float a, float b, float t);
    
    // Smoothing functions
    static double smoothstep(double edge0, double edge1, double x);
    static double smootherstep(double edge0, double edge1, double x);
    
    // Conversion functions
    static double dbToLinear(double db);
    static double linearToDb(double linear);
    static double frequencyToMidi(double frequency);
    static double midiToFrequency(double midiNote);
    
    // Window functions
    static std::vector<float> hanningWindow(int size);
    static std::vector<float> hammingWindow(int size);
    static std::vector<float> blackmanWindow(int size);
    static std::vector<float> kaiserWindow(int size, double beta);
    
    // Statistical functions
    static double mean(const std::vector<double>& data);
    static double variance(const std::vector<double>& data);
    static double standardDeviation(const std::vector<double>& data);
    static double median(const std::vector<double>& data);
    
    // Signal processing math
    static std::vector<std::complex<double>> complexMultiply(const std::vector<std::complex<double>>& a, 
                                                           const std::vector<std::complex<double>>& b);
    static std::vector<double> magnitude(const std::vector<std::complex<double>>& complex);
    static std::vector<double> phase(const std::vector<std::complex<double>>& complex);
    
    // Filter design helpers
    static std::vector<double> butterworthCoefficients(int order, double cutoff, double sampleRate);
    static std::vector<double> chebyshevCoefficients(int order, double cutoff, double sampleRate, double ripple);
    static std::vector<double> ellipticCoefficients(int order, double cutoff, double sampleRate, double ripple, double stopband);
    
    // FFT helpers
    static bool isPowerOfTwo(int n);
    static int nextPowerOfTwo(int n);
    static int log2(int n);
    
    // Random number generation
    static double random(double min = 0.0, double max = 1.0);
    static std::vector<double> randomVector(int size, double min = 0.0, double max = 1.0);
    
    // Vector operations
    static std::vector<double> add(const std::vector<double>& a, const std::vector<double>& b);
    static std::vector<double> multiply(const std::vector<double>& a, const std::vector<double>& b);
    static std::vector<double> scale(const std::vector<double>& data, double factor);
    static double dotProduct(const std::vector<double>& a, const std::vector<double>& b);
};

} // namespace utils
} // namespace song_processor 