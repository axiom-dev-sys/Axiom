cmake_minimum_required(VERSION 3.20)
project(Axiom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)

# GLFW
add_subdirectory(external/glfw)

# GLAD
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# ImGui
add_library(imgui
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    external/imgui
    external/imgui/backends
)

target_link_libraries(imgui PUBLIC glfw glad)

include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

FetchContent_MakeAvailable(glm)

add_executable(Axiom
    src/main.cpp
    src/Core/Application.cpp
    src/Core/Engine.cpp
    src/Core/Layer.cpp
    src/Core/LayerStack.cpp
    src/Core/Log.cpp
    src/Core/Time.cpp
    src/Game/GameLayer.cpp
    src/Platform/GLFW/Window.cpp
    src/Input/Input.cpp
    src/Camera/Camera.cpp
    src/Camera/Camera2D.cpp
    src/Renderer/API/OpenGL/Graphics/Texture.cpp
    src/Renderer/API/OpenGL/Graphics/Shader.cpp
    src/Renderer/Renderer.cpp
    src/Resource/ResourceManager.cpp
    src/Resource/AssetRegistry.cpp
    src/Renderer/API/OpenGL/OpenGLRenderer.cpp
    src/stb_image.cpp
    src/Scene/Scene.cpp
    src/Scene/SceneSerializer.cpp
    src/Scene/SceneManager.cpp
    src/Scene/Systems/RenderSystem.cpp
    src/Scene/Systems/MovementSystem.cpp
    src/Scene/Systems/CameraFollowSystem.cpp
    src/Scene/Systems/PlayerInputSystem.cpp
    src/Scene/Systems/CollisionSystem.cpp
    src/Scene/Systems/TimerSystem.cpp
    src/DebugTools/DebugOverlay.cpp
    src/DebugTools/DebugRenderer.cpp
    src/DebugTools/InspectorPanel.cpp
    src/DebugTools/HierarchyPanel.cpp
)

target_include_directories(Axiom PUBLIC
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(Axiom glfw glad glm::glm imgui)

add_custom_command(TARGET Axiom POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Axiom>/assets
)