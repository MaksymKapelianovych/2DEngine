#ifndef WIDGET_H
#define WIDGET_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <list>

#include "constants.h"

class Shader;
class Scene;

class Component;

class Widget
{
protected:
    glm::vec4 m_matrixPos; //location component
    Shader* m_shader; //render system
    Scene* scene_;
    Widget* parent_; // todo, get&set
    glm::vec3 m_position; //location component

    std::list<Component*> components;

public:
    Widget(Scene* parent, const glm::vec3 &pos = glm::vec3(0.f));
    virtual ~Widget();

    virtual glm::vec2 getScreenPos();
    virtual glm::vec4 getMatrixPos();
    virtual void setPos(const glm::vec3 &pos);

    virtual void draw();
    virtual bool mouse_callback(double xpos, double ypos) = 0;
    virtual bool mouse_key (int button, int action, int mode ) = 0;


    virtual void move(const glm::vec3 &offset);

    virtual Type getType();

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3 &value);
    Scene *getScene() const;

    void addComponent(Component* comp);
};

#endif // WIDGET_H
