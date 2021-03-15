//
// Created by zephyrus on 04.02.21.
//

#include "camera.h"

Camera::Camera(const glm::vec3& position)
        : position_(position), up_({0.f, 1.f, 0.f}), front_({0.0f, 0.0f, -1.0f}), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM)
{
    this->position_ = position;
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ)
        : position_({posX, posY, posZ}), up_({0.f, 1.f, 0.f}), front_({0.0f, 0.0f, -1.0f}), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM)
{
}

Camera::Camera(glm::vec3&& position)
		: position_(position), up_({0.f, 1.f, 0.f}), front_({0.0f, 0.0f, -1.0f}), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM)
{

}


glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position_, position_ + front_, up_);
}
