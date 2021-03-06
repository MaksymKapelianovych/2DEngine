#ifndef INC_2DENGINE_LOCATION_H
#define INC_2DENGINE_LOCATION_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <vector>

#include "component.h"

class Collider;

class Location : public Component
{
	friend class Component;
	friend class Collider;

    glm::vec2 position_;
    glm::vec4 matrixPos_;
    glm::vec2 velocity_; // todo maybe change to enum Direction and double speed
    glm::vec2 previousPosition_;
    float rotationAngle_;

public:
	Location() = delete;
	explicit Location(const std::weak_ptr<GameObject> &owner, const glm::vec2& pos);
	~Location() override;

    void moveTo(glm::vec2 newLocation);
    void moveBy(glm::vec2 offset);

    void setRotationAngle(float angle);
    void rotate(float angle);


    // Component interface
public:
    void update(GLfloat deltaTime) override;


public:
    //Getters & setters
	[[nodiscard]] glm::vec2 getScreenPos();
    [[nodiscard]] glm::vec4 getMatrixPos() const;
    [[nodiscard]] glm::vec2 getLocalPosition() const;
    [[nodiscard]] glm::vec2 getWorldPosition() const;
	[[nodiscard]] glm::vec2 getVelocity() const;
	float getLocalRotationAngle() const;
	float getWorldRotationAngle() const;

	void setPosition(const glm::vec2 &position);
    void setVelocity(const glm::vec2 &velocity);

private:
	void onCollide(std::weak_ptr<Collider> other);
};



#endif // INC_2DENGINE_LOCATION_H
