#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include "Signal.h"

class EventQueue
{
    //bool keys[1024];
    //bool mouse[3];
public:
    using MouseSignal = Signal<double, double>;
    using KeySignal = Signal<>;

private:
    static std::unordered_map<int, bool> keys;
    static std::unordered_map<int, bool> mouse;

    static int lastX, lastY;

    static std::unordered_map<int, MouseSignal> mousePressedSignals;
	static std::unordered_map<int, KeySignal> keyPressedSignals;
	//static std::unordered_map<int, Signal<double, double>> mouseReleasedSignals;
public:
    //EventQueue();

	static void init(GLFWwindow* window);
	static void consumeEvents();

	static void addFunctionForKey(int code, KeySignal::hashable_function_t function);
	static void addFunctionForMouse(int code, MouseSignal::hashable_function_t function);
	static void removeFunctionForKey(int code, KeySignal::hashable_function_t function);
	static void removeFunctionForMouse(int code, MouseSignal::hashable_function_t function);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_key (GLFWwindow* window, int button, int action, int mode );
};

#endif // EVENTQUEUE_H
