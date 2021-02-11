#include "eventqueue.h"

EventQueue::EventQueue()
{

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
    if(button == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS){
            mouse[0] = true;
        }else if(action == GLFW_RELEASE){
            mouse[0] = false;
        }
    }else if(button == GLFW_MOUSE_BUTTON_RIGHT){
        if(action == GLFW_PRESS){
            mouse[1] = true;
        }else if(action == GLFW_RELEASE){
            mouse[1] = false;
        }
    }else if(button == GLFW_MOUSE_BUTTON_MIDDLE){
        if(action == GLFW_PRESS){
            mouse[2] = true;
        }else if(action == GLFW_RELEASE){
            mouse[2] = false;
        }
    }
}
