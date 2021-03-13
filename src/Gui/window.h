#ifndef WINDOW_H
#define WINDOW_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "scene.h"

class Window
{
public:
	//Window() = delete;
    explicit Window(GLuint m_width = 800, GLuint m_height = 600);

    void update(double deltaTime);
    void draw();

    //Getters & setters
    GLuint getWidth() const;
    void setWidth(const GLuint &value);

    GLuint getHeight() const;
    void setHeight(const GLuint &value);

private:
    GLuint m_width;
    GLuint m_height;

    std::list<Scene*> childs;

    GLfloat lastX  =  m_width  / 2.0;
    GLfloat lastY  =  m_height / 2.0;

};

#endif // WINDOW_H
