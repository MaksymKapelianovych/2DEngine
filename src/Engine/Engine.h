//
// Created by zephyrus on 05.02.21.
//

#ifndef INC_2DENGINE_ENGINE_H
#define INC_2DENGINE_ENGINE_H
#include "RenderSystem/rendersystem.h"

class GLFWwindow;

//TODO maybe singleton
class Engine {

	GLFWwindow *window;
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
