#include "window.h"

#include "scene.h"

Window::Window(GLFWwindow *window, GLuint width, GLuint height)
	: std::enable_shared_from_this<Window>(), window_(window), width_(width), height_(height)
{

}


void Window::init()
{
	scene_ = std::make_shared<Scene>(weak_from_this());
	panel_ = std::make_shared<Scene>(weak_from_this());
}


void Window::update(GLfloat deltaTime)
{
	scene_->update(deltaTime);
}

void Window::draw()
{
	// Clear the colorbuffer
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene_->draw();
	//panel_->draw();

	// Swap the screen buffers
	glfwSwapBuffers(window_);
}

GLuint Window::getWidth() const
{
    return width_;
}

void Window::setWidth(const GLuint &value)
{
	width_ = value;
}

GLuint Window::getHeight() const
{
    return height_;
}

void Window::setHeight(const GLuint &value)
{
	height_ = value;
}
std::weak_ptr<Scene> Window::getScene() const
{
	return scene_;
}
std::weak_ptr<Scene> Window::getPanel() const
{
	return panel_;
}
void Window::addToScene(const std::shared_ptr<GameObject>& object)
{
	scene_->addObject(object);
}
void Window::addToPanel(const std::shared_ptr<GameObject>& object)
{
	panel_->addObject(object);
}

