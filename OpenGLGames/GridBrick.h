#pragma once
#include "Actor.h"
#include <vector>

class Bricks;

const int GRID_COLS = 16;
const int GRID_ROWS = 17;

class GridBrick : public Actor
{
public:
	GridBrick();
	~GridBrick();

	Bricks* getBricks(int i, int j) { return tiles[i][j]; }
	void hitBrick(int i, int j);

private:
	void AddBricks();
	void DrawBricks(int i, int j);
	void RemoveBrick(int i, int j);

	std::vector<std::vector<Bricks*>> tiles;
};

