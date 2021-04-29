#ifndef WINDOW_H
#define WINDOW_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <vector>

class Scene;
class GameObject;

class Window : public std::enable_shared_from_this<Window>
{
public:
	//Window() = delete;
    Window(GLFWwindow *window, GLuint width = 800, GLuint height = 600);
	virtual ~Window() = default;
	void init();

    virtual void update(GLfloat deltaTime);
    void draw();

    //Getters & setters
    GLuint getWidth() const;
    void setWidth(const GLuint &value);

    GLuint getHeight() const;
    void setHeight(const GLuint &value);

    std::weak_ptr<Scene> getScene() const;
    std::weak_ptr<Scene> getPanel() const;

    void addToScene(const std::shared_ptr<GameObject>& object);
    void addToPanel(const std::shared_ptr<GameObject>& object);

private:
	GLFWwindow* window_;
    GLuint width_;
    GLuint height_;

    std::shared_ptr<Scene> scene_;
    std::shared_ptr<Scene> panel_;

//    GLfloat lastX  =  width_  / 2.0;
//    GLfloat lastY  =  height_ / 2.0;
};

#endif // WINDOW_H
