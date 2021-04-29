//
// Created by zephyrus on 04.02.21.
//

#include "camera.h"

Camera::Camera(glm::vec3 position)
        : position_(position), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM)
{
    this->position_ = position;
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ)
        : position_({posX, posY, posZ}), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM)
{
}
