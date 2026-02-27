cmake_minimum_required(VERSION 3.20)
project(Axiom)

set(CMAKE_CXX_STANDARD 17)

add_executable(Axiom
    src/main.cpp 
    Axiom.rc
)

# GLFW
add_subdirectory(external/glfw)
include_directories(external/glfw/include)

target_link_libraries(Axiom glfw ${GLFW_LIBRARIES})

# GLAD
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

target_link_libraries(Axiom glad)