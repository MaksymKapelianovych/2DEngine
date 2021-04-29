//
// Created by zephyrus on 16.03.21.
//

#include "Map.h"
#include <memory>
#include <iostream>
#include "Engine/game_object.h"
#include "Components/location.h"
#include "Components/image.h"
#include "Cell.h"
#include "Food.h"
#include "Wall.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Path.h"
#include "PlayerMove.h"
#include "Components/BoxCollider.h"
#include "PhysicsSystem/PhysicsSystem.h"

Map::Map(const std::weak_ptr<GameObject>& owner)
	: Component(owner)
{

}
void Map::loadMap(const std::string& level, int levelWidthCount, int levelHeightCount)
{
//	map_.resize(levelHeightCount);
//	for(auto v: map_){
//		v.resize(levelWidthCount);
//	}

	int slideX, slideY, screenW = 800, screenH = 800, wallW = 40, wallH = 40;

	wallW = 24;
	wallH = 24;


	std::vector<std::string> textures{8};
	textures[0] = "../resources/textures/circle.png";
	textures[1] = "../resources/textures/up.png";
	textures[2] = "../resources/textures/up_down.png";
	textures[3] = "../resources/textures/left_down.png";
	textures[4] = "../resources/textures/left_up_right.png";
//	textures[5] = "../resources/textures/PU_1.png";
//	textures[6] = "../resources/textures/PU_2.png";
//	textures[7] = "../resources/textures/PU_3.png";

	Wall::setTextures(std::move(textures));
	Food::setTexture("../resources/textures/food.png");

	slideX = (- levelWidthCount * wallW) / 2;
	slideY = (- levelHeightCount * wallH) / 2;

	std::shared_ptr<Cell> t;
	std::weak_ptr<PacMan> p;
	std::weak_ptr<Ghost> g;

	//levelWidth = wallW * levelWidthCount;
	//levelHeight = wallH * levelHeightCount;

	for(int row = 0; row < levelHeightCount; ++row){
		map_.emplace_back(std::vector<std::weak_ptr<Cell>>());
		for(int column = 0; column < levelWidthCount; ++column){
			auto o = GameObject::create(owner_, glm::vec2{slideX + (wallW) * column + wallW / 2, slideY + (wallH) * row + wallH / 2});
			auto cell = o->addComponent<Cell>(row, column);

			switch (level[row * levelWidthCount + column])
			{
			case 'b':
			{
				auto wall = GameObject::create(o, glm::vec2{ 0, 0 });
				auto image = wall->addComponent<Image>();
				wall->addComponent<Wall>(cell);

				cell->setObject(wall);
				o->addChild(wall);
			}
				break;
			case 'p':
			{
				auto pacman = GameObject::create(o, glm::vec2{0, 0});
				auto image = pacman->addComponent<Image>();
				image->setTexture("../resources/textures/pacman2.png");
				image->setWidth(wallW);
				image->setHeight(wallH);
				p = pacman->addComponent<PacMan>(cell);

				cell->setObject(pacman);
				o->addChild(pacman);
				break;
			}
			case 'g':
			{
				auto ghost = GameObject::create(o, glm::vec2{0, 0});
				auto image = ghost->addComponent<Image>();
				image->setTexture("../resources/textures/ghost2.png");
				image->setWidth(wallW);
				image->setHeight(wallH);
				g = ghost->addComponent<Ghost>(cell);

				cell->setObject(ghost);
				o->addChild(ghost);
				break;
			}
			case 't':
			{
				auto target = GameObject::create(o, glm::vec2{ 0, 0 });
				auto image = target->addComponent<Image>();
				target->addComponent<Food>(cell);

				cell->setObject(target);
				t = cell;
				o->addChild(target);
			}
			default:
				break;
			}

			map_[row].emplace_back(cell);
			owner_.lock()->addChild(o);
		}
	}

	for(auto& row: map_){
		for(auto& column: row){
			if(auto c = column.lock()){
				c->init();
			}
		}
	}

	Path::ghost_ = g;
	Path::pacman_ = p;
	Path::map_ = getOwner()->getComponent<Map>();

	//pacman->getComponent<PacMan>()->tryDfs(t);

}
void Map::update(GLfloat deltaTime)
{

}
bool Map::hasWall(int row, int column) const
{
	if(row < 0 || row > map_.size() - 1 || column < 0 || column > map_[0].size() - 1){
		return false;
	}

	if(auto s = map_[row][column].lock()->getObject().lock())
	{
		if (auto wall = s->getComponent<Wall>())
		{
			return true;
		}
	}
	return false;
}
std::vector<std::weak_ptr<Cell>> Map::getNeighbours(std::weak_ptr<Cell> cell) const
{
	auto c = cell.lock();
	std::vector<std::weak_ptr<Cell>> result;
	if(c->getRow() - 1 >= 0 && !hasWall(c->getRow() - 1, c->getColumn())){
		result.push_back(map_[c->getRow() - 1][c->getColumn()]);
	}
	if(c->getColumn() + 1 <= map_[0].size() - 1 && !hasWall(c->getRow(), c->getColumn() + 1)){
		result.push_back(map_[c->getRow()][c->getColumn() + 1]);
	}
	if(c->getRow() + 1 <= map_.size() - 1 && !hasWall(c->getRow() + 1, c->getColumn())){
		result.push_back(map_[c->getRow() + 1][c->getColumn()]);
	}
	if(c->getColumn() - 1 >= 0 && !hasWall(c->getRow(), c->getColumn() - 1)){
		result.push_back(map_[c->getRow()][c->getColumn() - 1]);
	}


	return result;
}
bool Map::hasFood(int row, int column) const
{
	if(row < 0 || row > map_.size() - 1 || column < 0 || column > map_[0].size() - 1){
		return false;
	}

	if(auto s = map_[row][column].lock()->getObject().lock())
	{
		if (auto food = s->getComponent<Food>())
		{
			return true;
		}
	}
	return false;
}
void Map::eatFood(int row, int column)
{
	Path::food_ = {};
	std::cout << "Score: " << ++score_ << std::endl;
}
std::weak_ptr<Cell> Map::getNearestFood(int row, int column) const
{
	int minDistance = INT32_MAX;
	std::weak_ptr<Cell> cell;

	for(auto& i: map_){
		for(auto& j: i)
		{
			if (auto c = j.lock(); auto foodOwner = c->getObject().lock())
			{
				if (auto food = foodOwner->getComponent<Food>())
				{
					int temp = glm::distance(glm::vec2{ row, column }, glm::vec2{ c->getRow(), c->getColumn() });
					if (minDistance > temp)
					{
						minDistance = temp;
						cell = c;
					}
				}
			}
		}
	}

	return cell;
}
std::weak_ptr<Cell> Map::getNearestFood(const std::weak_ptr<Cell>& start) const
{
	if(start.expired())
	{
		return std::weak_ptr<Cell>();
	}
	auto cell = start.lock();
	return getNearestFood(cell->getRow(), cell->getColumn());
}
std::weak_ptr<Cell> Map::getPacMan() const
{
	for(auto& row: map_){
		for(auto& column: row){
			if (auto cell = column.lock(); auto pacmanOwner = cell->getObject().lock())
			{
				if (auto pacman = pacmanOwner->getComponent<PacMan>())
				{
					return cell;
				}
			}
		}
	}

	return std::weak_ptr<Cell>();
}
std::vector<std::weak_ptr<Cell>> Map::getGhosts() const
{
	std::vector<std::weak_ptr<Cell>> result{0};
	for(auto& row: map_){
		for(auto& column: row){
			if (auto cell = column.lock(); auto ghostOwner = cell->getObject().lock())
			{
				if (auto ghost = ghostOwner->getComponent<Ghost>())
				{
					result.emplace_back(cell);
				}
			}
		}
	}

	return result;
}



