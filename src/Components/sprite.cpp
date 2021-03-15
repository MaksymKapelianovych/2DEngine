//
// Created by zephyrus on 12.03.21.
//
#include <iostream>

#include "sprite.h"
#include "Gui/scene.h"
#include "Gui/game_object.h"
#include "location.h"

const GLfloat Sprite::WIDTH_SCALE = 10.f;
const GLfloat Sprite::HEIGHT_SCALE = 10.f;

Sprite::Sprite(const std::weak_ptr<GameObject>& owner) : Component(owner)
{
    shader_ = std::make_unique<Shader>("../resources/shaders/sprite.vert", "../resources/shaders/sprite.frag");
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);

	SetWidth(Sprite::WIDTH_SCALE);
	SetHeight(Sprite::HEIGHT_SCALE);
}

void Sprite::update(GLfloat deltaTime)
{
	// nothing
}
std::string Sprite::type() const
{
	return Component::type();
}
Sprite::~Sprite()
{

}
int Sprite::GetWidth() const
{
	return width_;
}
void Sprite::SetWidth(int width)
{
	Sprite::width_ = width;
}
int Sprite::GetHeight() const
{
	return height_;
}
void Sprite::SetHeight(int height)
{
	Sprite::height_ = height;
}
const glm::vec3& Sprite::GetColor() const
{
	return color_;
}
void Sprite::SetColor(const glm::vec3& color)
{
	Sprite::color_ = color;
}

void Sprite::draw()
{
	if(owner_.expired()){
		std::terminate(); // todo change to log error
	}


	auto owner = owner_.lock();
	glm::vec2 center = owner->getComponent<Location>()->getWorldPosition();
	glm::mat4 projection = owner->getScene()->getProjection();
	glm::mat4 model{1.f};
	model = glm::translate(model, glm::vec3(center, 0.f));
	model = glm::scale(model, glm::vec3(300.f, 300.f, 0.f));

	shader_->use();

	shader_->setMat4("projection", projection);
    shader_->setMat4("model", model);
	shader_->setVec3("color", color_);


	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

