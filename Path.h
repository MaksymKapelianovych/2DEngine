//
// Created by zephyrus on 22.03.21.
//

#ifndef PATH_H
#define PATH_H
#include <memory>
#include <vector>

class Cell;
class Map;
class PacMan;
class Ghost;

class Path
{


public:
	static std::weak_ptr<Map> map_;
	static std::weak_ptr<PacMan> pacman_;
	static std::weak_ptr<Ghost> ghost_;
	static std::weak_ptr<Cell> food_;
	static const int maxTreeLength;
	static int currentTreeLength;

	static std::weak_ptr<Cell> findPacman();
	static std::weak_ptr<Cell> findGhost();

private:
	static std::pair<std::weak_ptr<Cell>, int> calculatePacManMoves(std::weak_ptr<Cell> nextPacman, std::weak_ptr<Cell> nextGhost);
	static std::pair<std::weak_ptr<Cell>, int> calculateGhostMoves(std::weak_ptr<Cell> nextPacman, std::weak_ptr<Cell> nextGhost);

	static int caclulatePacmanPrice(std::weak_ptr<Cell> nextPacman, std::weak_ptr<Cell> ghost);
	static int caclulateGhostPrice(std::weak_ptr<Cell> pacman, std::weak_ptr<Cell> nextGhost);
};


#endif //PATH_H
