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
        engine/Vectors.h
        engine/controllers/TopDownController.h
        engine/controllers/TopDownController.cpp
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
        engine/Camera.cpp
        engine/Camera.h
        engine/Mat4.h
        engine/Mat4.cpp
        engine/controllers/Controller.h
        engine/controllers/PlatformerController.cpp
        engine/controllers/PlatformerController.h
        engine/WorldObject.cpp
        engine/WorldObject.h
        engine/Texture.cpp
        engine/Texture.h
        engine/Sprite.cpp
        engine/Sprite.h
        engine/TextureMap.cpp
        engine/TextureMap.h
        engine/Animation.cpp
        engine/Animation.h
        engine/Font.cpp
        engine/Font.h
        engine/Text.cpp
        engine/Text.h
)
target_include_directories(${PROJECT_NAME} PRIVATE
        C:/Users/JonahW/vcpkg/installed/x64-mingw-dynamic/include
)

target_link_libraries(physics PRIVATE SDL2::SDL2main SDL2::SDL2 glad::glad)
