//
// Created by zephyrus on 21.03.21.
//
#include <memory>
#include "BoxCollider.h"
#include "CircleCollider.h"

#include "Engine/game_object.h"
#include "location.h"

BoxCollider::BoxCollider(const std::weak_ptr<GameObject>& owner, uint width, uint height, std::string name)
	: Collider(owner, std::move(name)), width_(width), height_(height)
{
}


void BoxCollider::update(GLfloat deltaTime)
{

}
//bool BoxCollider::checkCollision(const std::weak_ptr<Collider>& other)
//{
//	if(other.expired()){
//		return false;
//	}
//	auto collider = other.lock();
//
//	if(this == collider.get()){
//		return false;
//	}
//
//	if(typeid(collider.get()) == typeid(BoxCollider)){
//		auto boxCollider = std::dynamic_pointer_cast<BoxCollider>(collider);
//
//		auto corners = getCorners();
//
//		for(auto corner : corners){
//			if(boxCollider->inside(corner)){
//				return true;
//			}
//		}
//
//		return inside(boxCollider);
//	}
//}
glm::vec2 BoxCollider::getCenter() const
{
	return owner_.lock()->getComponent<Location>()->getWorldPosition();
}
bool BoxCollider::checkCollision(const std::weak_ptr<BoxCollider>& other)
{
	if(other.expired()){
		return false;
	}
	auto collider = other.lock();
	if(this == collider.get()){
		return false;
	}
//	if(PhysicsSystem::getCollisionType(collisionName, collider->collisionName) == CollisionType::IGNORE){
//		return false;
//	}

	auto corners = getCorners();

	for(auto corner : corners){
		if(collider->inside(corner)){
			collide.emit(collider);
			collider->collide.emit(sharedFromThisByComponent<Collider>());
			return true;
		}
	}

	if(inside(collider)){
		collide.emit(collider);
		collider->collide.emit(sharedFromThisByComponent<Collider>());
		return true;
	}

	return false;
}
bool BoxCollider::checkCollision(const std::weak_ptr<CircleCollider>& other)
{
	if(other.expired()){
		return false;
	}
	auto collider = other.lock();
	if(PhysicsSystem::getCollisionType(collisionName, collider->collisionName) == CollisionType::IGNORE){
		return false;
	}

	auto corners = getCorners();

	for(auto corner : corners){
		if(collider->inside(corner)){
			collide.emit(collider);
			collider->collide.emit(weakFromThisByComponent<Collider>());
			return true;
		}
	}

	if(inside(collider)){
		collide.emit(collider);
		collider->collide.emit(weakFromThisByComponent<Collider>());
		return true;
	}

	return false;
}
//bool BoxCollider::checkCollision(const std::weak_ptr<CustomCollider>& other)
//{
//	return false;
//}
bool BoxCollider::inside(const std::weak_ptr<BoxCollider>& other)
{
	auto collider = other.lock();

	auto colliderCorners = collider->getCorners();

	for(auto corner : colliderCorners){
		if(!inside(corner)){
			return false;
		}
	}

	return true;
}
bool BoxCollider::inside(const std::weak_ptr<CircleCollider>& other)
{
	return false;
}
//bool BoxCollider::inside(const std::weak_ptr<CustomCollider>& other)
//{
//	return false;
//}
bool BoxCollider::inside(const glm::vec2& point)
{
	auto center = getCenter();
	if(center.x - getWidth()/2 <= point.x && point.x <= center.x + getWidth()/2 &&
		center.y - getHeight()/2 <= point.y && point.y <= center.y + getHeight()/2){
		std::cout << center.x - getWidth()/2 << " " << point.x << " " << center.x + getWidth()/2 << "\n";
	}
	return center.x - getWidth()/2 <= point.x && point.x <= center.x + getWidth()/2 &&
		center.y - getHeight()/2 <= point.y && point.y <= center.y + getHeight()/2;
}
void BoxCollider::setWidth(int width)
{
	width_ = width;
}
int BoxCollider::getWidth() const
{
	return width_;
}
void BoxCollider::setHeight(int height)
{
	height_ = height;
}
int BoxCollider::getHeight() const
{
	return height_;
}
std::vector<glm::vec2> BoxCollider::getCorners() const
{
	auto location = getCenter();

	std::vector<glm::vec2> corners{4};
	corners.emplace_back(location.x - getWidth()/2, location.y - getHeight()/2);
	corners.emplace_back(location.x + getWidth()/2, location.y - getHeight()/2);
	corners.emplace_back(location.x + getWidth()/2, location.y + getHeight()/2);
	corners.emplace_back(location.x - getWidth()/2, location.y + getHeight()/2);

	return corners;
}

