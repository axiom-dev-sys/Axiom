cmake_minimum_required(VERSION 3.20)
project(Axiom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)

# GLFW
add_subdirectory(external/glfw)

# GLAD
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

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
    src/Renderer/API/OpenGL/OpenGLRenderer.cpp
    src/stb_image.cpp
    src/Scene/Scene.cpp
)

target_include_directories(Axiom PUBLIC
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(Axiom glfw glad)

add_custom_command(TARGET Axiom POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)