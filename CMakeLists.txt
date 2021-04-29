cmake_minimum_required(VERSION 3.5)
project(2DEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(2DEngine main.cpp
        src/RenderSystem/camera.cpp
        src/RenderSystem/camera.h
        src/Components/component.cpp
        src/Components/component.h
        src/Components/location.cpp
        src/Components/location.h
        src/Components/mousecollider.cpp
        src/Components/mousecollider.h
        src/EventSystem/eventqueue.cpp
        src/EventSystem/eventqueue.h
        src/Engine/scene.cpp
        src/Engine/scene.h
        src/Engine/window.cpp
        src/Engine/window.h
        src/Engine/game_object.cpp
        src/Engine/game_object.h
        src/RenderSystem/shader.cpp
        src/RenderSystem/shader.h
        src/Utils/constants.h
        src/Utils/noise.h
        src/Utils/stb_image.h
        src/Utils/utils.h
        src/Engine/Engine.cpp
        src/Engine/Engine.h src/Components/sprite.cpp src/Components/sprite.h src/Components/drawable.cpp src/Components/drawable.h src/Components/image.cpp src/Components/image.h Map.cpp Map.h Cell.cpp Cell.h PacMan.cpp PacMan.h Wall.cpp Wall.h src/Components/Collider.cpp src/Components/Collider.h src/Components/BoxCollider.cpp src/Components/BoxCollider.h Path.cpp Path.h src/Components/CircleCollider.cpp src/Components/CircleCollider.h Food.cpp Food.h Ghost.cpp Ghost.h src/EventSystem/FunctionWrapper.h src/EventSystem/Signal.h PlayerMove.cpp PlayerMove.h src/PhysicsSystem/PhysicsSystem.h src/PhysicsSystem/PhysicsSystem.cpp)

include_directories(src)

#include_directories(/home/zephyrus/libs/glfw-3.3.2/include)
add_subdirectory(lib/glfw-3.3.2)
#find_library(glfw REQUIRED /home/zephyrus/libs/glfw-3.3.2/src)

target_link_libraries(2DEngine -lGL -lGLEW glfw)
