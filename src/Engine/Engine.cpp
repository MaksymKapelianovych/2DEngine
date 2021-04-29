//
// Created by zephyrus on 05.02.21.
//

#include "Engine.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <Components/location.h>

#include "game_object.h"
#include "window.h"
#include "EventSystem/eventqueue.h"
#include "PhysicsSystem/PhysicsSystem.h"
#include "Components/sprite.h"
#include "Components/image.h"
class RenderSystem{
public:
	static void init(GLFWwindow* w);
};
GLFWwindow *Engine::window = nullptr;
std::shared_ptr<Window> Engine::w = nullptr;
int Engine::WIDTH = 800;
int Engine::HEIGHT = 800;

void Engine::init() {
	glfwMakeContextCurrent(window);
	PhysicsSystem::init();
	EventQueue::init(window);
	RenderSystem::init(window);

	EventQueue::addFunctionForKey(GLFW_KEY_ESCAPE, { closeWindow });

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

}

void Engine::run() {
	double time = 0;
	glViewport(0, 0, Engine::WIDTH, Engine::WIDTH);
	while (!glfwWindowShouldClose(window)) {
		double temp = glfwGetTime();
		double dt = temp - time;
		time = temp;

		glfwPollEvents();
		EventQueue::consumeEvents();
		PhysicsSystem::update(dt);

		w->update(dt);
		w->draw();
	}

	close();
}
void Engine::close()
{
	glfwTerminate();
}

void Engine::closeWindow()
{
	glfwSetWindowShouldClose(window, GL_TRUE);
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
std::shared_ptr<Window> Engine::getWindow()
{
	return w;
}
