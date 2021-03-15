//
// Created by zephyrus on 14.03.21.
//
#define STB_IMAGE_IMPLEMENTATION
#include "Utils/stb_image.h"

#include "image.h"
#include "Gui/game_object.h"
#include "Gui/scene.h"
#include "location.h"
#include <iostream>

Image::Image(const std::weak_ptr<GameObject>& owner) : Component(owner)
{
	shader_ = std::make_unique<Shader>("../resources/shaders/texture.vert", "../resources/shaders/texture.frag");
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);
}
void Image::setTexture(const GLchar* path)
{
	loadTexture(texture_, path);
}
void Image::loadTexture(GLuint& texture, const GLchar* path)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int n;
	unsigned char* image = stbi_load(path, &width_, &height_, &n, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);
}
void Image::draw()
{
	if(owner_.expired()){
		std::terminate(); // todo change to log error
	}


	auto owner = owner_.lock();
	glm::vec2 center = owner->getComponent<Location>()->getWorldPosition();
	glm::mat4 projection = owner->getScene()->getProjection();

	glm::mat4 model{1.f};
	model = glm::translate(model, glm::vec3(center, 0.f));
	model = glm::scale(model, glm::vec3(width_, height_, 0.f));

	shader_->use();

	shader_->setMat4("model", model);
	shader_->setMat4("projection", projection);
	shader_->setInt("tex", 0);

	//bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
int Image::getWidth() const
{
	return width_;
}
int Image::getHeight() const
{
	return height_;
}
void Image::update(GLfloat deltaTime)
{

}
