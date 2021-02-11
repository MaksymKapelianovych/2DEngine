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
constexpr GLfloat YAW        = -90.0f;
constexpr GLfloat PITCH      =  0.0f;
constexpr GLfloat SPEED      =  3.0f;
constexpr GLfloat SENSITIVITY =  0.25f;
constexpr GLfloat ZOOM       =  45.0f;

class Camera
{
public:
    //Vectors
    glm::vec3 position, up, front, worldUp, right;
    //Euler angles
    GLfloat yaw, pitch;
    //Options
    GLfloat speed, sensitivity, zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           GLfloat yaw = YAW, GLfloat pitch = PITCH);
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

    glm::mat4 getViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(GLfloat yoffset);

private:
    void updateCameraVectors();
};

#endif //INC_2DENGINE_CAMERA_H
