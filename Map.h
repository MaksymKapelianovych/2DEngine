//
// Created by zephyrus on 16.03.21.
//

#ifndef MAP_H
#define MAP_H
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>
#include "Components/component.h"
#include <unordered_map>

class GameObject;
class Cell;

class Map : public Component
{
	int score_ = 0;
	std::vector<std::vector<std::weak_ptr<Cell>>> map_;

	//std::unordered_map<std::weak_ptr<Cell>, std::weak_ptr<Cell>> path_;
public:
	Map(const std::weak_ptr<GameObject>& owner);
	void loadMap(const std::string& level, int levelWidthCount, int levelHeightCount);
	bool hasWall(int row, int column) const;
	bool hasFood(int row, int column) const;
	void eatFood(int row, int column);
	std::weak_ptr<Cell> getNearestFood(int row, int column) const;
	std::weak_ptr<Cell> getNearestFood(const std::weak_ptr<Cell> &start) const;
	std::weak_ptr<Cell> getPacMan() const;
	std::vector<std::weak_ptr<Cell>> getGhosts() const;


	std::vector<std::weak_ptr<Cell>> getNeighbours(std::weak_ptr<Cell> cell) const;

public:
	void update(GLfloat deltaTime) override;
};


#endif //MAP_H
