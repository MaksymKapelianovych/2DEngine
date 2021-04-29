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
#include <memory>
#include <vector>

#include "Utils/constants.h"
//#include "window.h"
#include "RenderSystem/camera.h"

//Create Scene builder
class Window;
class GameObject;
class Drawable;

class Scene : public std::enable_shared_from_this<Scene>
{
private:
    //glm::mat4 projection;
    std::unique_ptr<Camera> camera;

    std::weak_ptr<Window> parent_;
	std::vector<std::shared_ptr<GameObject>> objects_;

public:
    Scene(std::weak_ptr<Window> parent);

    ~Scene();

    void update(GLfloat deltaTime);
    void draw();

	void addObject(const std::shared_ptr<GameObject>& object);

    [[nodiscard]] glm::mat4 getProjection() const;

	[[nodiscard]] glm::vec3 getCameraPosition();


};

#endif // SCENE_H
