#include "utils/math_utils.hpp"
#include <algorithm>
#include <cmath>
#include <random>
#include <numeric>

namespace song_processor {
namespace utils {

// Mathematical constants are defined in the header

double MathUtils::clamp(double value, double min, double max) {
    return std::max(min, std::min(max, value));
}

float MathUtils::clamp(float value, float min, float max) {
    return std::max(min, std::min(max, value));
}

int MathUtils::clamp(int value, int min, int max) {
    return std::max(min, std::min(max, value));
}

double MathUtils::lerp(double a, double b, double t) {
    return a + t * (b - a);
}

float MathUtils::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

double MathUtils::smoothstep(double edge0, double edge1, double x) {
    double t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return t * t * (3.0 - 2.0 * t);
}

double MathUtils::smootherstep(double edge0, double edge1, double x) {
    double t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

double MathUtils::dbToLinear(double db) {
    return std::pow(10.0, db / 20.0);
}

double MathUtils::linearToDb(double linear) {
    return 20.0 * std::log10(std::max(linear, 1e-10));
}

double MathUtils::frequencyToMidi(double frequency) {
    return 12.0 * std::log2(frequency / 440.0) + 69.0;
}

double MathUtils::midiToFrequency(double midiNote) {
    return 440.0 * std::pow(2.0, (midiNote - 69.0) / 12.0);
}

std::vector<float> MathUtils::hanningWindow(int size) {
    std::vector<float> window(size);
    for (int i = 0; i < size; ++i) {
        window[i] = 0.5f * (1.0f - std::cos(2.0f * PI * i / (size - 1)));
    }
    return window;
}

std::vector<float> MathUtils::hammingWindow(int size) {
    std::vector<float> window(size);
    for (int i = 0; i < size; ++i) {
        window[i] = 0.54f - 0.46f * std::cos(2.0f * PI * i / (size - 1));
    }
    return window;
}

std::vector<float> MathUtils::blackmanWindow(int size) {
    std::vector<float> window(size);
    for (int i = 0; i < size; ++i) {
        window[i] = 0.42f - 0.5f * std::cos(2.0f * PI * i / (size - 1)) + 0.08f * std::cos(4.0f * PI * i / (size - 1));
    }
    return window;
}

std::vector<float> MathUtils::kaiserWindow(int size, double beta) {
    std::vector<float> window(size);
    double i0_beta = std::cyl_bessel_i(0, beta);
    
    for (int i = 0; i < size; ++i) {
        double x = 2.0 * i / (size - 1) - 1.0;
        window[i] = static_cast<float>(std::cyl_bessel_i(0, beta * std::sqrt(1.0 - x * x)) / i0_beta);
    }
    return window;
}

double MathUtils::mean(const std::vector<double>& data) {
    if (data.empty()) return 0.0;
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double MathUtils::variance(const std::vector<double>& data) {
    if (data.size() < 2) return 0.0;
    
    double m = mean(data);
    double sum = 0.0;
    for (double value : data) {
        sum += (value - m) * (value - m);
    }
    return sum / (data.size() - 1);
}

double MathUtils::standardDeviation(const std::vector<double>& data) {
    return std::sqrt(variance(data));
}

double MathUtils::median(const std::vector<double>& data) {
    if (data.empty()) return 0.0;
    
    std::vector<double> sorted = data;
    std::sort(sorted.begin(), sorted.end());
    
    size_t size = sorted.size();
    if (size % 2 == 0) {
        return (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
    } else {
        return sorted[size / 2];
    }
}

std::vector<std::complex<double>> MathUtils::complexMultiply(const std::vector<std::complex<double>>& a, 
                                                           const std::vector<std::complex<double>>& b) {
    size_t size = std::min(a.size(), b.size());
    std::vector<std::complex<double>> result(size);
    
    for (size_t i = 0; i < size; ++i) {
        result[i] = a[i] * b[i];
    }
    
    return result;
}

std::vector<double> MathUtils::magnitude(const std::vector<std::complex<double>>& complex) {
    std::vector<double> result(complex.size());
    for (size_t i = 0; i < complex.size(); ++i) {
        result[i] = std::abs(complex[i]);
    }
    return result;
}

std::vector<double> MathUtils::phase(const std::vector<std::complex<double>>& complex) {
    std::vector<double> result(complex.size());
    for (size_t i = 0; i < complex.size(); ++i) {
        result[i] = std::arg(complex[i]);
    }
    return result;
}

std::vector<double> MathUtils::butterworthCoefficients(int order, double cutoff, double sampleRate) {
    // Placeholder implementation
    std::vector<double> coeffs(order + 1, 1.0);
    return coeffs;
}

std::vector<double> MathUtils::chebyshevCoefficients(int order, double cutoff, double sampleRate, double ripple) {
    // Placeholder implementation
    std::vector<double> coeffs(order + 1, 1.0);
    return coeffs;
}

std::vector<double> MathUtils::ellipticCoefficients(int order, double cutoff, double sampleRate, double ripple, double stopband) {
    // Placeholder implementation
    std::vector<double> coeffs(order + 1, 1.0);
    return coeffs;
}

bool MathUtils::isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int MathUtils::nextPowerOfTwo(int n) {
    if (n <= 0) return 1;
    
    int power = 1;
    while (power < n) {
        power <<= 1;
    }
    return power;
}

int MathUtils::log2(int n) {
    if (n <= 0) return 0;
    return 31 - __builtin_clz(n);
}

double MathUtils::random(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

std::vector<double> MathUtils::randomVector(int size, double min, double max) {
    std::vector<double> result(size);
    for (int i = 0; i < size; ++i) {
        result[i] = random(min, max);
    }
    return result;
}

std::vector<double> MathUtils::add(const std::vector<double>& a, const std::vector<double>& b) {
    size_t size = std::min(a.size(), b.size());
    std::vector<double> result(size);
    
    for (size_t i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
    
    return result;
}

std::vector<double> MathUtils::multiply(const std::vector<double>& a, const std::vector<double>& b) {
    size_t size = std::min(a.size(), b.size());
    std::vector<double> result(size);
    
    for (size_t i = 0; i < size; ++i) {
        result[i] = a[i] * b[i];
    }
    
    return result;
}

std::vector<double> MathUtils::scale(const std::vector<double>& data, double factor) {
    std::vector<double> result(data.size());
    
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] * factor;
    }
    
    return result;
}

double MathUtils::dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    size_t size = std::min(a.size(), b.size());
    double result = 0.0;
    
    for (size_t i = 0; i < size; ++i) {
        result += a[i] * b[i];
    }
    
    return result;
}

} // namespace utils
} // namespace song_processor 