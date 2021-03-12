#include "location.h"
#include "Gui/scene.h"

Location::Location(const std::shared_ptr<GameObject> &owner) : Component(owner), velocity_(0.f)
{
}

Location::~Location(){

}

void Location::moveTo(glm::vec2 newPosition)
{
    setPosition(newPosition);
}

void Location::moveBy(glm::vec2 offset)
{
    position_ += offset;
}

glm::vec2 Location::getScreenPos()
{
	if(owner_.expired()){
		std::terminate(); // todo maybe change
	}
    std::shared_ptr<Scene> scene = owner_.lock()->getScene();
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(position_, 1.f));

    matrixPos_ = glm::vec4(scene->getProjection() * scene->getView() * model * glm::vec4(0.f, 0.f, 0.f, 1.0f));

    glm::vec2 pos = glm::vec2(scene->getWidth()/2+scene->getWidth()/2*matrixPos_.x/matrixPos_.w,
                              scene->getHeight()/2-scene->getHeight()/2*matrixPos_.y/matrixPos_.w);
    pos += scene->getWindowPos();
    return pos;
}

void Location::update(GLfloat deltaTime)
{
    position_ += velocity_ * deltaTime;
}

glm::vec2 Location::getPosition() const
{
    return position_;
}

void Location::setPosition(const glm::vec2 &position)
{
    position_ = position;
}

glm::vec4 Location::getMatrixPos() const
{
    return matrixPos_;
}

glm::vec2 Location::getVelocity() const
{
    return velocity_;
}

void Location::setVelocity(const glm::vec2 &velocity)
{
    velocity_ = velocity;
}

