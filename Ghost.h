//
// Created by zephyrus on 28.03.21.
//

#ifndef GHOST_H
#define GHOST_H
#include <memory>
#include "Components/component.h"

class Cell;
class Ghost : public Component
{
	std::weak_ptr<Cell> cell_;
	std::vector<std::string> textures_;
	std::vector<std::weak_ptr<Cell>> path_;

public:
	Ghost(const std::weak_ptr<GameObject>& owner, std::weak_ptr<Cell> cell);

	void tryDfs(const std::weak_ptr<Cell>& target);


private:
	//void dfs(std::weak_ptr<Cell> cell);

public:
	void update(float dt) override;
};


#endif //GHOST_H
