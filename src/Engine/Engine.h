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

    /**
     * Run the engine
     * config must be set
     */
    void run();

    /**
     *
     */
     ~Engine();
};


#endif //INC_2DENGINE_ENGINE_H
