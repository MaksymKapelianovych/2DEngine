//
// Created by zephyrus on 27.03.21.
//

#include "CircleCollider.h"

#include <cmath>
#include <utility>

#include "BoxCollider.h"

#include "Engine/game_object.h"
#include "location.h"

CircleCollider::CircleCollider(const std::weak_ptr<GameObject>& owner, uint radius, std::string name)
	: Collider(owner, std::move(name)), radius_(radius)
{

}
std::vector<glm::vec2> CircleCollider::getBorderPoints() const
{
	std::vector<glm::vec2> borders{4};
	auto center = getCenter();

	borders.emplace_back(center.x, center.y - getRadius());
	borders.emplace_back(center.x + getRadius(), center.y);
	borders.emplace_back(center.x, center.y + getRadius());
	borders.emplace_back(center.x - getRadius(), center.y);

	return borders;
}
void CircleCollider::update(GLfloat deltaTime)
{

}
glm::vec2 CircleCollider::getCenter() const
{
	return owner_.lock()->getComponent<Location>()->getWorldPosition();
}
bool CircleCollider::checkCollision(const std::weak_ptr<BoxCollider>& other)
{
	if(other.expired()){
		return false;
	}
	auto collider = other.lock();
	if(PhysicsSystem::getCollisionType(collisionName, collider->collisionName) == CollisionType::IGNORE){
		return false;
	}

	auto corners = collider->getCorners();
	for(auto corner : corners){
		if(inside(corner)){
			return true;
		}
	}

	return collider->inside(std::dynamic_pointer_cast<CircleCollider>(shared_from_this()));
}
bool CircleCollider::checkCollision(const std::weak_ptr<CircleCollider>& other)
{
	if(other.expired()){
		return false;
	}
	auto collider = other.lock();
	if(this == collider.get()){
		return false;
	}
	if(PhysicsSystem::getCollisionType(collisionName, collider->collisionName) == CollisionType::IGNORE){
		return false;
	}

	return glm::distance(collider->getCenter(), getCenter()) < collider->getRadius() + getRadius();
}
//bool CircleCollider::checkCollision(const std::weak_ptr<CustomCollider>& other)
//{
//	return false;
//}
bool CircleCollider::inside(const std::weak_ptr<BoxCollider>& other)
{
	if(other.expired()){
		return false;
	}
	auto collider = other.lock();

	auto corners = collider->getCorners();

	for(auto corner : corners){
		if(!inside(corner)){
			return false;
		}
	}

	return true;
}
bool CircleCollider::inside(const std::weak_ptr<CircleCollider>& other)
{
	if(other.expired()){
		return false;
	}
	auto collider = other.lock();

	auto center = getCenter();
	auto colliderCenter = collider->getCenter();

	return glm::distance(center, colliderCenter) + collider->getRadius() < getRadius();
}
//bool CircleCollider::inside(const std::weak_ptr<CustomCollider>& other)
//{
//	return false;
//}
bool CircleCollider::inside(const glm::vec2& point)
{
	return glm::distance(point, getCenter()) <= getRadius();
}
uint CircleCollider::getRadius() const
{
	return radius_;
}
void CircleCollider::setRadius(uint radius)
{
	radius_ = radius;
}
