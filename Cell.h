//
// Created by zephyrus on 16.03.21.
//

#ifndef CELL_H
#define CELL_H
#include <memory>
#include "Components/component.h"

class GameObject;

class Cell : public Component
{
	int row_, column_;
	static std::vector<std::string> textures_;

	std::weak_ptr<GameObject> object;
public:
	static void setTextures(std::vector<std::string> textures);

	Cell(std::weak_ptr<GameObject> owner, int row, int column);

	void setObject(std::weak_ptr<GameObject> obj);
	void removeObject();
	std::weak_ptr<GameObject> getObject() const;
	int getRow() const;
	int getColumn() const;

public:
	void init();
	void update(GLfloat dt) override;
};


#endif //CELL_H
