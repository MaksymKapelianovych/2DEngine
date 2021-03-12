#include "game_object.h"

#include "Components/location.h"

GameObject::GameObject(const std::shared_ptr<GameObject>& parent, const glm::vec3& pos) : parent_(parent)
{
	addComponent<Location>();
}

GameObject::~GameObject(){

}

void GameObject::draw()
{

}
std::shared_ptr<Scene> GameObject::getScene() const
{
	if(scene_.expired()){
		std::terminate(); // todo maybe change
	}
	return scene_.lock();
}



