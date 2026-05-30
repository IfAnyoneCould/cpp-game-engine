cmake_minimum_required(VERSION 4.2)
set(CMAKE_PREFIX_PATH "C:/Users/JonahW/vcpkg/installed/x64-mingw-dynamic")

project(physics)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/JonahW/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

find_package(SDL2 REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(physics main.cpp
        Grid.h
        Grid.cpp
        Unit.h
        Particle.h
        Particle.cpp
        Vector2.h
        Forces.h
        Vectors.h
        MovementController.h
        MovementController.cpp
        Triangle.h
        Shape.h
        Constants.h
        Shader.h
        Shader.cpp
        Vertex.h
        Vertex.cpp
        Shape.cpp
        RegularPolygon.cpp
        RegularPolygon.h
        Colors.h
)

target_link_libraries(physics PRIVATE SDL2::SDL2main SDL2::SDL2 glad::glad)
