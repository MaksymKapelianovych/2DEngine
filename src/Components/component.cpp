#include "component.h"
#include "2DEngine/widget.h"
#include <assert.h>

Widget *Component::getOwner() const
{
    return owner_;
}

Component::Component(Widget* obj)
{
    assert(obj != nullptr);
    owner_ = obj;
}

Component::~Component()
{
    //Component does not control owner`s life
}

std::string Component::type() const
{
    return "Component";
}
