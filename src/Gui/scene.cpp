#include "scene.h"

#include <utility>

#include "game_object.h"
#include "Components/drawable.h"
#include "Engine/Engine.h"
#include "camera.h"

bool Scene::keys[1024];


Scene::Scene(std::weak_ptr<Window> parent)
		: std::enable_shared_from_this<Scene>(), parent_(std::move(parent))
{
	camera = std::make_unique<Camera>(0.f, 0.f, 1.f);
}

Scene::~Scene()
{
}

glm::mat4 Scene::getProjection() const
{
	int w = Engine::getWidth() / 2;
	int h = Engine::getHeight() / 2;
    return glm::ortho(camera->position_.x - w, camera->position_.x + w, camera->position_.y + h, camera->position_.y - h, -1.f, 1.f);
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
//	for(auto& object : objects_){
//		if(auto drawable = object->getComponent<Drawable>()){
//			drawable->draw();
//		}
//	}
	for(auto& object: objects_){
		object->draw();
	}
}

void Scene::addObject(const std::shared_ptr<GameObject>& object)
{
	objects_.emplace_back(object);
	object->setScene(weak_from_this());
}
