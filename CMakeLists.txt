cmake_minimum_required(VERSION 3.20)
project(Axiom)

set(CMAKE_CXX_STANDARD 17)

# GLFW
add_subdirectory(external/glfw)

# GLAD
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(Axiom
    src/main.cpp
    src/Core/Engine.cpp
    src/Core/Window.cpp
    src/Renderer/Renderer.cpp
)

target_include_directories(Axiom PUBLIC include)

target_link_libraries(Axiom glfw glad)