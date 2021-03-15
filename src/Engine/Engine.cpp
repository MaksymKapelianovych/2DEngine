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

int Engine::WIDTH = 600;
int Engine::HEIGHT = 600;

Engine::Engine() {
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
	auto object = std::make_shared<GameObject>(nullptr);
	auto q = object->addComponent<Location>();
	if(auto s = object->addComponent<Image>()){
		s->setTexture("../resources/textures/1.png");
	}

//	auto s = object->addComponent<Sprite>();
//	s->SetWidth(10);
//	s->SetHeight(10);
//	s->SetColor({1.f, 0.5f, 0.3f});

	w->addToScene(object);
	std::cout << glGetError();
	glViewport(0, 0, Engine::WIDTH, Engine::WIDTH);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		w->draw();
	}
}
Engine::~Engine()
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
