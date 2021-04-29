#include "game_object.h"

#include <utility>

#include "Components/location.h"

std::shared_ptr<GameObject> GameObject::create(std::weak_ptr<GameObject> parent, const glm::vec2& pos)
{
	std::shared_ptr<GameObject> object(new GameObject(std::move(parent)));
	object->addComponent<Location>(pos);
	return object;
}

GameObject::GameObject(std::weak_ptr<GameObject> parent) : std::enable_shared_from_this<GameObject>(), parent_(std::move(parent))
{
	if(auto p = parent_.lock()){
		scene_ = p->scene_;
	}
	//addComponent<Location>();
}

GameObject::~GameObject(){

}

void GameObject::draw()
{
	for(auto& comp : components){
		if(auto drawable = std::dynamic_pointer_cast<Drawable>(comp)){
			drawable->draw();
		}
	}

	for(auto& child: childs_){
		child->draw();
	}
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
	if(updated_){
		return;
	}
	updated_ = true;
	for(auto& comp : components){
		comp->update(dt);
	}

	for(auto& child: childs_){
		child->update(dt);
	}
}
void GameObject::addChild(std::shared_ptr<GameObject> child)
{
//	if(child.use_count() != 1){
//		std::terminate(); // todo change with warning
//	}
	child->parent_ = weak_from_this();
	childs_.emplace_back(child);
}
void GameObject::removeChild(std::shared_ptr<GameObject> child)
{
	childs_.erase(std::remove(childs_.begin(), childs_.end(), child), childs_.end());
}
std::weak_ptr<GameObject> GameObject::getParent() const
{
	return parent_;
}
void GameObject::setReadyToUpdate()
{
	updated_ = false;
	for(auto& child: childs_){
		child->setReadyToUpdate();
	}
}





