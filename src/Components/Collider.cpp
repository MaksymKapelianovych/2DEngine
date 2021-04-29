//
// Created by zephyrus on 21.03.21.
//

#include "Collider.h"

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "location.h"
#include "Engine/game_object.h"

#include <utility>
#include <memory>

Collider::Collider(const std::weak_ptr<GameObject>& owner, std::string name)
	: Component(owner), collisionName(std::move(name))
{
	addOnCollide({&Location::onCollide, getOwner()->getComponent<Location>().get()});
}

Collider::~Collider() noexcept
{
	removeOnCollide({&Location::onCollide, getOwner()->getComponent<Location>().get()});
}

void Collider::addOnCollide(CollideSignal::hashable_function_t function)
{
	collide.add(function);
}
void Collider::removeOnCollide(CollideSignal::hashable_function_t function)
{
	collide.remove(function);
}

