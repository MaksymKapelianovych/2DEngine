//
// Created by zephyrus on 21.03.21.
//

#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <memory>
#include <vector>
#include "component.h"
#include "Collider.h"


class BoxCollider: public Collider
{
	uint width_, height_;

public:
	BoxCollider() = delete;
	BoxCollider(const std::weak_ptr<GameObject>& owner, uint width, uint height, std::string name);

	std::vector<glm::vec2> getCorners() const;
	/**
	 * Setters & getters
	 */

	void setWidth(int width);
	int getWidth() const;
	void setHeight(int height);
	int getHeight() const;

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


#endif //BOXCOLLIDER_H
