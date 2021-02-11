#ifndef CONSTANTS_H
#define CONSTANTS_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

enum class Mouse{
    RIGHT_PRESSED,
    LEFT_PRESSED,
    NONE
};

enum class Type{
    Drawable,
    AxisVector,
    Point
};

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

#endif // CONSTANTS_H
