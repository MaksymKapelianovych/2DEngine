#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>
#include <typeinfo>

#include "Utils/constants.h"
#include "Components/component.h"

class Shader;
class Scene;


class GameObject : public std::enable_shared_from_this<GameObject>
{
	friend class Scene;
protected:
    std::weak_ptr<GameObject> parent_; // todo, get&set
    std::vector<std::shared_ptr<GameObject>> childs_;
    std::weak_ptr<Scene> scene_;
	void setScene(std::weak_ptr<Scene> scene);

    std::vector<std::shared_ptr<Component>> components;

public:
    explicit GameObject(std::weak_ptr<GameObject> parent = std::weak_ptr<GameObject>(), const glm::vec3 &pos = glm::vec3(0.f));
    ~GameObject();

    void update(GLfloat dt);
    void draw();

    [[nodiscard]] std::shared_ptr<Scene> getScene() const;
    [[nodiscard]] std::weak_ptr<GameObject> getParent() const; // todo maybe change to std::optional
	void addChild(std::shared_ptr<GameObject> &&child);

	template <class CompType>
	std::shared_ptr<CompType> addComponent();
	template <class CompType>
	std::shared_ptr<CompType> getComponent() const;
};

template <class CompType>
std::shared_ptr<CompType> GameObject::addComponent()
{
	if(getComponent<CompType>()){
		return nullptr;
	}
	if constexpr (std::is_base_of_v<Drawable, CompType>){
		if(getComponent<Drawable>()){
			return nullptr;
		}
	}
	return std::dynamic_pointer_cast<CompType>(components.emplace_back(Component::create<CompType>(weak_from_this())));
}

template <class CompType>
std::shared_ptr<CompType> GameObject::getComponent() const
{
	for(const auto& comp : components){
		if(auto cast = std::dynamic_pointer_cast<CompType>(comp)){
			return cast;
		}
	}

	return nullptr;
}

#endif // GAME_OBJECT_H
