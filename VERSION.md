# Axiom Engine — Version History

This file tracks the development progress of the Axiom Engine.

---

## v0.1 — Core Prototype

**Foundation stage of the engine.**

* GLFW window creation
* OpenGL context initialization
* Basic game loop
* Screen clearing (render loop baseline)
* Time / delta time system
* Basic logging system

**Goal:** Engine starts and runs a window successfully.

---

## v0.2 — Stabilization Update

**Date: 01.05.2026**

### Added

* 2D matrix camera system
* `RenderComponent` for scene object rendering
* Basic 2D coordinate system
* Initial component integration into Scene

### Changed

* Scene architecture partially redesigned
* Render pipeline simplified and stabilized
* Unified rendering call structure
* Component interaction structure simplified for core stability

### Removed / Temporarily Disabled

* Logging system temporarily removed for rewrite
* Unused and conflicting code parts removed
* Simplified subsystems for engine stabilization

### Fixed

* Linker error: `Scene::onRender`
* Incorrect non-static shader method calls
* Basic renderer initialization issues

### Known Limitations

* Camera supports only 2D
* No lighting system
* Component system is still in early formation

**Goal:** Stable engine core ready for Scene + Component expansion.

---

## v0.3 — Scene & Components (Planned)

* Entity system
* TransformComponent
* SpriteComponent
* Scene update/render loop
* Multiple entities rendering

---

## v0.4 — Rendering Pipeline (Planned)

* Batch rendering
* Render queue
* Texture management
* Shader system improvements
* Camera matrix integration refinement

---

## v0.5 — Resource System (Planned)

* ResourceManager upgrade
* Texture caching
* Shader loading system
* Asset organization

---

## v0.6 — Editor Foundations (Planned)

* Scene hierarchy
* Inspector
* Debug overlay
* Gizmos

---

## v0.7 — Gameplay Framework (Planned)

* Scripting system
* Prefabs
* Events system
* Scene serialization

---

## v1.0 — First Stable Release (Planned)

* Full scene system
* Complete rendering pipeline
* Resource system
* Basic editor
* Gameplay-ready framework

**Goal:** First production-ready version of Axiom Engine.
