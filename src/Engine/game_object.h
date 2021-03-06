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
#include "Components/drawable.h"
#include "Components/Collider.h"


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
	explicit GameObject(std::weak_ptr<GameObject> parent = std::weak_ptr<GameObject>());

	bool updated_;
public:
	static std::shared_ptr<GameObject> create(std::weak_ptr<GameObject> parent = std::weak_ptr<GameObject>(), const glm::vec2 &pos = glm::vec2(0.f));
//	template <class CompType>
//	std::shared_ptr<CompType> addComponent();
	template <class CompType, class ...Args>
	std::shared_ptr<CompType> addComponent(Args&& ...args);
	template <class CompType>
	std::shared_ptr<CompType> getComponent() const;


    ~GameObject();

    void update(GLfloat dt);
    void draw();

    [[nodiscard]] std::shared_ptr<Scene> getScene() const;
    [[nodiscard]] std::weak_ptr<GameObject> getParent() const; // todo maybe change to std::optional
	void addChild(std::shared_ptr<GameObject> child);
	void removeChild(std::shared_ptr<GameObject> child);

	void setReadyToUpdate();
};

template <class CompType, class ...Args>
std::shared_ptr<CompType> GameObject::addComponent(Args&&... args)
{
	if(getComponent<CompType>()){
		return nullptr;
	}
	if constexpr (std::is_base_of_v<Drawable, CompType>){
		if(getComponent<Drawable>()){
			return nullptr;
		}
	}else if constexpr (std::is_base_of_v<Collider, CompType>){
		if(getComponent<Collider>()){
			return nullptr;
		}
	}
	return std::dynamic_pointer_cast<CompType>(components.emplace_back(Component::create<CompType>(weak_from_this(),
			std::forward<Args>(args)...)));
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
