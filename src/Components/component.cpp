#include "component.h"
#include "Gui/game_object.h"

std::shared_ptr<GameObject> Component::getOwner() const
{
	if(owner_.expired()){
		std::terminate(); // todo maybe change
	}
    return owner_.lock();
}

Component::Component(const std::shared_ptr<GameObject> &owner)
{
    owner_ = owner;
}

Component::~Component()
{
    //Component does not control owner`s life
}

std::string Component::type() const
{
    return "Component";
}

