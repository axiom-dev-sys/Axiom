# Axiom Engine — Version History

This file tracks the development progress of the Axiom Engine.

---

## v0.1 — Core Prototype

### Added

- GLFW window
- OpenGL initialization
- Basic render loop
- Delta Time system
- Logging system
- Engine/Application foundation

### Goal

The engine can create a window, initialize OpenGL and execute the main loop.

---

## v0.2 — Engine Stabilization

### Added

- 2D Camera
- Initial rendering components
- Basic scene architecture
- Component integration

### Changed

- Scene architecture redesigned
- Rendering pipeline stabilized
- Core engine structure simplified

### Removed

- Temporary logging rewrite
- Unused experimental code

### Fixed

- Scene rendering issues
- Shader initialization
- Linker errors

### Goal

Prepare a stable engine core for further ECS and gameplay development.

---

## v0.3 — ECS & Scene System

### Added

- Entity System
- Component System
- TransformComponent
- SpriteComponent
- VelocityComponent
- Scene update/render loop
- Camera follow system

---

## v0.4 — Gameplay Foundation

### Added

- Collision System
- Game States
- Pause System
- Scene Switching
- Camera improvements

---

## v0.5 — Resource & Serialization

### Added

- Scene Manager
- Resource Manager
- Asset Registry
- Scene Serialization (Save)
- Trigger / Collision Events

---

## v0.6 — Events & Cleanup

### Added

- Event System
- Timer System
- Collision Events
- Trigger Events
- Architecture cleanup

---

## v0.7 — Gameplay Framework

### Added

- Enemy System
- Power System
- Game Context
- Gameplay systems foundation

---

## v0.8 — Asset Pipeline

### Added

- Asset organization
- Paths system
- Executable asset loading
- Serializer improvements

---

## v0.9 — Editor & Debug Tools

### Added

- Debug Overlay
- Debug Renderer
- Hierarchy
- Inspector
- Scene Editor
- Asset Browser
- Console
- Statistics Panel
- Editor UI

---

## v1.0 — First Stable Release

**Date:** 2026-06-26

### Includes

- OpenGL Renderer
- ECS Architecture
- Scene System
- Resource Manager
- Asset Registry
- Scene Serialization
- Editor UI
- Editor Panels
- Debug Tools
- Collision System
- Input System
- Camera System
- Timer System
- Gameplay Framework

### Goal

First stable public release of the Axiom Engine.

Provides a complete foundation for 2D game development, including rendering,
ECS, scene management, resource management, serialization,
debugging tools, and an integrated editor.

## v1.1 — Runtime Architecture

### Added

- Runtime Session
- Runtime World
- Runtime State
- Runtime scene lifecycle
- Runtime scene transitions

### Changed

- Runtime controls refactored
- GameLayer architecture improved
- Scene switching unified
- Runtime workflow stabilized

### Fixed

- Runtime state transitions
- Play / Pause / Stop behavior
- Runtime scene restoration
- Runtime switching stability

---

## v1.2 — Editor Generation I

### Added

- FreeType integration
- Hierarchy improvements
- Inspector improvements
- Scene Editor improvements
- Asset Browser improvements
- Console Panel
- Statistics Panel
- Status Bar
- Preferences Panel

### Changed

- Editor interface redesigned
- Scene management workflow improved
- Runtime information unified
- Editor panels polished

### Fixed

- Status synchronization between editor panels
- Scene Editor runtime state
- Statistics runtime information
- Status Bar improvements
- Various editor bugs and UI issues

### Goal

Complete the first generation of the Axiom Editor.

Provide a stable, integrated editor for scene management, debugging,
resource browsing and runtime control before moving to the next stage
of engine development.