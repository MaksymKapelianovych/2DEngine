//
// Created by zephyrus on 20.03.21.
//

#ifndef WALL_H
#define WALL_H
#include <memory>
#include "Components/component.h"

class GameObject;
class Cell;

class Wall : public Component
{
	static std::vector<std::string> textures_;

	std::weak_ptr<Cell> cell_;

public:
	static void setTextures(std::vector<std::string>&& textures);
	Wall(const std::weak_ptr<GameObject>& owner, std::weak_ptr<Cell> cell);

	void init();

public:
	void update(float dt) override;
};


#endif //WALL_H
