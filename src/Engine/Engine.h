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

	static GLFWwindow *window;
	static std::shared_ptr<Window> w;

public:
	static int getWidth();
	static int getHeight();
	static std::weak_ptr<Window> getWindow();

	static int WIDTH;
	static int HEIGHT;


	/**
	 *
	 * Create new engine
	 */

	Engine();
	~Engine();

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


#endif //INC_2DENGINE_ENGINE_H
