# New Distortion Types for Fire

This document describes the new distortion types added to the Fire plugin.

## Wet Saturation Types

### 1. Water Saturation (Mode 12)
A unique saturation algorithm that uses asymmetric sine waveshaping with dispersion effects. This creates a "wet" sound with subtle phase shifts that vary with frequency content. The algorithm combines:
- Asymmetric sine waveshaping for a natural, flowing sound
- Frequency-dependent phase dispersion for added movement
- Gentle limiting to maintain control

### 2. Piss Saturation (Mode 13)
A more aggressive version of the Water Saturation algorithm with stronger dispersion effects and more pronounced harmonic content. Features:
- More aggressive asymmetric waveshaping with multiple harmonics
- Stronger dispersion effect for a more "liquid" sound
- Soft compression on the high end to prevent harshness
- Increased harmonic complexity for a richer sound

## Tape Emulation Types

### 1. Cold Tape (Mode 14)
A subtle tape saturation with minimal coloration and slight high-end roll-off. Characteristics:
- Subtle saturation with minimal distortion
- Gentle high-frequency attenuation
- Clean transient response
- Minimal compression

### 2. Clean Tape (Mode 15)
A clean tape emulation with minimal saturation but some compression. Provides:
- Very subtle saturation
- Soft knee compression for smooth dynamics
- Minimal coloration
- Maintains clarity while adding subtle analog character

### 3. Warm Tape (Mode 16)
A warm tape emulation with moderate saturation and low-mid boost. Features:
- Asymmetric saturation for warmth
- Low-mid emphasis
- Subtle harmonic enhancement
- Balanced compression

### 4. Hot Tape (Mode 17)
A hot tape emulation with strong saturation and compression. Provides:
- Strong asymmetric saturation
- Added harmonics and slight distortion
- Noticeable compression
- Rich harmonic content

### 5. Cassette Tape (Mode 18)
A cassette tape emulation with noise, wow/flutter simulation, and frequency limitations. Features:
- Basic saturation with noise
- Wow/flutter simulation through phase modulation
- Frequency limitations (high and low end roll-off)
- Authentic cassette character

## Usage Tips

- **Wet Saturation Types**: These work well on individual instruments or buses where you want to add unique character. Try them on synths, vocals, or drum buses.
- **Tape Emulation Types**: These are great for adding analog warmth to your mix. Use Cold or Clean Tape for subtle warming, Warm Tape for more character, and Hot Tape or Cassette for more obvious tape effects.
- **Drive Control**: The different tape types respond differently to the Drive parameter - experiment to find the sweet spot for each type.
- **Bias Control**: The Bias parameter can dramatically change the character of the tape emulations by adding asymmetry to the saturation.
- **Rectification**: The Rec parameter works well with the tape emulations to create interesting harmonic effects.

## Technical Implementation

These new distortion types are implemented as waveshaping functions in the `ClippingFunctions.h` file. They use various combinations of:
- Trigonometric functions (sin, tanh)
- Compression algorithms
- Phase modulation
- Harmonic generation
- Frequency-dependent processing

Each algorithm is carefully tuned to provide a unique sonic character while maintaining the overall sound quality of the Fire plugin.