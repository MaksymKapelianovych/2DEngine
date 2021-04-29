//
// Created by zephyrus on 28.03.21.
//

#include "Food.h"

#include <utility>

#include "Engine/game_object.h"
#include "Cell.h"
#include "Components/image.h"

std::string Food::texture_ = "";

void Food::setTexture(std::string&& texture)
{
	texture_ = std::move(texture);
}
Food::Food(const std::weak_ptr<GameObject>& owner, std::weak_ptr<Cell> cell)
	: Component(owner), cell_(std::move(cell))
{

}
void Food::init()
{
	auto image = owner_.lock()->getComponent<Image>();
	image->setTexture(texture_.c_str());
	image->setWidth(24);
	image->setHeight(24);
}
void Food::update(float dt)
{

}
