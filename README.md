# Axiom Engine

[Русская версия](README_RU.md)

Axiom Engine is a lightweight 2D game engine written in C++17 using OpenGL.

The project is focused on 2D game development and learning the architecture of modern game engines.  
Its core systems include ECS, scene management, resource management, scene serialization, debugging tools, and an integrated editor.

## Editor

![Axiom Editor](docs/images/axiom-editor.png)

## Features

- Rendering
  - OpenGL Renderer
  - Camera System

- Core
  - ECS (Entity Component System)
  - Scene Manager
  - Resource Manager
  - Asset Registry
  - Scene Serialization
  - Collision System
  - Timer System
  - Input System
  - Runtime System

- Debug
  - Debug Overlay
  - Debug Renderer

- Editor
  - Editor UI
  - Inspector Panel
  - Hierarchy Panel
  - Scene Editor Panel
  - Asset Browser Panel
  - Console Panel
  - Statistics Panel

## Technologies

- C++17
- OpenGL
- GLFW
- GLAD
- GLM
- ImGui
- stb_image
- CMake

## Project Goal

The main goal of Axiom Engine is not only to create a game engine, but also to understand how a game engine works internally.

The project is built around three directions:

- Game design — creating meaningful gameplay experiences
- System architecture — ECS, logic, balance, and extensibility
- Story and atmosphere — building deep and expressive game worlds

Axiom is being developed as a foundation for future original games with unique mechanics and presentation.

## Build and Run

### CMake

Clone the repository:

```bash
git clone https://github.com/axiom-dev-sys/Axiom.git
cd Axiom
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Visual Studio

Open the project in Visual Studio 2022
Select the Debug or Release configuration
Build and run the project

## Current Status

Axiom Engine 1.1.х introduces the Runtime architecture, extending the first stable release with a dedicated runtime workflow for gameplay execution inside the editor.

The engine now provides a solid 2D foundation including rendering, ECS, runtime management, scene management, resource management, serialization, debugging tools, and an integrated editor.

Future versions will continue expanding the engine with new editor features, gameplay systems, rendering improvements, and additional tools.