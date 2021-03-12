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
#include <vector>

#include "Utils/constants.h"
class Widget;


/**
 * Component is abstract object that describe concrete property of the object
 *
 * Component of each type is static container of all same objects
 *
 * All constructors are private because of new component.
 * Default constructor is deleted, all child`s default constructors must be deleted either.
 *
 * To create component use static method
 *
 * @tparam T
 */
template<typename T>
class Component
{
protected:
	static std::vector<T> components_;   //Component is owner for all components of it`s type
    Widget* owner_; 			 		//Component does not control owner`s life

    explicit Component(Widget* obj);
	virtual ~Component();

	/**
	 * Static functions
	 */
public:
	Component() = delete;


	[[nodiscard]]
	static T& create(Widget* obj);

	/**
	 * Component function
	 */

public:
    virtual void update(GLfloat deltaTime) = 0;

    [[maybe_unused]]
    virtual std::string type() const;

    Widget *getOwner() const;
};

#endif // INC_2DENGINE_COMPONENT_H
