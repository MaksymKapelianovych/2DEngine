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
#include "drawable.h"

class GameObject;


/**
 * Component is abstract object that describe concrete property of the object
 *
 *
 * All constructors are private because of new component.
 * Default constructor is deleted, all child`s default constructors must be deleted either.
 *
 * To create component use static method
 *
 * @tparam T
 */
class Component : protected std::enable_shared_from_this<Component>
{
protected:
    std::weak_ptr<GameObject> owner_; 			 		//Component does not control owner`s life

    explicit Component(const std::weak_ptr<GameObject> &owner);
	virtual ~Component();

	/**
	 * Static functions
	 */
public:
	template <class T>
	static std::shared_ptr<T> create(const std::weak_ptr<GameObject>& obj);

	template <class CompType>
	std::weak_ptr<CompType> weakFromThisByComponent();

	template <class CompType>
	std::shared_ptr<CompType> sharedFromThisByComponent();

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
std::shared_ptr<T> Component::create(const std::weak_ptr<GameObject>& obj)
{
	auto component = std::make_shared<T>(obj);
	return component;
}

template <class CompType>
std::weak_ptr<CompType> Component::weakFromThisByComponent()
{
	return std::dynamic_pointer_cast<CompType>(weak_from_this().lock());
}
template <class CompType>
std::shared_ptr<CompType> Component::sharedFromThisByComponent()
{
	return std::dynamic_pointer_cast<CompType>(shared_from_this());
}


#endif // INC_2DENGINE_COMPONENT_H
