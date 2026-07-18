# Axiom Engine

[Русская версия](README_RU.md)

Axiom Engine is a lightweight 2D game engine written in C++17 using OpenGL.

The project is focused on 2D game development and learning the architecture of modern game engines.  
Its core systems include ECS, scene management, resource management, scene serialization, debugging tools, and an integrated editor.

## Editor

The second generation of the Axiom Editor.

The editor now includes a viewport-based workflow with integrated tools
for scene editing, entity inspection, asset management, debugging,
and runtime control.

It provides entity selection, dragging, grid snapping, scene management,
runtime interaction, and development tools for 2D game creation.

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
  - Grid System
  - Snap System

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
  - Status Bar
  - Preferences Panel
  - Viewport Panel

- Runtime
  - Runtime Session Lifecycle
  - Play / Pause / Stop
  - Main Menu
  - Gameplay HUD
  - Win / Game Over States
  - Runtime Scene Transitions

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

Axiom Engine 1.4.x completes the Game Framework stage.

The engine now combines the second generation editor with runtime
systems, gameplay state management, an integrated HUD, scene transitions,
and debugging tools.

Axiom currently provides a complete foundation for 2D game development,
including rendering, ECS, scene management, runtime architecture,
serialization, debugging tools, and an integrated editor.

The next stage of development will focus on creating the first playable
prototype using Axiom Engine.