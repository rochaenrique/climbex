cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# TODO: Make this mutable
add_definitions(-DCBX_DEBUG)

project(Climbex VERSION 0.1)

set(SOURCES
    src/Window.cpp
    src/Log.cpp
    src/ResourceManager.cpp
    src/renderer/Shader.cpp
    src/renderer/Program.cpp
    src/renderer/VertexArray.cpp
    src/renderer/VertexBuffer.cpp
    src/renderer/Texture.cpp

    src/math/matx.hpp
    src/math/vec.hpp
)

if (CBX_EXAMPLES)  
    set(SOURCES 
        ${SOURCES}
        examples/main.cpp
    )
endif()

add_executable(Climbex ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(Climbex PUBLIC glfw GLEW::GLEW OpenGL::GL)

target_include_directories(Climbex PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "vendor"
    "src"
)

