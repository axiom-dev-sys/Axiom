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

Редактор Axiom предоставляет единое рабочее пространство
для создания и тестирования 2D-сцен.

Редактор включает настраиваемое Docking-пространство с инструментами
редактирования сцен, управления сущностями и ресурсами,
отладки и контроля Runtime.

Поддерживаются выбор и перемещение объектов, сетка и привязка,
создание и переключение сцен, сериализация сцен, файловые диалоги,
Runtime-взаимодействие и сохранение расположения панелей.

Редактор также отслеживает состояние текущей сцены и защищает
несохранённые изменения при открытии, создании и переключении сцен,
а также при выходе из редактора.

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
  - Docking Workspace
  - Persistent Editor Layout
  - Editor Context
  - Scene Document State
  - Scene Dirty State Tracking
  - New / Open / Save / Save As
  - Unsaved Changes Protection
  - Scene Switching
  - Entity Selection and Manipulation
  - Grid and Snapping Tools
  - File Dialog Integration

- Runtime
  - Runtime Session Lifecycle
  - Play / Pause / Stop
  - Main Menu
  - Difficulty Selection
  - Gameplay Prototype
  - Enemy AI
  - Camera System
  - Power Management
  - Gameplay HUD
  - Win / Game Over States
  - Runtime Scene Transitions

## Технологии

- C++17
- OpenGL
- GLFW
- GLAD
- GLM
- ImGui
- ImGuiFileDialog
- stb_image
- CMake

## Цель проекта

Главная цель Axiom Engine — не только создать игровой движок, но и глубоко понять принципы работы современных игровых движков.

Проект развивается сразу в трёх направлениях:

- Геймдизайн — создание интересных игровых механик.
- Архитектура — ECS, логика, расширяемость и структура движка.
- История и атмосфера — создание выразительных игровых миров.

Axiom развивается как фундамент для будущих оригинальных игр с собственной механикой и стилем.

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

Axiom Engine 1.6.x завершает этап интеграции редактора и движка
(Editor–Engine Integration).

Системы редактора и движка теперь объединены в более целостный
рабочий процесс для редактирования сцен, сериализации,
тестирования Runtime и работы с игровым проектом.

Редактор включает Docking-пространство, сохранение расположения панелей,
инструменты работы со сценами и сущностями, файловые диалоги,
отслеживание состояния текущей сцены и защиту от потери
несохранённых изменений.

Runtime предоставляет Play / Pause / Stop, главное меню,
игровые системы, искусственный интеллект врага, управление энергией,
Gameplay HUD, выбор сложности, перезапуск игры
и состояния Win / Game Over.

На данный момент Axiom предоставляет стабильный фундамент
для разработки и тестирования 2D-игр непосредственно
через встроенный редактор и Runtime.

Следующий этап разработки — Axiom Engine 1.7.x —
будет посвящён Project-Driven Development и дальнейшему развитию
движка вокруг потребностей реального игрового проекта.