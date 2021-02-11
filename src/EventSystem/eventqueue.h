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

class EventQueue
{
    bool keys[1024];
    bool mouse[3];
public:
    EventQueue();

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void mouse_key (GLFWwindow* window, int button, int action, int mode );
};

#endif // EVENTQUEUE_H
