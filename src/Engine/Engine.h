//
// Created by zephyrus on 05.02.21.
//

#ifndef INC_2DENGINE_ENGINE_H
#define INC_2DENGINE_ENGINE_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <memory>
#include "window.h"

class GLFWwindow;
class EventQueue;

//TODO maybe singleton
class Engine {

	static GLFWwindow *window;
	static std::shared_ptr<Window> w;
	static int WIDTH;
	static int HEIGHT;

public:
	static int getWidth();
	static int getHeight();
	template <class W, class ...Args>
	static std::shared_ptr<W> createWindow(uint width, uint height, const char * title, Args... args);
	static std::shared_ptr<Window> getWindow();

	static void closeWindow();

public:

	static void init();
	static void close();

    /**
     * Run the engine
     * config must be set
     */
    static void run();

    // Callbacks (temporary; todo create event system)
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

template <class W, class... Args>
std::shared_ptr<W> Engine::createWindow(uint width, uint height, const char * title, Args... args)
{
	if constexpr(!std::is_base_of_v<Window, W>){
		std::terminate();
	}
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(Engine::WIDTH, Engine::HEIGHT, title, nullptr, nullptr);
	auto temp = std::make_shared<W>(window, width, height, std::forward<Args>(args)...);
	w = temp;
	w->init();
	return temp;
}



#endif //INC_2DENGINE_ENGINE_H
