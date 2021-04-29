#ifndef INC_2DENGINE_MOUSECOLLIDER_H
#define INC_2DENGINE_MOUSECOLLIDER_H
#include "component.h"
#include <list>
#include <string>
#include "PhysicsSystem/PhysicsSystem.h"
#include "EventSystem/FunctionWrapper.h"
#include "EventSystem/Signal.h"
#include "component.h"

class MouseCollider : public Component
{

protected:
	using CollideSignal = Signal<>;
	CollideSignal collide;

public:
    MouseCollider(const std::weak_ptr<GameObject>& owner);
    ~MouseCollider();

    void update(GLfloat deltaTime) override;

	void addOnCollide(CollideSignal::hashable_function_t function);

private:
	void onLeftButtonClicked(double x, double y);
	void onRightButtonClicked(double x, double y);
};

#endif // INC_2DENGINE_MOUSECOLLIDER_H
