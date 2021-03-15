#include "game_object.h"

#include <utility>

#include "Components/location.h"

GameObject::GameObject(const std::shared_ptr<GameObject>& parent, const glm::vec3& pos) : std::enable_shared_from_this<GameObject>(), parent_(parent)
{
	if(parent){
		scene_ = parent->scene_;
	}
	//addComponent<Location>();
}

GameObject::~GameObject(){

}

void GameObject::draw()
{

}
void GameObject::setScene(std::weak_ptr<Scene> scene)
{
	if(scene_.lock()){
		return;
	}

	scene_ = std::move(scene);
}
std::shared_ptr<Scene> GameObject::getScene() const
{
	if(scene_.expired()){
		std::terminate(); // todo maybe change
	}
	return scene_.lock();
}
void GameObject::update(GLfloat dt)
{
	for(auto& comp : components){
		comp->update(dt);
	}
}




