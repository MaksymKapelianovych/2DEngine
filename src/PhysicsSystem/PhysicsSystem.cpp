//
// Created by zephyrus on 23.04.21.
//

#include "PhysicsSystem.h"

#include "Components/Collider.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"

std::vector<std::weak_ptr<Collider>> PhysicsSystem::colliders;
std::unordered_set<std::string> PhysicsSystem::colliderNames;
std::unordered_set<CollisionScheme> PhysicsSystem::colliderSchemes;

void PhysicsSystem::init()
{
	addColliderNames({"static", "dynamic"});

	addCollisionScheme(CollisionScheme::Builder("static")
		.addCollisionType("static", CollisionType::BLOCK)
		.addCollisionType("dynamic", CollisionType::BLOCK)
		.build());

	addCollisionScheme(CollisionScheme::Builder("dynamic")
		.addCollisionType("static", CollisionType::BLOCK)
		.addCollisionType("dynamic", CollisionType::OVERLAP)
		.build());


}

void PhysicsSystem::update(double dt)
{
	colliders.erase(std::remove_if(colliders.begin(), colliders.end(), [](std::weak_ptr<Collider>& c){
		return c.expired();
	}), colliders.end());
}

void PhysicsSystem::addCollider(std::weak_ptr<Collider> collider)
{
	if(!colliderNames.contains(collider.lock()->collisionName)){
		std::terminate();
	}
	colliders.emplace_back(collider);
}
void PhysicsSystem::addColliderNames(std::initializer_list<std::string> names)
{
	for(const std::string& name : names){
		if(PhysicsSystem::colliderNames.contains(name)){
			std::terminate();
		}
		colliderNames.emplace(name);
	}
}
void PhysicsSystem::addCollisionScheme(CollisionScheme scheme)
{
	colliderSchemes.emplace(scheme);
}
CollisionType PhysicsSystem::getCollisionType(const std::string& lhs, const std::string& rhs)
{
	auto firstCollisionScheme = std::find_if(colliderSchemes.begin(), colliderSchemes.end(), [&lhs](auto&& a){
			return a.getName() == lhs;
		});
	auto secondCollisionScheme = std::find_if(colliderSchemes.begin(), colliderSchemes.end(), [&rhs](auto&& a){
			return a.getName() == rhs;
		});
	if(firstCollisionScheme == colliderSchemes.end() || secondCollisionScheme == colliderSchemes.end()){
		return CollisionType::IGNORE;
	}

	auto firstCollisionPreset = firstCollisionScheme->collisions_.find(rhs);
	auto secondCollisionPreset = secondCollisionScheme->collisions_.find(lhs);

	if(firstCollisionPreset == firstCollisionScheme->collisions_.end() ||
		secondCollisionPreset == secondCollisionScheme->collisions_.end()){
		return CollisionType::BLOCK;
	}

	return firstCollisionPreset->second & secondCollisionPreset->second;
}
void PhysicsSystem::checkCollision(std::weak_ptr<Collider> collider)
{
	auto to = collider.lock();
	for(auto& c : colliders){
		if(c.expired()){
			continue;
		}
		auto from = c.lock();
		if(from == to){
			continue;
		}

		if(auto d = std::dynamic_pointer_cast<BoxCollider>(to))
		{
			if (from->checkCollision(d))
			{
				break;
			}
		}
		else if(auto d = std::dynamic_pointer_cast<CircleCollider>(to); from->checkCollision(d)){
			break;
		}
	}
}

CollisionScheme::CollisionScheme(Builder *builder)
{
	name_ = std::move(builder->name_);
	collisions_ = std::move(builder->collisions_);
}
std::string CollisionScheme::getName() const
{
	return name_;
}
CollisionScheme::Builder::Builder(std::string name)
{
	if(!PhysicsSystem::colliderNames.contains(name)){
		std::terminate();
	}
	name_ = name;
}
CollisionScheme::Builder& CollisionScheme::Builder::addCollisionType(std::string name, CollisionType type)
{
	if(PhysicsSystem::colliderNames.contains(name))
	{
		collisions_.emplace(name, type);
	}
	return *this;
}
CollisionScheme CollisionScheme::Builder::build()
{
	return CollisionScheme(this);
}

