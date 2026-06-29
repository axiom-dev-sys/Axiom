# Axiom Engine

[English version](README.md)

Axiom Engine — собственный игровой движок на C++17 с использованием OpenGL.

Проект ориентирован на разработку 2D-игр и изучение архитектуры современных игровых движков.

Основой движка являются:
- ECS (Entity Component System)
- система сцен
- менеджер ресурсов
- сериализация сцен
- инструменты отладки
- встроенный редактор

## Редактор

![Axiom Editor](docs/images/axiom-editor.png)

## Возможности

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

## Технологии

- C++17
- OpenGL
- GLFW
- GLAD
- GLM
- ImGui
- stb_image
- CMake

## Цель проекта

The main goal of Axiom Engine is not only to create a game engine, but also to understand how a game engine works internally.

The project is built around three directions:

- Game design — creating meaningful gameplay experiences
- System architecture — ECS, logic, balance, and extensibility
- Story and atmosphere — building deep and expressive game worlds

Axiom is being developed as a foundation for future original games with unique mechanics and presentation.

## Сборка и запуск

### CMake

Клонируйте репозиторий:

```bash
git clone https://github.com/axiom-dev-sys/Axiom.git
cd Axiom
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Visual Studio

- Откройте проект в Visual Studio 2022.
- Выберите конфигурацию **Debug** или **Release**.
- Соберите и запустите проект.

## Текущее состояние

Axiom Engine 1.1.х представляет архитектуру Runtime, отделяющую режим редактирования от режима выполнения игры.

Теперь движок предоставляет надёжную основу для разработки 2D-игр, включая рендеринг, ECS, управление Runtime, систему сцен, управление ресурсами, сериализацию, инструменты отладки и встроенный редактор.

Будущие версии продолжат развивать движок, добавляя новые возможности редактора, игровые системы, улучшения рендеринга и дополнительные инструменты.