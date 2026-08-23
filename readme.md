# Custom OpenGL Engine

A OpenGL 3D rendering framework built from scratch in C++17, focused on learning modern graphics programming and clean engine architecture.

## Features

- **RAII wrappers** for core OpenGL objects: `VAO`, `VBO<T>` (templated), `EBO`, `SSBO`, with proper move semantics and no copying.
- **Mesh system** — `Mesh` + `MeshFactory` for generating primitives (triangle, quad, colored/textured cube, textured torus) with a flexible `AttributeLayout` for vertex attributes.
- **Free-fly camera** — mouse look (yaw/pitch) and WASD movement with acceleration and damping.
- **Resource management** — `ResourceManager` for shaders and textures, loaded via `ShaderLoader` / `TextureLoader` (using `stb_image`).
- **Input handling** — `Keyboard` state tracking and a `Cursor` for mouse delta calculation.
- **Event system** — lightweight `EventManager` with `KeyPressEvent` / `MouseEvent`, decoupling GLFW callbacks from game logic.
- **Frame limiting** — `FrameLimiter` for fixed/target frame rate and delta-time calculation.
- **Cross-platform window/context setup** — `Screen` wraps GLFW window creation, with special handling for macOS (forward-compatible core profile).

## Dependencies

- [GLFW](https://www.glfw.org/) — windowing and input
- [GLAD](https://glad.dav1d.de/) — OpenGL function loading
- [GLM](https://github.com/g-truc/glm) — math library
- [stb_image](https://github.com/nothings/stb) — texture loading

All dependencies are expected under `external/` (as CMake subdirectories for GLFW/GLAD/GLM) and are pulled in automatically by the build.

## Building

Requirements: CMake 3.10+, a C++17 compiler.

```bash
git clone --recurse-submodules <repo-url>
cd z
mkdir build && cd build
cmake ..
cmake --build .
```

The `res/` folder is copied next to the built executable automatically as a post-build step, so shaders and textures are found at runtime.

## Running

```bash
./z
```

Controls:
- `W` / `A` / `S` / `D` — move the camera
- Mouse — look around
- Cursor is locked and hidden by default

On start, the app opens a window, loads a basic textured shader and an oil-texture, generates a torus mesh, and spins it while you can fly the camera around the scene.

## Project structure

```
src/
├── core/           # Application, Screen, FrameLimiter
├── graphics/       # VAO/VBO/EBO/SSBO, Camera, Mesh, MeshFactory, Attribute
├── input/          # Keyboard, Cursor, Event system
├── resources/       # ResourceManager, Shader/Texture loaders and resources
└── scene/          # (WIP) Scene abstraction
res/                # Shaders, textures, other runtime assets
external/           # GLFW, GLAD, GLM
```

## Status

This is a work-in-progress learning project. Known rough edges:

- `Scene` is currently a stub — everything is set up directly in `Application::run()`.
- No proper error handling for failed shader/texture loads (returns `nullptr`, not yet checked everywhere).
- Some resource paths are relative and assume the working directory matches the executable location.

## License

Personal / educational project — no license specified yet.