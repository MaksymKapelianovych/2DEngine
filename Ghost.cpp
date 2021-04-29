//
// Created by zephyrus on 28.03.21.
//

#include <iostream>
#include "Ghost.h"
#include "Engine/game_object.h"
#include "Map.h"
#include "Cell.h"
#include "Components/image.h"
#include "Components/sprite.h"
#include "Path.h"

Ghost::Ghost(const std::weak_ptr<GameObject>& owner, std::weak_ptr<Cell> cell)
	: Component(owner), cell_(std::move(cell))
{

}
void Ghost::tryDfs(const std::weak_ptr<Cell>& target)
{
	auto map = owner_.lock()->getParent().lock()->getParent().lock()->getComponent<Map>();

}
void Ghost::update(float dt)
{
	if(Path::food_.expired()){
		auto cell = getOwner()->getParent().lock()->getComponent<Cell>();
		auto map = owner_.lock()->getParent().lock()->getParent().lock()->getComponent<Map>();
		if(auto food = map->getNearestFood(cell).lock()){
		}else{
			return;
		}
	}
		static float time = 0;
		time += dt;
		if (time > 0.2)
		{
			if (auto nextCell = Path::findGhost().lock())
			{
				auto owner = getOwner();
				owner->getParent().lock()->getComponent<Cell>()->removeObject();


				auto map = owner_.lock()->getParent().lock()->getParent().lock()->getComponent<Map>();

				if (map->getPacMan().lock() == nextCell)
				{
					std::cout << "Pacman is eaten\n";
				}
				nextCell->setObject(owner);
				cell_ = nextCell;
				time = 0;

			}
		}

}
