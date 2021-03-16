cmake_minimum_required(VERSION 3.5)
project(2DEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(2DEngine main.cpp
        src/Gui/camera.cpp
        src/Gui/camera.h
        src/Components/component.cpp
        src/Components/component.h
        src/Components/location.cpp
        src/Components/location.h
        src/Components/mesh.cpp
        src/Components/mesh.h
        src/Components/model.cpp
        src/Components/model.h
        src/Components/mousecollider.cpp
        src/Components/mousecollider.h
        src/EventSystem/eventqueue.cpp
        src/EventSystem/eventqueue.h
        src/Gui/scene.cpp
        src/Gui/scene.h
        src/Gui/window.cpp
        src/Gui/window.h
        src/Gui/game_object.cpp
        src/Gui/game_object.h
        src/Gui/shader.cpp
        src/Gui/shader.h
        src/Utils/constants.h
        src/Utils/noise.h
        src/Utils/stb_image.h
        src/Utils/utils.h
        src/Engine/Engine.cpp
        src/Engine/Engine.h src/EventSystem/mouseevents.cpp src/EventSystem/mouseevents.h src/Components/sprite.cpp src/Components/sprite.h src/Components/drawable.cpp src/Components/drawable.h src/Components/image.cpp src/Components/image.h Map.cpp Map.h Cell.cpp Cell.h)

include_directories(src)

#include_directories(/home/zephyrus/libs/glfw-3.3.2/include)
add_subdirectory(lib/glfw-3.3.2)
#find_library(glfw REQUIRED /home/zephyrus/libs/glfw-3.3.2/src)

target_link_libraries(2DEngine -lGL -lGLEW glfw)
