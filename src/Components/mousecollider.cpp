#include "mousecollider.h"
#include "PhysicsSystem/PhysicsSystem.h"
#include "EventSystem/FunctionWrapper.h"
#include "EventSystem/Signal.h"
#include "EventSystem/eventqueue.h"



MouseCollider::MouseCollider(const std::weak_ptr<GameObject>& owner)
	: Component(owner)
{
	EventQueue::addFunctionForMouse(GLFW_MOUSE_BUTTON_LEFT, {&MouseCollider::onLeftButtonClicked, this});
	EventQueue::addFunctionForMouse(GLFW_MOUSE_BUTTON_RIGHT, {&MouseCollider::onRightButtonClicked, this});

}

MouseCollider::~MouseCollider()
{
	EventQueue::removeFunctionForMouse(GLFW_MOUSE_BUTTON_LEFT, {&MouseCollider::onLeftButtonClicked, this});
	EventQueue::removeFunctionForMouse(GLFW_MOUSE_BUTTON_RIGHT, {&MouseCollider::onRightButtonClicked, this});
}

void MouseCollider::update(GLfloat deltaTime)
{

}

void MouseCollider::addOnCollide(CollideSignal::hashable_function_t function)
{
	collide.add(function);
}
void MouseCollider::onLeftButtonClicked(double x, double y)
{

}
void MouseCollider::onRightButtonClicked(double x, double y)
{

}
