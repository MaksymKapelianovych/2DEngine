#include "eventqueue.h"

std::unordered_map<int, bool> EventQueue::keys;
std::unordered_map<int, bool> EventQueue::mouse;

int EventQueue::lastX;
int EventQueue::lastY;

std::unordered_map<int, Signal<double, double>> EventQueue::mousePressedSignals;
std::unordered_map<int, Signal<>> EventQueue::keyPressedSignals;

void EventQueue::init(GLFWwindow *window)
{
	glfwSetKeyCallback(window, EventQueue::key_callback);
	glfwSetCursorPosCallback(window, EventQueue::mouse_callback);
	glfwSetMouseButtonCallback(window, EventQueue::mouse_key);
	glfwSetScrollCallback(window, EventQueue::scroll_callback);

	keys[GLFW_KEY_0] = false;
	keys[GLFW_KEY_1] = false;
	keys[GLFW_KEY_2] = false;
	keys[GLFW_KEY_3] = false;
	keys[GLFW_KEY_4] = false;
	keys[GLFW_KEY_5] = false;
	keys[GLFW_KEY_6] = false;
	keys[GLFW_KEY_7] = false;
	keys[GLFW_KEY_8] = false;
	keys[GLFW_KEY_9] = false;

	keyPressedSignals[GLFW_KEY_0] = Signal<>();
	keyPressedSignals[GLFW_KEY_1] = Signal<>();
	keyPressedSignals[GLFW_KEY_2] = Signal<>();
	keyPressedSignals[GLFW_KEY_3] = Signal<>();
	keyPressedSignals[GLFW_KEY_4] = Signal<>();
	keyPressedSignals[GLFW_KEY_5] = Signal<>();
	keyPressedSignals[GLFW_KEY_6] = Signal<>();
	keyPressedSignals[GLFW_KEY_7] = Signal<>();
	keyPressedSignals[GLFW_KEY_8] = Signal<>();
	keyPressedSignals[GLFW_KEY_9] = Signal<>();

	mouse[GLFW_MOUSE_BUTTON_LEFT] = false;
	mouse[GLFW_MOUSE_BUTTON_MIDDLE] = false;
	mouse[GLFW_MOUSE_BUTTON_RIGHT] = false;

	mousePressedSignals[GLFW_MOUSE_BUTTON_LEFT] = Signal<double, double>();
	mousePressedSignals[GLFW_MOUSE_BUTTON_MIDDLE] = Signal<double, double>();
	mousePressedSignals[GLFW_MOUSE_BUTTON_RIGHT] = Signal<double, double>();



//	mouseReleasedSignals[GLFW_MOUSE_BUTTON_LEFT] = Signal<double, double>();
//	mouseReleasedSignals[GLFW_MOUSE_BUTTON_MIDDLE] = Signal<double, double>();
//	mouseReleasedSignals[GLFW_MOUSE_BUTTON_RIGHT] = Signal<double, double>();
}

void EventQueue::consumeEvents()
{
	for(auto [first, second] : mousePressedSignals){
		if(mouse[first]){
			second.emit(lastX, lastY);
		}
	}

	for(auto [first, second] : keyPressedSignals){
		if(keys[first]){
			second.emit();
		}
	}
}

void EventQueue::addFunctionForKey(int code, KeySignal::hashable_function_t function)
{
	keyPressedSignals[code].add(function);
}
void EventQueue::addFunctionForMouse(int code, MouseSignal::hashable_function_t function)
{
	mousePressedSignals[code].add(function);
}
void EventQueue::removeFunctionForKey(int code, KeySignal::hashable_function_t function)
{
	keyPressedSignals[code].remove(function);
}
void EventQueue::removeFunctionForMouse(int code, MouseSignal::hashable_function_t function)
{
	mousePressedSignals[code].remove(function);
}

void EventQueue::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if(key >= 0 && key <= 1024){
        if(action == GLFW_PRESS){
            keys[key] = true;
        }else if(action == GLFW_RELEASE){
            keys[key] = false;
        }
    }
}

void EventQueue::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    //call mouse collider or create new way to send mouse click event
}

void EventQueue::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{

}

void EventQueue::mouse_key(GLFWwindow *window, int button, int action, int mode)
{
	if(action == GLFW_PRESS){
		mouse[button] = true;
	}else if(action == GLFW_RELEASE){
		mouse[button] = false;
	}

//    if(button == GLFW_MOUSE_BUTTON_LEFT){
//        if(action == GLFW_PRESS){
//            mouse[0] = true;
//        }else if(action == GLFW_RELEASE){
//            mouse[0] = false;
//        }
//    }else if(button == GLFW_MOUSE_BUTTON_RIGHT){
//        if(action == GLFW_PRESS){
//            mouse[1] = true;
//        }else if(action == GLFW_RELEASE){
//            mouse[1] = false;
//        }
//    }else if(button == GLFW_MOUSE_BUTTON_MIDDLE){
//        if(action == GLFW_PRESS){
//            mouse[2] = true;
//        }else if(action == GLFW_RELEASE){
//            mouse[2] = false;
//        }
//    }
}

