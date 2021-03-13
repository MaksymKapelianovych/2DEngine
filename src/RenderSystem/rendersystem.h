#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


#include <vector>
#include <memory>
#include "Components/drawable.h"

class GLFWwindow;
class RenderSystem
{
	static GLFWwindow *window_;
	static std::vector<std::weak_ptr<Drawable>> sprites_;
public:
    //explicit RenderSystem(GLFWwindow*);

    static void init(GLFWwindow*);
    static void draw();

    static void removeExpired();
    static void addDrawable(const std::weak_ptr<Drawable> &sprite);
};

#endif // RENDERSYSTEM_H
