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
    Window(GLuint m_width, GLuint m_height);

//    bool key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) override;
//    bool mouse_callback(double xpos, double ypos) override;
//    bool scroll_callback(double xoffset, double yoffset) override;
//    bool mouseKey (int button, int action, int mode ) override;
//    bool drag_drop(double xoffset, double yoffset) override;
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
    //std::list<std::shared_ptr<Widget>> objects;
    //std::shared_ptr<Scene> activeScene;
    //std::shared_ptr<Widget> activeWidget;


    //static bool    keys[1024];
    GLfloat lastX  =  m_width  / 2.0;
    GLfloat lastY  =  m_height / 2.0;

    //Mouse mouseState = Mouse::NONE;
    //bool enableDrag = false;
};

#endif // WINDOW_H
