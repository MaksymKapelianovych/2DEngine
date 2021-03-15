#include "scene.h"

#include <utility>

#include "game_object.h"
#include "Components/drawable.h"

bool Scene::keys[1024];


Scene::Scene(std::weak_ptr<Window> parent) : std::enable_shared_from_this<Scene>(), parent_(std::move(parent))
{

}

Scene::~Scene()
{
}

glm::mat4 Scene::getView() const
{
    return camera->getViewMatrix();
}

glm::mat4 Scene::getProjection() const
{
    return projection;
}

glm::vec3 Scene::getCameraPosition()
{
    return camera->position_;
}


void Scene::update(GLfloat deltaTime)
{
	for(auto& object : objects_){
		object->update(deltaTime);
	}
}
void Scene::draw()
{
	for(auto& object : objects_){
		if(auto drawable = object->getComponent<Drawable>()){
			drawable->draw();
		}
	}
}

void Scene::addObject(const std::shared_ptr<GameObject>& object)
{
	objects_.emplace_back(object);
	object->setScene(weak_from_this());
}
