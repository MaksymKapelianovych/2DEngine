#include "component.h"
#include "Gui/widget.h"
#include <cassert>

template<typename T>
Widget *Component<T>::getOwner() const
{
    return owner_;
}

template<typename T>
Component<T>::Component(Widget* obj)
{
    owner_ = obj;
}

template<typename T>
Component<T>::~Component()
{
    //Component does not control owner`s life
}

template<typename T>
std::string Component<T>::type() const
{
    return "Component";
}

template <typename T>
T& Component<T>::create(Widget* obj)
{
    assert(obj != nullptr);
    return components_.template emplace_back(obj);
}
