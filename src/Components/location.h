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

class Location : public Component
{
	friend class Component;

    glm::vec2 position_;
    glm::vec4 matrixPos_;
    glm::vec2 velocity_; // todo maybe change to enum Direction and double speed
public:
	Location() = delete;
	explicit Location(const std::weak_ptr<GameObject> &owner);
	~Location() override;

    void moveTo(glm::vec2 newLocation);
    void moveBy(glm::vec2 offset);


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

	void setPosition(const glm::vec2 &position);
    void setVelocity(const glm::vec2 &velocity);
};



#endif // INC_2DENGINE_LOCATION_H
