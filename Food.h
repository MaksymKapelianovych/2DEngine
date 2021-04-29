//
// Created by zephyrus on 28.03.21.
//

#ifndef FOOD_H
#define FOOD_H
#include <memory>
#include "Components/component.h"

class GameObject;
class Cell;

class Food : public Component
{
	static std::string texture_;
	std::weak_ptr<Cell> cell_;

public:
	static void setTexture(std::string&& texture);
	Food(const std::weak_ptr<GameObject>& owner, std::weak_ptr<Cell> cell);

	void init();

public:
	void update(float dt) override;

};


#endif //FOOD_H
