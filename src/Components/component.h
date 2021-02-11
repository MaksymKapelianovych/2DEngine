#ifndef INC_2DENGINE_COMPONENT_H
#define INC_2DENGINE_COMPONENT_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "2DEngine/constants.h"
class Widget;

class Component
{
protected:
    Widget* owner_;  //Component does not control owner`s life
public:
    Component(Widget* obj);
    virtual ~Component();

    virtual void update(GLfloat deltaTime) = 0;
//    virtual void addObject(Widget*) = 0;
//    virtual void removeObject(Widget*) = 0;

    virtual std::string type() const;
    Widget *getOwner() const;
};

#endif // INC_2DENGINE_COMPONENT_H
