# Extended Distortion Types for Fire

This document describes all the new distortion types added to the Fire plugin.

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

### 3. Mud Saturation (Mode 14)
A thick, dense saturation with emphasis on low-mid frequencies. Characteristics:
- Heavy low-mid resonance for a thick, muddy sound
- Subtle harmonic complexity that varies with input level
- Slight compression to control peaks
- Works well for adding weight to thin sounds

### 4. Ice Saturation (Mode 15)
A crystalline, bright saturation with high-frequency emphasis. Features:
- Reduced low end for clarity
- High-frequency shimmer and harmonic ringing
- Creates a cold, bright tone
- Excellent for adding presence and air

### 5. Acid Saturation (Mode 16)
An aggressive, corrosive saturation with resonant peaks. Provides:
- Strong resonant peaks for a biting, acidic sound
- Harmonic dissonance for added aggression
- Frequency-dependent bite that increases with level
- Aggressive limiting for a controlled but intense sound

### 6. Steam Saturation (Mode 17)
An airy, diffuse saturation with subtle movement. Features:
- Soft saturation base with airy movement
- Diffusion that creates a sense of space
- Subtle noise texture that varies with input level
- Creates a sense of motion and space

## Tape Emulation Types

### 1. Cold Tape (Mode 18)
A subtle tape saturation with minimal coloration and slight high-end roll-off. Characteristics:
- Subtle saturation with minimal distortion
- Gentle high-frequency attenuation
- Clean transient response
- Minimal compression

### 2. Clean Tape (Mode 19)
A clean tape emulation with minimal saturation but some compression. Provides:
- Very subtle saturation
- Soft knee compression for smooth dynamics
- Minimal coloration
- Maintains clarity while adding subtle analog character

### 3. Warm Tape (Mode 20)
A warm tape emulation with moderate saturation and low-mid boost. Features:
- Asymmetric saturation for warmth
- Low-mid emphasis
- Subtle harmonic enhancement
- Balanced compression

### 4. Hot Tape (Mode 21)
A hot tape emulation with strong saturation and compression. Provides:
- Strong asymmetric saturation
- Added harmonics and slight distortion
- Noticeable compression
- Rich harmonic content

### 5. Cassette Tape (Mode 22)
A cassette tape emulation with noise, wow/flutter simulation, and frequency limitations. Features:
- Basic saturation with noise
- Wow/flutter simulation through phase modulation
- Frequency limitations (high and low end roll-off)
- Authentic cassette character

### 6. Vintage Tape (Mode 23)
A vintage tape emulation with rich harmonic content and subtle compression. Features:
- Rich harmonic saturation for a vintage sound
- Subtle warmth in the low-mids
- Very gentle wow/flutter for authentic movement
- Subtle noise and frequency roll-off
- Soft compression for a smooth sound

### 7. Lo-Fi Tape (Mode 24)
A lo-fi tape emulation with heavy degradation and artifacts. Provides:
- Significant noise and distortion
- Heavy wow/flutter for unstable pitch
- Severe frequency limitations
- Distortion artifacts and occasional dropouts
- Perfect for lo-fi beats and experimental sounds

### 8. Studio Tape (Mode 25)
A professional studio tape emulation with subtle enhancement and compression. Features:
- Clean, transparent saturation
- Very subtle harmonic enhancement
- Minimal wow/flutter (well-maintained machine)
- Very low noise floor
- Professional compression for a polished sound

### 9. Magnetic Saturation (Mode 26)
A magnetic saturation emulation with hysteresis simulation. Characteristics:
- Simulates magnetic memory/hysteresis effects
- Subtle harmonic enhancement
- Dynamic response that changes with input history
- Creates a natural, organic saturation

## Creative Distortion Types

### 1. Quantization Distortion (Mode 27)
A bit-crushing style distortion with adjustable resolution. Features:
- Simulates digital bit reduction
- Creates stepped distortion artifacts
- Blends with original signal for control
- Great for digital artifacts and lo-fi effects

### 2. Resonant Distortion (Mode 28)
A distortion with resonant peaks at specific frequencies. Provides:
- Basic saturation with resonant peaks
- Creates a vocal or formant-like quality
- Adds character and emphasis to specific frequency ranges
- Works well for creating distinctive tonal colors

### 3. Dynamic Distortion (Mode 29)
A distortion that changes character based on input level. Features:
- Subtle distortion at low levels
- More aggressive distortion at high levels
- Creates a dynamic, responsive sound
- Maintains clarity for quiet passages while adding character to louder parts

### 4. Asymmetric Wave Folder (Mode 30)
An asymmetric wavefolder with rich harmonics. Characteristics:
- Basic wavefolder for complex harmonic generation
- Added asymmetry for a more natural sound
- Rich harmonic content that varies with input level
- Creates complex, evolving timbres

### 5. Pulse Distortion (Mode 31)
A distortion that creates pulse-like waveforms. Features:
- Creates pulse-like shapes from any input
- Softened edges to prevent harshness
- Added harmonics for richness
- Great for creating synth-like tones from any source

## Usage Tips

### Wet Saturation Types
- **Water & Piss Saturation**: Great for adding unique character to synths, vocals, or drum buses.
- **Mud Saturation**: Perfect for adding weight to thin sounds or creating thick bass tones.
- **Ice Saturation**: Excellent for adding presence and air to vocals, acoustic guitars, or high-frequency content.
- **Acid Saturation**: Use on drums, synths, or any sound that needs aggressive character.
- **Steam Saturation**: Great for ambient sounds, pads, or creating a sense of space and movement.

### Tape Emulation Types
- **Cold & Clean Tape**: Use for subtle warming and analog character without obvious distortion.
- **Warm & Vintage Tape**: Perfect for adding classic analog warmth to any source.
- **Hot Tape**: Great for more obvious tape saturation and compression.
- **Cassette & Lo-Fi Tape**: Use for lo-fi beats, experimental sounds, or creative effects.
- **Studio Tape & Magnetic Saturation**: Excellent for adding professional polish and subtle enhancement.

### Creative Distortion Types
- **Quantization Distortion**: Great for digital artifacts, glitch effects, or lo-fi sounds.
- **Resonant Distortion**: Use to add vocal-like qualities or emphasize specific frequencies.
- **Dynamic Distortion**: Perfect for maintaining clarity while adding character.
- **Asymmetric Wave Folder**: Excellent for creating complex, evolving timbres.
- **Pulse Distortion**: Use to create synth-like tones from any source.

## Parameter Interactions

- **Drive**: Different distortion types respond differently to the Drive parameter. Experiment to find the sweet spot for each type.
- **Bias**: The Bias parameter can dramatically change the character of many distortion types by adding asymmetry.
- **Rectification**: The Rec parameter works well with most distortion types to create interesting harmonic effects.
- **Mix**: For subtle effects, use a lower Mix value to blend the distorted signal with the original.
- **Multiband Processing**: Try different distortion types on different frequency bands for complex, layered distortion effects.

## Technical Implementation

These distortion types are implemented as waveshaping functions in the `ClippingFunctions.h` file. They use various combinations of:
- Trigonometric functions (sin, tanh)
- Compression algorithms
- Phase modulation
- Harmonic generation
- Frequency-dependent processing
- Dynamic response based on input level
- Noise and artifact generation

Each algorithm is carefully tuned to provide a unique sonic character while maintaining the overall sound quality of the Fire plugin.