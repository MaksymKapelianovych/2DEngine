#include <algorithm>

#include "rendersystem.h"

GLFWwindow *RenderSystem::window_ = nullptr;
std::vector<std::weak_ptr<Drawable>> RenderSystem::sprites_ = {};

void RenderSystem::init(GLFWwindow* window)
{
	RenderSystem::window_ = window;
}

void RenderSystem::draw()
{
	removeExpired();

	// Clear the colorbuffer
	glClearColor(.8f, .2f, .2f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto& s : sprites_){
		auto sprite = s.lock();
		sprite->draw();
	}

	// Swap the screen buffers
	glfwSwapBuffers(window_);
}
void RenderSystem::removeExpired()
{
	auto it = std::remove_if(sprites_.begin(), sprites_.end(), [](auto&& obj){ return obj.expired();});
	sprites_.erase(it, sprites_.end());
}
void RenderSystem::addDrawable(const std::weak_ptr<Drawable>& sprite)
{
	sprites_.emplace_back(sprite);
}

