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
#include <memory>

#include "Utils/constants.h"
class GameObject;


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
class Component
{
protected:
    std::weak_ptr<GameObject> owner_; 			 		//Component does not control owner`s life

    explicit Component(const std::shared_ptr<GameObject> &owner);
	virtual ~Component();

	/**
	 * Static functions
	 */
public:
	template <class T>
		static std::unique_ptr<T> create(const std::shared_ptr<GameObject>& obj);

	Component() = delete;

	/**
	 * Component function
	 */

public:
    virtual void update(GLfloat deltaTime) = 0;

    [[maybe_unused]]
    virtual std::string type() const;

    std::shared_ptr<GameObject> getOwner() const;
};

template <class T>
std::unique_ptr<T> Component::create(const std::shared_ptr<GameObject>& obj)
{
	return std::make_unique<T>(obj);
}



#endif // INC_2DENGINE_COMPONENT_H
