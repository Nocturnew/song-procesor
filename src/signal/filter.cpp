#include "signal/filter.hpp"
#include "utils/math_utils.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>

namespace song_processor {
namespace signal {

struct Filter::Impl {
    FilterType type = FilterType::LOW_PASS;
    double cutoffFrequency = 1000.0;
    double highCutoffFrequency = 2000.0; // For band-pass/band-stop
    double Q = 1.0;
    int order = 4;
    double sampleRate = 44100.0;
    
    // Filter coefficients
    std::vector<double> bCoeffs; // Numerator coefficients
    std::vector<double> aCoeffs; // Denominator coefficients
    
    // State for filtering
    std::vector<double> xHistory; // Input history
    std::vector<double> yHistory; // Output history
    
    void updateCoefficients();
    void resetHistory();
};

Filter::Filter() : pImpl(std::make_unique<Impl>()) {}

Filter::~Filter() = default;

void Filter::setCutoffFrequency(double freq) {
    pImpl->cutoffFrequency = std::max(20.0, std::min(freq, pImpl->sampleRate / 2.0));
    pImpl->updateCoefficients();
}

void Filter::setQ(double q) {
    pImpl->Q = std::max(0.1, std::min(q, 100.0));
    pImpl->updateCoefficients();
}

void Filter::setOrder(int order) {
    pImpl->order = std::max(1, std::min(order, 8));
    pImpl->updateCoefficients();
}

void Filter::designLowPass(double cutoffFreq, double sampleRate, int order) {
    pImpl->type = FilterType::LOW_PASS;
    pImpl->cutoffFrequency = cutoffFreq;
    pImpl->sampleRate = sampleRate;
    pImpl->order = order;
    pImpl->updateCoefficients();
}

void Filter::designHighPass(double cutoffFreq, double sampleRate, int order) {
    pImpl->type = FilterType::HIGH_PASS;
    pImpl->cutoffFrequency = cutoffFreq;
    pImpl->sampleRate = sampleRate;
    pImpl->order = order;
    pImpl->updateCoefficients();
}

void Filter::designBandPass(double lowFreq, double highFreq, double sampleRate, int order) {
    pImpl->type = FilterType::BAND_PASS;
    pImpl->cutoffFrequency = lowFreq;
    pImpl->highCutoffFrequency = highFreq;
    pImpl->sampleRate = sampleRate;
    pImpl->order = order;
    pImpl->updateCoefficients();
}

void Filter::designBandStop(double lowFreq, double highFreq, double sampleRate, int order) {
    pImpl->type = FilterType::BAND_STOP;
    pImpl->cutoffFrequency = lowFreq;
    pImpl->highCutoffFrequency = highFreq;
    pImpl->sampleRate = sampleRate;
    pImpl->order = order;
    pImpl->updateCoefficients();
}

void Filter::designNotch(double frequency, double sampleRate, double Q) {
    pImpl->type = FilterType::NOTCH;
    pImpl->cutoffFrequency = frequency;
    pImpl->sampleRate = sampleRate;
    pImpl->Q = Q;
    pImpl->updateCoefficients();
}

std::vector<float> Filter::apply(const std::vector<float>& input) {
    if (pImpl->bCoeffs.empty() || pImpl->aCoeffs.empty()) {
        return input; // No filter applied
    }
    
    std::vector<float> output(input.size());
    
    for (size_t i = 0; i < input.size(); ++i) {
        // Direct Form II implementation
        double x = static_cast<double>(input[i]);
        double y = 0.0;
        
        // Feed forward (numerator)
        for (size_t j = 0; j < pImpl->bCoeffs.size(); ++j) {
            if (i >= j) {
                y += pImpl->bCoeffs[j] * (i - j < pImpl->xHistory.size() ? pImpl->xHistory[i - j] : x);
            }
        }
        
        // Feed back (denominator)
        for (size_t j = 1; j < pImpl->aCoeffs.size(); ++j) {
            if (i >= j) {
                y -= pImpl->aCoeffs[j] * (i - j < pImpl->yHistory.size() ? pImpl->yHistory[i - j] : 0.0);
            }
        }
        
        // Normalize by a[0]
        y /= pImpl->aCoeffs[0];
        
        output[i] = static_cast<float>(y);
        
        // Update history
        if (pImpl->xHistory.size() <= i) {
            pImpl->xHistory.push_back(x);
        } else {
            pImpl->xHistory[i] = x;
        }
        
        if (pImpl->yHistory.size() <= i) {
            pImpl->yHistory.push_back(y);
        } else {
            pImpl->yHistory[i] = y;
        }
    }
    
    return output;
}

std::vector<std::complex<double>> Filter::getFrequencyResponse(int numPoints) {
    std::vector<std::complex<double>> response(numPoints);
    
    for (int i = 0; i < numPoints; ++i) {
        double frequency = (static_cast<double>(i) / numPoints) * pImpl->sampleRate / 2.0;
        double omega = 2.0 * MathUtils::PI * frequency / pImpl->sampleRate;
        std::complex<double> z = std::exp(std::complex<double>(0, omega));
        
        std::complex<double> numerator = 0.0;
        std::complex<double> denominator = 0.0;
        
        // Calculate numerator
        for (size_t j = 0; j < pImpl->bCoeffs.size(); ++j) {
            numerator += pImpl->bCoeffs[j] * std::pow(z, -static_cast<double>(j));
        }
        
        // Calculate denominator
        for (size_t j = 0; j < pImpl->aCoeffs.size(); ++j) {
            denominator += pImpl->aCoeffs[j] * std::pow(z, -static_cast<double>(j));
        }
        
        response[i] = numerator / denominator;
    }
    
    return response;
}

FilterType Filter::getType() const {
    return pImpl->type;
}

double Filter::getCutoffFrequency() const {
    return pImpl->cutoffFrequency;
}

double Filter::getQ() const {
    return pImpl->Q;
}

int Filter::getOrder() const {
    return pImpl->order;
}

void Filter::Impl::updateCoefficients() {
    // Reset history when coefficients change
    resetHistory();
    
    // Calculate normalized frequency
    double normalizedFreq = cutoffFrequency / sampleRate;
    double normalizedHighFreq = highCutoffFrequency / sampleRate;
    
    // Clear previous coefficients
    bCoeffs.clear();
    aCoeffs.clear();
    
    switch (type) {
        case FilterType::LOW_PASS: {
            // Simple first-order low-pass filter
            double alpha = 1.0 / (1.0 + 2.0 * MathUtils::PI * normalizedFreq);
            bCoeffs = {alpha};
            aCoeffs = {1.0, alpha - 1.0};
            break;
        }
        
        case FilterType::HIGH_PASS: {
            // Simple first-order high-pass filter
            double alpha = 1.0 / (1.0 + 2.0 * MathUtils::PI * normalizedFreq);
            bCoeffs = {1.0 - alpha};
            aCoeffs = {1.0, alpha - 1.0};
            break;
        }
        
        case FilterType::BAND_PASS: {
            // Simple band-pass filter
            double centerFreq = (cutoffFrequency + highCutoffFrequency) / 2.0;
            double bandwidth = highCutoffFrequency - cutoffFrequency;
            double normalizedCenter = centerFreq / sampleRate;
            double normalizedBandwidth = bandwidth / sampleRate;
            
            double alpha = std::tan(MathUtils::PI * normalizedBandwidth / 2.0);
            double beta = std::cos(2.0 * MathUtils::PI * normalizedCenter);
            
            double a0 = 1.0 + alpha;
            bCoeffs = {alpha / a0, 0.0, -alpha / a0};
            aCoeffs = {1.0, -2.0 * beta / a0, (1.0 - alpha) / a0};
            break;
        }
        
        case FilterType::BAND_STOP: {
            // Simple band-stop filter
            double centerFreq = (cutoffFrequency + highCutoffFrequency) / 2.0;
            double bandwidth = highCutoffFrequency - cutoffFrequency;
            double normalizedCenter = centerFreq / sampleRate;
            double normalizedBandwidth = bandwidth / sampleRate;
            
            double alpha = std::tan(MathUtils::PI * normalizedBandwidth / 2.0);
            double beta = std::cos(2.0 * MathUtils::PI * normalizedCenter);
            
            double a0 = 1.0 + alpha;
            bCoeffs = {1.0 / a0, -2.0 * beta / a0, 1.0 / a0};
            aCoeffs = {1.0, -2.0 * beta / a0, (1.0 - alpha) / a0};
            break;
        }
        
        case FilterType::NOTCH: {
            // Notch filter (band-stop at specific frequency)
            double normalizedFreq = cutoffFrequency / sampleRate;
            double alpha = std::tan(MathUtils::PI * normalizedFreq / Q);
            
            double a0 = 1.0 + alpha;
            bCoeffs = {1.0 / a0, -2.0 * std::cos(2.0 * MathUtils::PI * normalizedFreq) / a0, 1.0 / a0};
            aCoeffs = {1.0, -2.0 * std::cos(2.0 * MathUtils::PI * normalizedFreq) / a0, (1.0 - alpha) / a0};
            break;
        }
    }
    
    // Ensure we have at least one coefficient
    if (bCoeffs.empty()) {
        bCoeffs = {1.0};
    }
    if (aCoeffs.empty()) {
        aCoeffs = {1.0};
    }
}

void Filter::Impl::resetHistory() {
    xHistory.clear();
    yHistory.clear();
}

} // namespace signal
} // namespace song_processor 