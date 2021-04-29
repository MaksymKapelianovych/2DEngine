//
// Created by zephyrus on 21.03.21.
//

#ifndef COLLIDER_H
#define COLLIDER_H
#include <memory>
#include <string>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "PhysicsSystem/PhysicsSystem.h"
#include "EventSystem/FunctionWrapper.h"
#include "EventSystem/Signal.h"
#include "component.h"

class BoxCollider;
class CircleCollider;
//class CustomCollider;


class Collider : public Component
{
	friend class BoxCollider;
	friend class CircleCollider;
protected:
	using CollideSignal = Signal<std::weak_ptr<Collider>>;
	CollideSignal collide;
public:
	const std::string collisionName;
	Collider(const std::weak_ptr<GameObject>& owner, std::string name);
	~Collider();

	[[nodiscard]] virtual glm::vec2 getCenter() const = 0;

	//bool checkCollision(const std::weak_ptr<Collider>& other);

	virtual bool checkCollision(const std::weak_ptr<BoxCollider>& other) = 0;
	virtual bool checkCollision(const std::weak_ptr<CircleCollider>& other) = 0;
//	virtual bool checkCollision(const std::weak_ptr<CustomCollider>& other) = 0;

	virtual bool inside(const std::weak_ptr<BoxCollider>& other) = 0;
	virtual bool inside(const std::weak_ptr<CircleCollider>& other) = 0;
//	virtual bool inside(const std::weak_ptr<CustomCollider>& other) = 0;

	virtual bool inside(const glm::vec2 &point) = 0;

	void addOnCollide(CollideSignal::hashable_function_t function);
	void removeOnCollide(CollideSignal::hashable_function_t function);
};


#endif //COLLIDER_H
