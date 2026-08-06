# Atmospheric Scattering

<img width="1523" height="779" alt="Image" src="https://github.com/user-attachments/assets/f45c55cd-c87f-4d27-8f68-d57874dc1a1a" />

Real-time atmospheric scattering in OpenGL using a fullscreen ray-marched sky pass.

The renderer models the planet and atmosphere as concentric spheres and computes single scattering in the fragment shader. It currently supports Rayleigh scattering, Mie scattering, sun-ray transmittance, tone mapping, and an animated sun direction.

## Tech Stack

- C++17
- OpenGL 3.3 Core
- GLSL 330
- GLFW
- GLAD
- GLM
- CMake
- Visual Studio 2022 on Windows

## Current Features

- Fullscreen quad sky rendering
- World-space ray reconstruction from camera matrices
- Ray-sphere intersection for planet and atmosphere
- Rayleigh scattering for blue sky color
- Secondary light ray marching for atmospheric transmittance
- Mie scattering for haze and sun glow
- Exposure tone mapping and gamma correction
- Animated sun direction
- Placeholder ground below the horizon

## Project Layout

```text
src/
|-- core/
|   |-- Window.h / Window.cpp
|   `-- Shader.h / Shader.cpp
|-- graphic/
|   |-- Mesh.h / Mesh.cpp
|   `-- Renderer.h / Renderer.cpp
|-- scene/
|   |-- Camera.h / Camera.cpp
|   `-- Transform.h / Transform.cpp
|-- shaders/
|   |-- sky.vert
|   `-- sky.frag
`-- main.cpp
```

## Build

From the repository root:

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

Run:

```powershell
.\build\Debug\AtmosphericScattering.exe
```

## Controls

- `W` / `S`: move forward and backward
- `A` / `D`: move left and right
- `Esc`: close the window

The current camera has movement only. There is no mouse-look yet.

## Atmosphere Model

The simulation uses kilometers as world units:

```text
1 world unit = 1 kilometer
```

The planet is centered at the world origin.

Default scale:

```text
ground radius      = 6371 km
atmosphere radius  = 6471 km
camera start       = (0, 6372, 0)
```

If the camera starts near the origin, it is inside the planet and the atmosphere math will behave incorrectly.

## Important Shader Values

The main atmosphere parameters are uploaded from `Renderer.cpp`:

```cpp
sunIntensity
groundRadius
atmosphereRadius
betaR
Hr
viewSamples
lightSamples
betaM
Hm
mieG
exposure
```

Good starting values:

```text
sunIntensity = 20.0
groundRadius = 6371.0
atmosphereRadius = 6471.0
betaR = (5.8e-3, 1.35e-2, 3.31e-2)
Hr = 8.0
viewSamples = 16
lightSamples = 8
betaM = 21.0e-3
Hm = 1.2
mieG = 0.888
exposure = 0.5
```

## Rendering Notes

The sky is rendered as a fullscreen quad. The fragment shader reconstructs a world-space ray for every pixel:

```text
UV -> NDC -> view ray -> world ray
```

That ray is marched through the atmosphere. At each sample, another ray is marched toward the sun to compute how much sunlight reaches the sample point.

Final color is:

```text
Rayleigh contribution + Mie contribution
```

then exposure tone mapping and gamma correction.

## References

- Nishita et al. atmospheric scattering model
- Reference implementation: https://github.com/kentril0/OpenGL_Atmospheric_Scattering

