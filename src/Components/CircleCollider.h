//
// Created by zephyrus on 27.03.21.
//

#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "component.h"
#include "Collider.h"
#include <vector>

class CircleCollider: public Collider
{
	uint radius_;
public:
	CircleCollider() = delete;
	CircleCollider(const std::weak_ptr<GameObject>& owner, uint radius, std::string name);

	std::vector<glm::vec2> getBorderPoints() const;
	/**
	 * Setter & getters
	 */
	uint getRadius() const;
	void setRadius(uint radius);

	/**
	 * Implementing Component functions
	 */
public:
	void update(GLfloat deltaTime) override;

	/**
	 * Implementing Collider functions
	 */
public:
	[[nodiscard]] glm::vec2 getCenter() const override;
	bool checkCollision(const std::weak_ptr<BoxCollider>& other) override;
	bool checkCollision(const std::weak_ptr<CircleCollider>& other) override;
//	bool checkCollision(const std::weak_ptr<CustomCollider>& other) override;
	bool inside(const std::weak_ptr<BoxCollider>& other) override;
	bool inside(const std::weak_ptr<CircleCollider>& other) override;
//	bool inside(const std::weak_ptr<CustomCollider>& other) override;
	bool inside(const glm::vec2& point) override;
};


#endif //CIRCLECOLLIDER_H
