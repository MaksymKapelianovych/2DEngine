//
// Created by zephyrus on 20.03.21.
//

#ifndef PACMAN_H
#define PACMAN_H
#include <memory>
#include "Components/component.h"

class Cell;
class PacMan : public Component
{
	std::weak_ptr<Cell> cell_;
	std::vector<std::string> textures_;
	std::vector<std::weak_ptr<Cell>> path_;

public:
	PacMan(const std::weak_ptr<GameObject>& owner, std::weak_ptr<Cell> cell);

	void tryDfs(const std::weak_ptr<Cell>& target);


private:
	//void dfs(std::weak_ptr<Cell> cell);

public:
	void update(float dt) override;
};


#endif //PACMAN_H
