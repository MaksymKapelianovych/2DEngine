//
// Created by zephyrus on 12.03.21.
//

#include "sprite.h"

Sprite::Sprite(const std::shared_ptr<GameObject>& owner) : Component(owner)
{

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
	return width;
}
void Sprite::SetWidth(int width)
{
	Sprite::width = width;
}
int Sprite::GetHeight() const
{
	return height;
}
void Sprite::SetHeight(int height)
{
	Sprite::height = height;
}
const glm::vec4& Sprite::GetColor() const
{
	return color;
}
void Sprite::SetColor(const glm::vec4& color)
{
	Sprite::color = color;
}

