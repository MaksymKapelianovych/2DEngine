#include "location.h"
#include "Engine/scene.h"
#include "Engine/game_object.h"
#include "Engine/Engine.h"
#include "Collider.h"
#include "PhysicsSystem/PhysicsSystem.h"

Location::Location(const std::weak_ptr<GameObject> &owner, const glm::vec2& pos)
	: Component(owner), position_(pos), velocity_(0.f), rotationAngle_(0.f)
{

}

Location::~Location(){

}

void Location::moveTo(glm::vec2 newPosition)
{
    setPosition(newPosition);
}

void Location::moveBy(glm::vec2 offset)
{
    position_ += offset;
}
void Location::setRotationAngle(float angle)
{
	rotationAngle_ = angle;
}
void Location::rotate(float angle)
{
	rotationAngle_ += angle;
}
float Location::getWorldRotationAngle() const
{
	if(auto owner = owner_.lock()->getParent().lock()){
		return owner->getComponent<Location>()->getWorldRotationAngle() + getLocalRotationAngle();
	}
	return getLocalRotationAngle();
}
float Location::getLocalRotationAngle() const
{
	return rotationAngle_;
}


glm::vec2 Location::getScreenPos()
{
	if(owner_.expired()){
		std::terminate(); // todo maybe change
	}
    std::shared_ptr<Scene> scene = owner_.lock()->getScene();
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(position_, 1.f));

    matrixPos_ = glm::vec4(scene->getProjection() * model * glm::vec4(0.f, 0.f, 0.f, 1.0f));

    glm::vec2 pos = glm::vec2(Engine::getWidth()/2+Engine::getWidth()/2*matrixPos_.x/matrixPos_.w,
						Engine::getHeight()/2-Engine::getHeight()/2*matrixPos_.y/matrixPos_.w);
    return pos;
}

void Location::update(GLfloat deltaTime)
{
	previousPosition_ = position_;
    position_ += velocity_ * deltaTime;

    if(auto collider = getOwner()->getComponent<Collider>()){
    	PhysicsSystem::checkCollision(collider);
    }
}

glm::vec2 Location::getWorldPosition() const
{
	if(auto owner = owner_.lock()->getParent().lock()){
		return owner->getComponent<Location>()->getWorldPosition() + getLocalPosition();
	}
	return getLocalPosition();
}

glm::vec2 Location::getLocalPosition() const
{
    return position_;
}

void Location::setPosition(const glm::vec2 &position)
{
    position_ = position;
}

glm::vec4 Location::getMatrixPos() const
{
    return matrixPos_;
}

glm::vec2 Location::getVelocity() const
{
    return velocity_;
}

void Location::setVelocity(const glm::vec2 &velocity)
{
    velocity_ = velocity;
}
void Location::onCollide(std::weak_ptr<Collider> other)
{
	if(auto collider = getOwner()->getComponent<Collider>()){
		std::string a = collider->collisionName;
		std::string b = other.lock()->collisionName;
		if(PhysicsSystem::getCollisionType(collider->collisionName, other.lock()->collisionName) == CollisionType::BLOCK){
			position_ = previousPosition_;
		}
	}
}

