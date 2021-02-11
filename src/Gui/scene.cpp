#include "scene.h"

bool Scene::keys[1024];


Scene::Scene(Scene *parent):parent(parent)
{
    if(parent){
        setWidth(parent->getWidth());
        setHeight(parent->getHeight());
        setX(parent->getX());
        setY(parent->getY());
    }
}

Scene::Scene(GLuint x, GLuint y, GLuint width, GLuint height, Scene* parent):
    m_width(width), m_height(height), m_x(x), m_y(y), parent(parent)/*, activeScene(nullptr), activeWidget(nullptr)*/
{

}

Scene::~Scene()
{
}

GLuint Scene::getWidth() const
{
    return m_width;
}

void Scene::setWidth(const GLuint &value)
{
    m_width = value;
}

GLuint Scene::getHeight() const
{
    return m_height;
}

void Scene::setHeight(const GLuint &value)
{
    m_height = value;
}

GLuint Scene::getX() const
{
    return m_x;
}

void Scene::setX(const GLuint &value)
{
    m_x = value;
}

GLuint Scene::getY() const
{
    return m_y;
}

void Scene::setY(const GLuint &value)
{
    m_y = value;
}

glm::vec2 Scene::getPos() const
{
    return glm::vec2(m_x, m_y);
}

void Scene::setPos(const glm::vec2 &pos)
{
    m_x = pos.x;
    m_y = pos.y;
}

void Scene::setPos(GLint x, GLint y)
{
    m_x = x;
    m_y = y;
}

//void Scene::setParent(Scene *p)
//{
//    if(parent){
//        parent->removeChild(this);
//    }
//    parent = p;
//    parent->addChild(this);
//}

Scene *Scene::getParent() const
{
    return parent;
}

glm::mat4 Scene::getView() const
{
    return camera->getViewMatrix();
}

glm::mat4 Scene::getProjection() const
{
    return projection;
}

void Scene::setProjection(const glm::mat4 &value)
{
    projection = value;
}
//void Scene::addChild(Scene *child)
//{
//    childs.push_back(child);
//}

glm::vec3 Scene::getCameraPosition()
{
    return camera->position;
}

glm::vec2 Scene::getWindowPos()
{
    glm::vec2 pos(m_x, m_y);
    if(parent){
        glm::vec2 parentPos = parent->getWindowPos();
        pos += parentPos;
    }

    return pos;
}

//void Scene::removeChild(Scene *child)
//{
//    childs.remove(child);
//}

void Scene::draw()
{
    glm::vec2 pos = getWindowPos();
    glViewport(pos.x, pos.y, m_width, m_height);
    glEnable(GL_DEPTH_TEST);

    for(auto it = childs.begin(); it != childs.end(); ++it){
        (*it)->draw();
    }

//    for(auto it = objects.begin(); it != objects.end(); ++it){
//        (*it)->draw();
//    }
    glDisable(GL_DEPTH_TEST);
}

void Scene::update(double deltaTime)
{

}

//bool Scene::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
//{
//    if (key >= 0 && key < 1024)
//    {
//        if (action == GLFW_PRESS)
//            keys[key] = true;
//        else if (action == GLFW_RELEASE)
//            keys[key] = false;
//    }
//}

//bool Scene::mouse_callback(double xpos, double ypos)
//{
//    glm::vec2 pos = getWindowPos();
//    if(pos.x < xpos && xpos < pos.x + m_width && pos.y < ypos && ypos < pos.y + m_height){
//        for(auto it = childs.begin(); it != childs.end(); ++it){
//            if((*it)->mouse_callback(xpos, ypos)){
//                activeScene = (*it);
//                return true;
//            }
//        }
//        for(auto it = objects.begin(); it != objects.end(); ++it){
//            if((*it)->mouse_callback(xpos, ypos)){
//                activeWidget = (*it);
//                return true;
//            }
//        }
//        return true;
//    }
//    return false;
//}


