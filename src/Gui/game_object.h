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


class GameObject
{
protected:
    std::weak_ptr<GameObject> parent_; // todo, get&set
    std::weak_ptr<Scene> scene_;

    std::vector<std::shared_ptr<Component>> components;

public:
    explicit GameObject(const std::shared_ptr<GameObject>& parent, const glm::vec3 &pos = glm::vec3(0.f));
    virtual ~GameObject();

    virtual void draw();
    [[nodiscard]] std::shared_ptr<Scene> getScene() const;

	template <class CompType>
    void addComponent();
};

template <class CompType>
void GameObject::addComponent()
{
	for(const auto& comp : components){
		if(typeid(comp.get()) == typeid(CompType)){
			return;
		}
	}
	components.emplace_back(Component::create<CompType>(this));
}

#endif // GAME_OBJECT_H
