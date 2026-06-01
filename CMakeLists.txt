cmake_minimum_required(VERSION 4.2)
set(CMAKE_PREFIX_PATH "C:/Users/JonahW/vcpkg/installed/x64-mingw-dynamic")

project(physics)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/JonahW/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

find_package(SDL2 REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(physics game/main.cpp
        engine/Unit.h
        engine/PhysicsObject.h
        engine/PhysicsObject.cpp
        engine/Vector2.h
        engine/Forces.h
        engine/Vectors.h
        engine/MovementController.h
        engine/MovementController.cpp
        engine/Triangle.h
        engine/Shape.h
        engine/Constants.h
        engine/Shader.h
        engine/Shader.cpp
        engine/Vertex.h
        engine/Vertex.cpp
        engine/Shape.cpp
        engine/RegularPolygon.cpp
        engine/RegularPolygon.h
        engine/Colors.h
        engine/Rectangle.cpp
        engine/Rectangle.h
        engine/Geometry.h
        engine/Physics.cpp
        engine/Physics.h
        engine/GameObject.cpp
        engine/GameObject.h
        engine/Game.h
        engine/Engine.cpp
        engine/Engine.h
)

target_link_libraries(physics PRIVATE SDL2::SDL2main SDL2::SDL2 glad::glad)
