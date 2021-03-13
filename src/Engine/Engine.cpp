//
// Created by zephyrus on 05.02.21.
//

#include "Engine.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "Gui/game_object.h"
#include "Components/sprite.h"

Engine::Engine() {
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions

	window = glfwCreateWindow(800, 600, "GL Engine", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	RenderSystem::init(window);
}

void Engine::run() {
	auto object = std::make_shared<GameObject>(nullptr);
	object->addComponent<Sprite>();
	auto s = object->getComponent<Sprite>();
	while (!glfwWindowShouldClose(window)) {
		RenderSystem::draw();
	}
}
Engine::~Engine()
{
	glfwTerminate();
}
