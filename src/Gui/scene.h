#ifndef SCENE_H
#define SCENE_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include <memory>

#include "constants.h"
#include "camera.h"
#include "widget.h"

//Create Scene builder


class Scene
{
protected:
    glm::mat4 projection;
    std::unique_ptr<Camera> camera;


    GLuint m_width, m_height, m_x, m_y;
    Scene *parent;

    std::list<std::shared_ptr<Scene>> childs;
    //std::list<std::shared_ptr<Widget>> objects;
    //std::shared_ptr<Scene> activeScene;
    //std::shared_ptr<Widget> activeWidget;


    static bool    keys[1024];
    GLfloat lastX  =  m_width  / 2.0;
    GLfloat lastY  =  m_height / 2.0;

    Mouse mouseState = Mouse::NONE;
    bool enableDrag = false;


public:
    Scene(Scene* parent = nullptr);
    Scene( GLuint x, GLuint y, GLuint width, GLuint height,Scene* parent = nullptr);

    virtual ~Scene();


    void addChild(std::shared_ptr<Scene> child);
    void removeChild(std::shared_ptr<Scene> child);

    //void addObject(std::shared_ptr<Widget> obj);
    //void removeObject(std::shared_ptr<Widget> obj);

    virtual void draw();
    virtual void update(double deltaTime);
//    virtual bool key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//    virtual bool mouse_callback(double xpos, double ypos);
//    virtual bool scroll_callback(double xoffset, double yoffset)=0;
//    virtual bool mouseKey (int button, int action, int mode )=0;
//    virtual bool drag_drop(double xoffset, double yoffset)=0;
//    virtual void do_movement(double deltaTime)=0;

    //Getters & setters
    GLuint getWidth() const;
    void setWidth(const GLuint &value);

    GLuint getHeight() const;
    void setHeight(const GLuint &value);

    GLuint getX() const;
    void setX(const GLuint &value);

    GLuint getY() const;
    void setY(const GLuint &value);

    glm::vec2 getPos() const;
    void setPos(const glm::vec2& pos);
    void setPos(GLint x, GLint y);

    void setParent(Scene *p);
    Scene *getParent() const;

    glm::mat4 getView() const;

    glm::mat4 getProjection() const;
    void setProjection(const glm::mat4 &value);

    glm::vec3 getCameraPosition();

    glm::vec2 getWindowPos();

};

#endif // SCENE_H
