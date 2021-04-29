//
// Created by zephyrus on 23.04.21.
//

#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H
#include "Components/component.h"

class PlayerMove : public Component
{
public:
	PlayerMove(const std::weak_ptr<GameObject>& owner);

public:
	void update(GLfloat deltaTime) override;

	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();
};


#endif //PLAYERMOVE_H
