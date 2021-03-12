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

class Sprite : public Component
{
	int width, height;
	glm::vec4 color;

public:
	explicit Sprite(const std::shared_ptr<GameObject>& owner);

	int GetWidth() const;
	void SetWidth(int width);
	int GetHeight() const;
	void SetHeight(int height);
	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);

public:
	virtual void update(GLfloat deltaTime) override;
	virtual std::string type() const override;
protected:
	virtual ~Sprite() override;
};


#endif //SPRITE_H
