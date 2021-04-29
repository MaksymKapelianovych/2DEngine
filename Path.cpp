//
// Created by zephyrus on 22.03.21.
//

#include "Path.h"

#include <stack>
#include <queue>
#include <chrono>
#include <iostream>

#include "Map.h"
#include "Cell.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Engine/game_object.h"

struct Node{
	Node* parent;
	std::weak_ptr<Cell> current;
	int cost;
	int priority;
	std::vector<Node*> children;
};

void deleteNode(Node* n){
	for(auto child: n->children){
		deleteNode(child);
	}

	delete n;
}

auto cmp = [](Node* lhs, Node* rhs){ return lhs->priority > rhs->priority; };

class AStar{
	std::shared_ptr<Map> map_;
	std::shared_ptr<Cell> start_;
	std::shared_ptr<Cell> target_;

	std::vector<std::weak_ptr<Cell>> visited;

	std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> priority_queue{cmp};
	std::vector<std::weak_ptr<Cell>> path;

public:
	AStar(const std::weak_ptr<Map>& map, const std::weak_ptr<Cell>& start, const std::weak_ptr<Cell>& target) : map_(map), start_(start), target_(target){
	}

	std::vector<std::weak_ptr<Cell>> find(){
		Node *head = new Node();
		head->current = start_;
		head->priority = 0;
		priority_queue.emplace(head);
		visited.push_back(head->current);

		while(!priority_queue.empty()){
			Node* current = priority_queue.top();
			priority_queue.pop();

			if(current->current.lock() == target_){
				Node* n = current;
				while(n->parent){
					path.emplace_back(n->current);
					n = n->parent;
				}
				deleteNode(n);
				return path;
			}

			auto neighbours = map_->getNeighbours(current->current);

			for(const auto& neighbour: neighbours)
			{
				if (std::find_if(visited.cbegin(), visited.cend(),
					[&neighbour](const std::weak_ptr<Cell>& c) { return neighbour.lock() == c.lock(); }) == visited.cend())
				{
					visited.push_back(neighbour);
					int new_cost = 1 + current->cost;
					int priority = manhattan_length(target_, neighbour.lock()) + new_cost;
					Node* temp = new Node();
					temp->current = neighbour;
					temp->cost = new_cost;
					temp->priority = priority;
					temp->parent = current;
					current->children.emplace_back(temp);
					priority_queue.push(temp);
				}
			}
		}
		return {};
	}

private:
	static int manhattan_length(const std::shared_ptr<Cell>& a, const std::shared_ptr<Cell>& b)
	{
		return abs(a->getColumn() - b->getColumn()) + abs(a->getRow() - b->getRow());
	}
};

std::weak_ptr<Map> Path::map_ = {};
std::weak_ptr<PacMan> Path::pacman_ = {};
std::weak_ptr<Ghost> Path::ghost_ = {};
std::weak_ptr<Cell> Path::food_ = {};
const int Path::maxTreeLength = 1;
int Path::currentTreeLength;

std::weak_ptr<Cell> Path::findPacman()
{
	auto res = calculatePacManMoves(pacman_.lock()->getOwner()->getParent().lock()->getComponent<Cell>(), ghost_.lock()->getOwner()->getParent().lock()->getComponent<Cell>()).first;
	currentTreeLength = 0;
	return res;
}
std::weak_ptr<Cell> Path::findGhost()
{
	auto res = calculateGhostMoves(pacman_.lock()->getOwner()->getParent().lock()->getComponent<Cell>(), ghost_.lock()->getOwner()->getParent().lock()->getComponent<Cell>()).first;
	currentTreeLength = 0;
	return res;
}
std::pair<std::weak_ptr<Cell>, int> Path::calculatePacManMoves(std::weak_ptr<Cell> pacman, std::weak_ptr<Cell> ghost)
{
	currentTreeLength++;
	if(currentTreeLength > maxTreeLength){
		return std::pair<std::weak_ptr<Cell>, int>{};
	}
	std::pair<std::weak_ptr<Cell>, int> max{};
	max.second = INT32_MIN;
	auto possibleMoves = map_.lock()->getNeighbours(pacman);
	for(auto nextPacman : possibleMoves){
		int cost = caclulatePacmanPrice(nextPacman, ghost);
		int nextCost = 0;
		if(currentTreeLength < maxTreeLength)
		{
			auto[cell, nextCost] = calculateGhostMoves(nextPacman, ghost);
		}
		if (max.second < cost + nextCost)
		{
			max.first = nextPacman;
			max.second = cost + nextCost;
		}
	}

	return max;
}
std::pair<std::weak_ptr<Cell>, int> Path::calculateGhostMoves(std::weak_ptr<Cell> pacman, std::weak_ptr<Cell> ghost)
{
	currentTreeLength++;
	if(currentTreeLength > maxTreeLength){
		return std::pair<std::weak_ptr<Cell>, int>{};
	}
	std::pair<std::weak_ptr<Cell>, int> min{};
	min.second = INT32_MAX;

	auto possibleMoves = map_.lock()->getNeighbours(ghost);
	for(auto nextGhost : possibleMoves){
		int cost = caclulateGhostPrice(pacman, nextGhost);
		auto [cell, nextCost] = calculatePacManMoves(pacman, nextGhost);
		if(min.second > cost + nextCost){
			min.first = nextGhost;
			min.second = cost + nextCost;
		}
	}

	return min;
}
int Path::caclulatePacmanPrice(std::weak_ptr<Cell> nextPacman, std::weak_ptr<Cell> ghost)
{
	int toFood = AStar(map_, nextPacman, food_).find().size();
	int toGhost = AStar(map_, nextPacman, ghost).find().size();
	return 1.5*toGhost-toFood;
}
int Path::caclulateGhostPrice(std::weak_ptr<Cell> pacman, std::weak_ptr<Cell> nextGhost)
{
	return AStar(map_, nextGhost, pacman).find().size();;
}
