cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(Climbex VERSION 0.1)

set(SOURCES
    src/main.cpp
    src/Window.cpp
    src/Shader.cpp
    src/Program.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
    src/ResourceManager.cpp
    src/events/Event.h
    src/events/Dispatch.h
    src/events/KeyEvents.h
)

set(GLAD_DIR vendor/glad)

add_executable(Climbex ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(Climbex PUBLIC glfw GLEW::GLEW OpenGL::GL)

target_include_directories(Climbex PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${GLAD_DIR}/include"
)

