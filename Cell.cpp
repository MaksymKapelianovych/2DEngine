//
// Created by zephyrus on 16.03.21.
//

#include "Cell.h"

#include <utility>

#include "Engine/game_object.h"
#include "Map.h"
#include "Components/image.h"
#include "Wall.h"
#include "Food.h"

std::vector<std::string> Cell::textures_ = {};

void Cell::setTextures(std::vector<std::string> textures)
{
	textures_ = std::move(textures);
}

void Cell::update(GLfloat dt)
{

}
Cell::Cell(std::weak_ptr<GameObject> owner, int row, int column) : Component(owner), row_(row), column_(column)
{

}
void Cell::init()
{
	if(auto o = getObject().lock()){
	    if(auto wall = o->getComponent<Wall>())
		{
			wall->init();
		}else if(auto food = o->getComponent<Food>())
		{
			food->init();
		}
	}
}

int Cell::getRow() const
{
	return row_;
}
int Cell::getColumn() const
{
	return column_;
}
void Cell::setObject(std::weak_ptr<GameObject> obj)
{
	removeObject();
	object = obj;
	getOwner()->addChild(object.lock());
}
void Cell::removeObject()
{
	if(!getObject().expired()){
		getOwner()->removeChild(getObject().lock());
	}
	object.reset();
}
std::weak_ptr<GameObject> Cell::getObject() const
{
	return object;
}
