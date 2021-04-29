//
// Created by zephyrus on 20.03.21.
//

#include "Wall.h"

#include <utility>
#include <Components/location.h>
#include "Cell.h"
#include "Engine/game_object.h"
#include "Components/image.h"
#include "Map.h"

std::vector<std::string> Wall::textures_ = {};


void Wall::setTextures(std::vector<std::string>&& textures)
{
	textures_ = std::move(textures);
}
Wall::Wall(const std::weak_ptr<GameObject>& owner, std::weak_ptr<Cell> cell)
	: Component(owner), cell_(std::move(cell))
{

}
void Wall::init()
{
	auto cell = cell_.lock();
	int row = cell->getRow();
	int column = cell->getColumn();


	auto image = owner_.lock()->getComponent<Image>();
	auto map = cell->getOwner()->getParent().lock()->getComponent<Map>();

	bool top_left = map->hasWall(row - 1, column - 1);
	bool top = map->hasWall(row - 1, column);
	bool top_right = map->hasWall(row - 1, column + 1);
	bool right = map->hasWall(row, column + 1);
	bool bottom_right = map->hasWall(row + 1, column + 1);
	bool bottom = map->hasWall(row + 1, column);
	bool bottom_left = map->hasWall(row + 1, column - 1);
	bool left = map->hasWall(row, column - 1);

	// none
//	if(!(top_left || top || top_right || right || bottom_right || bottom || bottom_left || left)){
//		image->setTexture(textures_[0].c_str());
//	}else
	/*if (top && right && bottom && left)
	{
		image->setTexture(textures_[6].c_str());
	}
	else */
	auto location = owner_.lock()->getComponent<Location>();
	if ((top && bottom && right) || (right && left && bottom) ||
		(bottom && top && left) || (left && right && top))
	{
		image->setTexture(textures_[4].c_str());
		if(top && bottom && right){
			location->rotate(glm::radians(90.f));
		}else if(right && left && bottom){
			location->rotate(glm::radians(180.f));
		}else if(bottom && top && left){
			location->rotate(glm::radians(270.f));
		}
	}
	else if ((top && right) || (right && bottom) || (bottom && left) || (left && top))
	{
		image->setTexture(textures_[3].c_str());
		if(top && right){
			location->rotate(glm::radians(180.f));
		}else if(right && bottom){
			location->rotate(glm::radians(270.f));
		}else if(left && top){
			location->rotate(glm::radians(90.f));
		}
	}
	else if ((top && bottom) || (right && left))
	{
		image->setTexture(textures_[2].c_str());
		if(right && left){
			location->rotate(glm::radians(90.f));
		}
	}
	else if (top || right || bottom || left)
	{
		image->setTexture(textures_[1].c_str());
		if(right){
			location->rotate(glm::radians(90.f));
		}else if(bottom){
			location->rotate(glm::radians(180.f));
		}else if(left){
			location->rotate(glm::radians(270.f));
		}
	}
	else
	{
		image->setTexture(textures_[0].c_str());
	}
	image->setWidth(24);
	image->setHeight(24);
}
void Wall::update(float dt)
{

}
