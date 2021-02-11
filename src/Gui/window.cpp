#include "window.h"

Window::Window(GLuint width, GLuint height): m_width(width), m_height(height)
{

}

void Window::update(double deltaTime)
{

}

void Window::draw(){
    glViewport(0, 0, m_width, m_height);
    glEnable(GL_DEPTH_TEST);

    for(auto it = childs.begin(); it != childs.end(); ++it){
        (*it)->draw();
    }

//    for(auto it = objects.begin(); it != objects.end(); ++it){
//        (*it)->draw();
//    }
    glDisable(GL_DEPTH_TEST);
}

GLuint Window::getWidth() const
{
    return m_width;
}

void Window::setWidth(const GLuint &value)
{
    m_width = value;
}

GLuint Window::getHeight() const
{
    return m_height;
}

void Window::setHeight(const GLuint &value)
{
    m_height = value;
}

//bool Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//    if(activeScene){
//        activeScene->key_callback(window, key, scancode, action, mode);
//    }
//    for(auto it = childs.begin(); it != childs.end(); ++it){
//        if((*it)->key_callback(window, key, scancode, action, mode)){
//            return true;
//        }
//    }
//    return false;
//}

//bool Window::mouse_callback(double xpos, double ypos)
//{
//    if(Scene::mouse_callback(xpos, ypos)){
//        return true;
//    }
//    return false;
//    for(auto it = childs.begin(); it != childs.end(); ++it){
//        if((*it)->mouse_callback(xpos, ypos)){
//            activeScene = (*it);
//            return true;
//        }
//    }
//    return false;
//}

//bool Window::scroll_callback(double xoffset, double yoffset)
//{
//    if(activeScene){
//        return activeScene->scroll_callback(xoffset, yoffset);
//    }
//    return false;
//    for(auto it = childs.begin(); it != childs.end(); ++it){
//        if((*it)->scroll_callback(xoffset, yoffset)){
//            return true;
//        }
//    }
//    return false;
//}

//bool Window::mouseKey(int button, int action, int mode)
//{
//    if(activeScene){
//        return activeScene->mouseKey(button, action, mode);
//    }
//    return false;
//    for(auto it = childs.begin(); it != childs.end(); ++it){
//        if((*it)->mouseKey(button, action, mode)){
//            return true;
//        }
//    }
//    return false;
//}

//bool Window::drag_drop(double xoffset, double yoffset)
//{
//    return false;
//}

//void Window::update(double deltaTime)
//{
//    if(activeScene){
//        activeScene->update(deltaTime);
//    }
//    for(auto it = childs.begin(); it != childs.end(); ++it){
//        (*it)->do_movement(deltaTime);
//    }
//}
