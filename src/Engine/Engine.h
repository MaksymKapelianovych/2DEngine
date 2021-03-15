//
// Created by zephyrus on 05.02.21.
//

#ifndef INC_2DENGINE_ENGINE_H
#define INC_2DENGINE_ENGINE_H
#include <memory>

class GLFWwindow;
class Window;

//TODO maybe singleton
class Engine {

	GLFWwindow *window;
	std::shared_ptr<Window> w;

public:
	static int getWidth();
	static int getHeight();

	static int WIDTH;
	static int HEIGHT;

public:


    /**
     *
     * Create new engine
     */

    Engine();
	~Engine();

    /**
     * Run the engine
     * config must be set
     */
    void run();

    // Callbacks (temporary; todo create event system)
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};


#endif //INC_2DENGINE_ENGINE_H
