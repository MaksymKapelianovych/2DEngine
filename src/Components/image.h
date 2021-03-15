//
// Created by zephyrus on 14.03.21.
//

#ifndef IMAGE_H
#define IMAGE_H
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "component.h"
#include "Gui/shader.h"

class Image : public Component, public Drawable
{
	int width_, height_;
	std::unique_ptr<Shader> shader_;
	glm::mat4 model_{1.f};
	GLfloat vertices[20] = {
		0.5f,  0.5f, 0.0f, 1.f, 1.f,  //Top Right
		0.5f, -0.5f, 0.0f, 1.f, 0.f,  // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.f, 0.f,  // Bottom Left
		-0.5f,  0.5f, 0.0f, 0.f, 1.f   // Top Left
	};
public:
	virtual void update(GLfloat deltaTime) override;
private:
	GLuint indices[6] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};
	GLuint VBO, VAO, EBO;
	GLuint texture_;

public:
	Image() = delete;
	Image(const std::weak_ptr<GameObject> &owner);

public:
	void setTexture(const GLchar *path);
	void draw() override;

	int getWidth() const;
	int getHeight() const;

private:
	void loadTexture(GLuint &texture, const GLchar *path); // todo create texture loader class

};


#endif //IMAGE_H
