//
// Created by zephyrus on 04.02.21.
//

#ifndef INC_2DENGINE_CAMERA_H
#define INC_2DENGINE_CAMERA_H


// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement: char {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values

constexpr GLfloat SPEED      =  3.0f;
constexpr GLfloat SENSITIVITY =  0.25f;
constexpr GLfloat ZOOM       =  45.0f;

class Camera
{
public:
    //Vectors
    glm::vec3 position_;

    //Options
    GLfloat speed, sensitivity, zoom;

    Camera(glm::vec3 position = {0.f, 0.f, 30.f});
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ);

//    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
//    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
//    void ProcessMouseScroll(GLfloat yoffset);

};

#endif //INC_2DENGINE_CAMERA_H
