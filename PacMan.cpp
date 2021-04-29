//
// Created by zephyrus on 20.03.21.
//

#include "PacMan.h"
#include "Engine/game_object.h"
#include "Map.h"
#include "Cell.h"
#include "Components/image.h"
#include "Components/sprite.h"
#include "Path.h"

#include <iostream>
#include <utility>
PacMan::PacMan(const std::weak_ptr<GameObject>& owner, std::weak_ptr<Cell> cell)
	: Component(owner), cell_(std::move(cell))
{

}
void PacMan::tryDfs(const std::weak_ptr<Cell>& target)
{
	auto map = owner_.lock()->getParent().lock()->getParent().lock()->getComponent<Map>();

	//path_ = Path::find(map, cell_, target);
}
void PacMan::update(float dt)
{

	if(Path::food_.expired()){
		auto cell = getOwner()->getParent().lock()->getComponent<Cell>();
		auto map = owner_.lock()->getParent().lock()->getParent().lock()->getComponent<Map>();
		if(auto food = map->getNearestFood(cell).lock()){
			Path::food_ = food;
		}else{
			return;
		}
	}
	static float time = 0;
	time += dt;
	if (time > 0.2)
	{
		if(auto nextCell = Path::findPacman().lock())
		{
			//std::cout << "Pacman moves " << nextCell->getRow() << " " << nextCell->getColumn() << "\n";
			auto owner = getOwner();
			auto cell = owner->getParent().lock();

			owner->getParent().lock()->getComponent<Cell>()->removeObject();
			auto map = owner_.lock()->getParent().lock()->getParent().lock()->getComponent<Map>();

			if (map->hasFood(nextCell->getRow(), nextCell->getColumn()))
			{
				map->eatFood(nextCell->getRow(), nextCell->getColumn());
			}
			else if (auto ghosts = map->getGhosts(); !ghosts.empty())
			{
				for (const auto& ghost : ghosts)
				{
					if (ghost.lock() == nextCell)
					{
						time = 0;
						return;
					}
				}
			}
			nextCell->setObject(owner);
			cell_ = nextCell;
			time = 0;
		}
	}
}
