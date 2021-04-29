//
// Created by zephyrus on 23.04.21.
//

#include "PlayerMove.h"
#include "Engine/game_object.h"
#include "Components/location.h"
#include "EventSystem/eventqueue.h"

PlayerMove::PlayerMove(const std::weak_ptr<GameObject>& owner)
	: Component(owner)
{
	EventQueue::addFunctionForKey(GLFW_KEY_0, {&PlayerMove::moveUp, this});
	EventQueue::addFunctionForKey(GLFW_KEY_1, {&PlayerMove::moveRight, this});
	EventQueue::addFunctionForKey(GLFW_KEY_2, {&PlayerMove::moveDown, this});
	EventQueue::addFunctionForKey(GLFW_KEY_3, {&PlayerMove::moveLeft, this});

}
void PlayerMove::update(GLfloat deltaTime)
{

}
void PlayerMove::moveUp()
{
	getOwner()->getComponent<Location>()->setVelocity({0.f, 10.f});
}
void PlayerMove::moveRight()
{
	getOwner()->getComponent<Location>()->setVelocity({10.f, 0.f});

}
void PlayerMove::moveDown()
{
	getOwner()->getComponent<Location>()->setVelocity({0.f, -10.f});

}
void PlayerMove::moveLeft()
{
	getOwner()->getComponent<Location>()->setVelocity({-10.f, 0.f});

}
