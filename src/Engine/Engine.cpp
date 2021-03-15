//
// Created by zephyrus on 05.02.21.
//

#include "Engine.h"
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <Components/location.h>

#include "Gui/game_object.h"
#include "Gui/window.h"
#include "Components/sprite.h"
#include "Components/image.h"

GLFWwindow *Engine::window = nullptr;
std::shared_ptr<Window> Engine::w = nullptr;
int Engine::WIDTH = 800;
int Engine::HEIGHT = 800;

void Engine::init() {
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions

	window = glfwCreateWindow(Engine::WIDTH, Engine::HEIGHT, "GL Engine", nullptr, nullptr);
	w = std::make_shared<Window>(window, Engine::WIDTH, Engine::HEIGHT);
	w->init();

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	//RenderSystem::init(window);
}

void Engine::run() {
	glViewport(0, 0, Engine::WIDTH, Engine::WIDTH);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		w->draw();
	}

	close();
}
void Engine::close()
{
	glfwTerminate();
}

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			int r = action;
			//keys[key] = true;
		else if (action == GLFW_RELEASE)
			return;
			//keys[key] = false;
	}
}
int Engine::getWidth()
{
	return Engine::WIDTH;
}
int Engine::getHeight()
{
	return Engine::HEIGHT;
}
std::weak_ptr<Window> Engine::getWindow()
{
	return w;
}
