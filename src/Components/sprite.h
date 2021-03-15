//
// Created by zephyrus on 12.03.21.
//

#ifndef SPRITE_H
#define SPRITE_H

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

#include "component.h"
#include "drawable.h"
#include "Gui/shader.h"

class Sprite : public Component, public Drawable
{
	static const GLfloat WIDTH_SCALE, HEIGHT_SCALE;
	int width_, height_;
	glm::vec3 color_;
	std::unique_ptr<Shader> shader_;

	GLfloat vertices[12] = {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left
	};
	GLuint indices[6] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};
	GLuint VBO, VAO, EBO;

public:
	explicit Sprite(const std::weak_ptr<GameObject>& owner);

	int GetWidth() const;
	void SetWidth(int width);
	int GetHeight() const;
	void SetHeight(int height);
	const glm::vec3& GetColor() const;
	void SetColor(const glm::vec3& color);


public:
	virtual void update(GLfloat deltaTime) override;
	virtual std::string type() const override;

	virtual ~Sprite() override;

	// Drawable interface
public:
	void draw() override;
};


#endif //SPRITE_H
