/*
  ==============================================================================

    ClippingFunctions.h
    Created: 9 Sep 2021 9:21:12am
    Author:  羽翼深蓝Wings

  ==============================================================================
*/

#pragma once
#include <math.h>
namespace waveshaping
{

using JMath = juce::dsp::FastMathApproximations;

template<typename T>
T arctanSoftClipping (T x) noexcept
{
    return atan(x) / 2.0f;
}

template<typename T>
T expSoftClipping (T x) noexcept
{
    if (x > 0)
    {
        x = 1.0f - expf(-x);
    }
    else
    {
        x = -1.0f + expf(x);
    }
    return x;
}

template<typename T>
T tanhSoftClipping (T x) noexcept
{
    return tanh(x);
}

template<typename T>
T cubicSoftClipping (T x) noexcept
{
    if (x > 1.0f)
    {
        x = 1.0f * 2.0f / 3.0f;
    }
    else if (x < -1.0f)
    {
        x = -1.0f * 2.0f / 3.0f;
    }
    else
    {
        x = x - (pow(x, 3.0f) / 3.0f);
    }
    return x * 3.0f / 2.0f;
}

template<typename T>
T hardClipping (T x) noexcept
{
    if (x > 1.0f)
    {
        x = 1.0f;
    }
    else if (x < -1.0f)
    {
        x = -1.0f;
    }
    return x;
}

template<typename T>
T sausageFattener (T x) noexcept
{
    x = x * 1.1f;
    if (x >= 1.1f)
    {
        x = 1.0f;
    }
    else if (x <= -1.1f)
    {
        x = -1.0f;
    }
    else if (x > 0.9f && x < 1.1f)
    {
        x = -2.5f * x * x + 5.5f * x - 2.025f;
    }
    else if (x < -0.9f && x > -1.1f)
    {
        x = 2.5f * x * x + 5.5f * x + 2.025f;
    }
    return x;
}

template<typename T>
T sinFoldback (T x) noexcept
{
    return std::sin(x);
}

template<typename T>
T linFoldback (T x) noexcept
{
    if (x > 1.0f || x < -1.0f)
    {
        x = fabs(fabs(fmod(x - 1.0f, 1.0f * 4)) - 1.0f * 2) - 1.0f;
    }
    return x;
}

template<typename T>
T limitClip (T x) noexcept
{
    return juce::jlimit (-0.1f, 0.1f, x);
}

template<typename T>
T singleSinClip (T x) noexcept
{
    if (std::fabs (x) < juce::MathConstants<T>::pi)
    {
        return JMath::sin (x);
    }
    else
    {
        return 0;//signbit (x) * 1.0f;
    }
}

template<typename T>
T logicClip (T x) noexcept
{
    return 2.0f / (1.0f + JMath::exp (-2.0f * x)) - 1.0f;
}

template<typename T>
T tanclip (T x) noexcept
{
    float soft = 0.0f;
    return juce::jlimit (-1.0f, 1.0f, static_cast<float>(JMath::tanh ((1.0f - 0.5f * soft) * x) - 0.02 * x));
}

// WET SATURATION TYPES

template<typename T>
T waterSaturation (T x) noexcept
{
    // Asymmetric sine waveshaping with dispersion
    T phase = x * 0.8f;
    T asymSine = std::sin(phase) + 0.2f * std::sin(2.0f * phase + 0.3f);
    
    // Add dispersion effect (frequency-dependent phase shift)
    T dispersion = 0.1f * std::sin(3.0f * phase) * std::tanh(x * 0.5f);
    
    return juce::jlimit(-1.0f, 1.0f, asymSine + dispersion);
}

template<typename T>
T pissSaturation (T x) noexcept
{
    // More aggressive asymmetric waveshaping with stronger dispersion
    T phase = x * 1.2f;
    T asymSine = std::sin(phase) + 0.3f * std::sin(2.0f * phase + 0.5f) + 0.15f * std::sin(3.0f * phase + 0.7f);
    
    // Stronger dispersion effect
    T dispersion = 0.2f * std::sin(4.0f * phase) * std::tanh(x * 0.7f);
    
    // Add slight compression to the high end
    T compressed = asymSine + dispersion;
    if (std::abs(compressed) > 0.7f)
        compressed = 0.7f + 0.3f * std::tanh((std::abs(compressed) - 0.7f) * 3.0f) * (compressed > 0 ? 1.0f : -1.0f);
    
    return juce::jlimit(-1.0f, 1.0f, compressed);
}

template<typename T>
T mudSaturation (T x) noexcept
{
    // Thick, dense saturation with low-mid emphasis
    T phase = x * 0.7f;
    
    // Base saturation with emphasis on low-mids
    T baseSat = std::tanh(phase * 1.2f);
    
    // Add low-mid resonance
    T lowMidRes = 0.25f * std::sin(phase * 0.6f) * std::tanh(phase * 0.4f);
    
    // Add subtle harmonic complexity
    T harmonics = 0.15f * std::sin(2.0f * phase) * (1.0f - std::abs(phase));
    
    // Combine with slight compression
    T result = baseSat + lowMidRes + harmonics;
    if (std::abs(result) > 0.8f)
        result = 0.8f + 0.2f * std::tanh((std::abs(result) - 0.8f) * 2.0f) * (result > 0 ? 1.0f : -1.0f);
    
    return juce::jlimit(-1.0f, 1.0f, result);
}

template<typename T>
T iceSaturation (T x) noexcept
{
    // Crystalline, bright saturation with high-frequency emphasis
    T phase = x * 1.1f;
    
    // Base saturation with less low end
    T baseSat = std::tanh(phase) - 0.1f * std::tanh(phase * 0.5f);
    
    // Add high-frequency shimmer
    T highFreqShimmer = 0.2f * std::sin(3.0f * phase) * std::tanh(phase * 1.5f);
    
    // Add subtle harmonic ringing
    T harmonicRing = 0.15f * std::sin(4.0f * phase + 0.2f) * (0.8f + 0.2f * std::sin(8.0f * phase));
    
    // Combine with slight limiting
    T result = baseSat + highFreqShimmer + harmonicRing;
    
    return juce::jlimit(-0.95f, 0.95f, result);
}

template<typename T>
T acidSaturation (T x) noexcept
{
    // Aggressive, corrosive saturation with resonant peaks
    T phase = x * 1.4f;
    
    // Base distortion
    T baseDist = std::tanh(phase * 1.5f);
    
    // Add resonant peaks
    T resonance = 0.3f * std::sin(2.5f * phase) * std::tanh(phase * 0.8f);
    
    // Add harmonic dissonance
    T dissonance = 0.2f * std::sin(3.7f * phase + 0.4f) * std::sin(1.5f * phase);
    
    // Add frequency-dependent bite
    T bite = 0.15f * std::sin(5.0f * phase) * (1.0f - std::exp(-std::abs(phase)));
    
    // Combine with aggressive limiting
    T result = baseDist + resonance + dissonance + bite;
    if (std::abs(result) > 0.7f)
        result = 0.7f + 0.3f * std::tanh((std::abs(result) - 0.7f) * 4.0f) * (result > 0 ? 1.0f : -1.0f);
    
    return juce::jlimit(-1.0f, 1.0f, result);
}

template<typename T>
T steamSaturation (T x) noexcept
{
    // Airy, diffuse saturation with movement
    T phase = x * 0.9f;
    
    // Base soft saturation
    T baseSat = std::tanh(phase);
    
    // Add airy movement
    static float modPhase = 0.0f;
    modPhase += 0.0007f;
    if (modPhase > 6.28f) modPhase -= 6.28f;
    
    T movement = 0.15f * std::sin(modPhase) * std::sin(2.0f * phase);
    
    // Add diffusion
    T diffusion = 0.2f * std::sin(phase * 1.5f + 0.3f) * (0.7f + 0.3f * std::sin(3.0f * phase));
    
    // Add subtle noise texture
    T noise = 0.05f * (2.0f * static_cast<T>(std::rand()) / RAND_MAX - 1.0f) * std::abs(phase);
    
    return juce::jlimit(-0.95f, 0.95f, baseSat + movement + diffusion + noise);
}

// TAPE EMULATION TYPES

template<typename T>
T coldTape (T x) noexcept
{
    // Subtle tape saturation with slight high-end roll-off
    T drive = 0.6f * x;
    T saturation = std::tanh(drive);
    
    // Subtle high-frequency attenuation
    T highEndRolloff = 0.05f * std::sin(drive * 3.0f);
    
    return juce::jlimit(-0.95f, 0.95f, saturation - highEndRolloff);
}

template<typename T>
T cleanTape (T x) noexcept
{
    // Clean tape with minimal saturation but some compression
    T drive = 0.8f * x;
    
    // Soft knee compression
    T compressed = drive;
    if (std::abs(drive) > 0.7f)
        compressed = 0.7f + 0.3f * std::tanh((std::abs(drive) - 0.7f) * 2.0f) * (drive > 0 ? 1.0f : -1.0f);
    
    // Very subtle saturation
    T saturation = std::tanh(compressed * 1.1f);
    
    return juce::jlimit(-0.98f, 0.98f, saturation);
}

template<typename T>
T warmTape (T x) noexcept
{
    // Warm tape with moderate saturation and low-mid boost
    T drive = 1.2f * x;
    
    // Asymmetric saturation for warmth
    T warmth = 0.1f * std::sin(drive * 2.0f + 0.3f);
    
    // Soft saturation with low-mid emphasis
    T saturation = std::tanh(drive + warmth);
    
    // Add subtle harmonic enhancement
    T harmonics = 0.08f * std::sin(2.0f * drive) * std::tanh(drive * 0.5f);
    
    return juce::jlimit(-1.0f, 1.0f, saturation + harmonics);
}

template<typename T>
T hotTape (T x) noexcept
{
    // Hot tape with strong saturation and compression
    T drive = 1.8f * x;
    
    // Strong asymmetric saturation
    T asymSat = std::tanh(drive) + 0.2f * std::tanh(2.0f * drive);
    
    // Add harmonics and slight distortion
    T harmonics = 0.15f * std::sin(3.0f * drive) * std::tanh(drive * 0.7f);
    
    // Compression
    T result = asymSat + harmonics;
    if (std::abs(result) > 0.6f)
        result = 0.6f + 0.4f * std::tanh((std::abs(result) - 0.6f) * 2.5f) * (result > 0 ? 1.0f : -1.0f);
    
    return juce::jlimit(-1.0f, 1.0f, result);
}

template<typename T>
T cassetteTape (T x) noexcept
{
    // Cassette tape with noise, wow/flutter simulation, and frequency limitations
    T drive = 1.5f * x;
    
    // Basic saturation
    T saturation = std::tanh(drive);
    
    // Add noise (subtle)
    T noise = 0.03f * (2.0f * static_cast<T>(std::rand()) / RAND_MAX - 1.0f);
    
    // Simulate wow/flutter with subtle phase modulation
    static float phase = 0.0f;
    phase += 0.001f;
    if (phase > 6.28f) phase -= 6.28f;
    
    T wowFlutter = 0.04f * std::sin(phase) * saturation;
    
    // Frequency limitations (high and low end roll-off)
    T freqLimited = saturation - 0.1f * std::sin(drive * 4.0f) - 0.05f * std::sin(drive * 0.5f);
    
    return juce::jlimit(-0.95f, 0.95f, freqLimited + wowFlutter + noise);
}

template<typename T>
T vintageTape (T x) noexcept
{
    // Vintage tape with harmonic richness and subtle compression
    T drive = 1.3f * x;
    
    // Rich harmonic saturation
    T saturation = std::tanh(drive) + 0.1f * std::tanh(2.0f * drive) * (1.0f - std::abs(drive) * 0.3f);
    
    // Add subtle warmth
    T warmth = 0.15f * std::sin(drive * 0.7f) * std::tanh(drive * 0.4f);
    
    // Add subtle wow/flutter
    static float vPhase = 0.0f;
    vPhase += 0.0005f;
    if (vPhase > 6.28f) vPhase -= 6.28f;
    
    T wowFlutter = 0.02f * std::sin(vPhase) * saturation;
    
    // Add subtle noise
    T noise = 0.01f * (2.0f * static_cast<T>(std::rand()) / RAND_MAX - 1.0f);
    
    // Gentle frequency roll-off
    T freqRolloff = saturation - 0.07f * std::sin(drive * 3.0f);
    
    // Soft compression
    T result = freqRolloff + warmth + wowFlutter + noise;
    if (std::abs(result) > 0.8f)
        result = 0.8f + 0.2f * std::tanh((std::abs(result) - 0.8f) * 2.0f) * (result > 0 ? 1.0f : -1.0f);
    
    return juce::jlimit(-0.98f, 0.98f, result);
}

template<typename T>
T lofiTape (T x) noexcept
{
    // Lo-fi tape with heavy degradation and artifacts
    T drive = 1.6f * x;
    
    // Basic saturation
    T saturation = std::tanh(drive);
    
    // Add significant noise
    T noise = 0.08f * (2.0f * static_cast<T>(std::rand()) / RAND_MAX - 1.0f);
    
    // Simulate heavy wow/flutter
    static float lfPhase1 = 0.0f;
    static float lfPhase2 = 0.0f;
    lfPhase1 += 0.002f;
    lfPhase2 += 0.0013f;
    if (lfPhase1 > 6.28f) lfPhase1 -= 6.28f;
    if (lfPhase2 > 6.28f) lfPhase2 -= 6.28f;
    
    T wowFlutter = 0.1f * std::sin(lfPhase1) * saturation + 0.05f * std::sin(lfPhase2) * saturation;
    
    // Heavy frequency limitations
    T freqLimited = saturation - 0.2f * std::sin(drive * 4.0f) - 0.15f * std::sin(drive * 0.4f);
    
    // Add distortion artifacts
    T artifacts = 0.1f * std::sin(5.0f * drive) * (1.0f - std::abs(drive) * 0.5f);
    
    // Add dropouts
    static float dropPhase = 0.0f;
    dropPhase += 0.0003f;
    if (dropPhase > 6.28f) dropPhase -= 6.28f;
    
    T dropouts = (0.95f + 0.05f * std::sin(dropPhase * 5.0f));
    
    return juce::jlimit(-0.9f, 0.9f, (freqLimited + wowFlutter + noise + artifacts) * dropouts);
}

template<typename T>
T studioTape (T x) noexcept
{
    // Professional studio tape with subtle enhancement and compression
    T drive = 1.1f * x;
    
    // Clean, transparent saturation
    T saturation = std::tanh(drive * 0.9f);
    
    // Add subtle harmonic enhancement
    T harmonics = 0.05f * std::sin(2.0f * drive) * (1.0f - std::abs(drive) * 0.5f);
    
    // Add very subtle wow/flutter (well-maintained machine)
    static float stPhase = 0.0f;
    stPhase += 0.0002f;
    if (stPhase > 6.28f) stPhase -= 6.28f;
    
    T wowFlutter = 0.01f * std::sin(stPhase) * saturation;
    
    // Very minimal noise
    T noise = 0.005f * (2.0f * static_cast<T>(std::rand()) / RAND_MAX - 1.0f);
    
    // Gentle high-end roll-off
    T freqRolloff = saturation - 0.03f * std::sin(drive * 3.5f);
    
    // Professional compression
    T result = freqRolloff + harmonics + wowFlutter + noise;
    if (std::abs(result) > 0.75f)
        result = 0.75f + 0.25f * std::tanh((std::abs(result) - 0.75f) * 1.5f) * (result > 0 ? 1.0f : -1.0f);
    
    return juce::jlimit(-0.99f, 0.99f, result);
}

template<typename T>
T magneticSaturation (T x) noexcept
{
    // Magnetic saturation with hysteresis simulation
    T drive = 1.4f * x;
    
    // Static variable to simulate magnetic memory/hysteresis
    static T lastOutput = 0.0f;
    
    // Basic saturation
    T saturation = std::tanh(drive);
    
    // Simulate magnetic hysteresis (memory effect)
    T hysteresis = 0.2f * lastOutput;
    
    // Combine with current input
    T combined = 0.8f * saturation + hysteresis;
    
    // Add subtle harmonic enhancement
    T harmonics = 0.1f * std::sin(2.0f * drive) * (1.0f - std::abs(drive) * 0.4f);
    
    // Final result
    T result = combined + harmonics;
    
    // Store for next sample
    lastOutput = result * 0.7f; // Decay factor
    
    return juce::jlimit(-0.97f, 0.97f, result);
}

// CREATIVE DISTORTION TYPES

template<typename T>
T quantizationDistortion (T x) noexcept
{
    // Bit-crushing style distortion with adjustable resolution
    T drive = x * 1.2f;
    
    // Basic saturation first
    T saturation = std::tanh(drive);
    
    // Quantize to simulate bit reduction
    const float levels = 12.0f; // Adjust for different bit-depths
    T quantized = std::round(saturation * levels) / levels;
    
    // Blend with original
    T result = 0.8f * quantized + 0.2f * saturation;
    
    return juce::jlimit(-1.0f, 1.0f, result);
}

template<typename T>
T resonantDistortion (T x) noexcept
{
    // Distortion with resonant peaks
    T drive = x * 1.3f;
    
    // Basic saturation
    T saturation = std::tanh(drive);
    
    // Add resonant peaks at specific frequencies
    T resonance1 = 0.3f * std::sin(2.7f * drive) * std::tanh(drive * 0.6f);
    T resonance2 = 0.2f * std::sin(4.2f * drive) * std::tanh(drive * 0.4f);
    
    // Combine
    T result = saturation + resonance1 + resonance2;
    
    return juce::jlimit(-1.0f, 1.0f, result);
}

template<typename T>
T dynamicDistortion (T x) noexcept
{
    // Distortion that changes character based on input level
    T drive = x * 1.4f;
    
    // Calculate input level
    T inputLevel = std::abs(drive);
    
    // Different distortion types based on level
    T lowLevelDist = std::tanh(drive * 0.8f); // Subtle for low levels
    T highLevelDist = std::sin(drive) + 0.1f * std::sin(3.0f * drive); // More aggressive for high levels
    
    // Crossfade between types based on input level
    T blend = juce::jlimit(0.0f, 1.0f, inputLevel * 1.5f);
    T result = (1.0f - blend) * lowLevelDist + blend * highLevelDist;
    
    return juce::jlimit(-1.0f, 1.0f, result);
}

template<typename T>
T asymWaveFolder (T x) noexcept
{
    // Asymmetric wavefolder with rich harmonics
    T drive = x * 1.5f;
    
    // Basic wavefolder
    T folded = std::sin(drive * juce::MathConstants<T>::pi);
    
    // Add asymmetry
    T asymmetry = 0.2f * std::sin(2.0f * drive + 0.5f);
    
    // Add harmonics
    T harmonics = 0.15f * std::sin(3.0f * drive) * (1.0f - std::abs(drive) * 0.3f);
    
    // Combine
    T result = folded + asymmetry + harmonics;
    
    return juce::jlimit(-1.0f, 1.0f, result);
}

template<typename T>
T pulseDistortion (T x) noexcept
{
    // Distortion that creates pulse-like waveforms
    T drive = x * 1.2f;
    
    // Create pulse-like shape
    T pulse = std::tanh(drive * 5.0f);
    
    // Soften edges
    T softened = pulse * (0.7f + 0.3f * std::tanh(drive * 0.5f));
    
    // Add harmonics
    T harmonics = 0.1f * std::sin(2.0f * drive) + 0.05f * std::sin(3.0f * drive);
    
    // Combine
    T result = softened + harmonics;
    
    return juce::jlimit(-1.0f, 1.0f, result);
}

//template<typename T>
//T algClip (T x) noexcept
//{
//    float soft = 0.0f;
//    return x / std::sqrtf ((1.0f + 2.0f * soft + std::powf (x, 2.0f)));
//}

//template<typename T>
//T arcClip (T x) noexcept
//{
//    float soft = 0.0f;
//    return (2.0f / juce::MathConstants<T>::pi) * std::atanf ((1.6f - soft * 0.6f) * x);
//}

template<typename T>
T rectificationProcess (T x, T rectification) noexcept
{
    if (x < 0)
    {
        x *= (0.5f - rectification) * 2.0f;
    }
    return x;
}

}
