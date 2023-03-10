#include "Grid.h"
#include "Tile.h"
#include "Enemy.h"
#include "Tower.h"
#include <algorithm>

Grid::Grid() :
	Actor(),
	selectedTile(nullptr),
	nextEnemyTimer(0.0f)
{
	// 7 rows, 16 columns
	tiles.resize(NB_ROWS);
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i].resize(NB_COLS);
	}

	// Create tiles
	for (size_t i = 0; i < NB_ROWS; i++)
	{
		for (size_t j = 0; j < NB_COLS; j++)
		{
			tiles[i][j] = new Tile();
			tiles[i][j]->setPosition(Vector2(TILE_SIZE / 2.0f + j * TILE_SIZE, START_Y + i * TILE_SIZE));

			// Create obstacle in the middle of the grid
			if (i >= NB_ROWS / 2 - 1 && i <= NB_ROWS / 2 + 1 && j >= NB_COLS / 2 - 1 && j <= NB_COLS / 2 + 1)
			{
				tiles[i][j]->setTileState(Tile::TileState::Obstacle);
			}
			else
			{
				tiles[i][j]->setTileState(Tile::TileState::Default);
			}
		}
	}

	// Set start/end tiles
	getStartTile().setTileState(Tile::TileState::Start);
	getEndTile().setTileState(Tile::TileState::Base);

	// Fill adjacent tiles
	for (int i = 0; i < NB_ROWS; i++)
	{
		for (int j = 0; j < NB_COLS; j++)
		{
			if (i > 0)
			{
				tiles[i][j]->adjacentTile.push_back(tiles[i - 1][j]);
			}
			if (i < NB_ROWS - 1)
			{
				tiles[i][j]->adjacentTile.push_back(tiles[i + 1][j]);
			}
			if (j > 0)
			{
				tiles[i][j]->adjacentTile.push_back(tiles[i][j - 1]);
			}
			if (j < NB_COLS - 1)
			{
				tiles[i][j]->adjacentTile.push_back(tiles[i][j + 1]);
			}
		}
	}

	// Find path in reverse
	findPath(getEndTile(), getStartTile());
	updatePathTiles(getStartTile());
}

void Grid::updateActor(float dt)
{
	Actor::updateActor(dt);

	nextEnemyTimer -= dt;
	if (nextEnemyTimer <= 0.f)
	{
		new Enemy();
		nextEnemyTimer += TIME_BETWEEN_ENEMIES;
	}
}

void Grid::processClick(int x, int y)
{
	y -= static_cast<int>(START_Y - TILE_SIZE / 2);
	if (y >= 0)
	{
		x /= static_cast<int>(TILE_SIZE);
		y /= static_cast<int>(TILE_SIZE);
		if (x >= 0 && x < static_cast<int>(NB_COLS) && y >= 0 && y < static_cast<int>(NB_ROWS))
		{
			selectTile(y, x);
		}
	}
}

void Grid::buildTower()
{
	if (selectedTile && !selectedTile->isBlocked)
	{
		selectedTile->isBlocked = true;
		if (findPath(getEndTile(), getStartTile()))
		{
			Tower* t = new Tower();
			t->setPosition(selectedTile->getPosition());
		}
		else
		{
			selectedTile->isBlocked = false;
			findPath(getEndTile(), getStartTile());
		}

		updatePathTiles(getStartTile());
	}
}

bool Grid::findPath(Tile& start, const Tile& goal)
{
	for (size_t i = 0; i < NB_ROWS; i++)
	{
		for (size_t j = 0; j < NB_COLS; j++)
		{
			tiles[i][j]->g = 0.0f;
			tiles[i][j]->isOpenSet = false;
			tiles[i][j]->isClosedSet = false;
		}
	}

	vector<Tile*> openSet;
	Tile* current = &start;
	current->isClosedSet = true;

	do
	{
		// Add adjacent tiles to open set
		for (Tile* neighbours : current->adjacentTile)
		{
			if (neighbours->isBlocked)
			{
				continue;
			}

			// Only check a tile if it is not in the closed set
			if (!neighbours->isClosedSet)
			{
				if (!neighbours->isOpenSet)
				{
					// H is the distance between the neighbour and the goal
					// G is the cost of the tile
					// F is the cost + the distance
					neighbours->parent = current;
					neighbours->h = (neighbours->getPosition() - goal.getPosition()).length();
					neighbours->g = current->g + TILE_SIZE;
					neighbours->f = neighbours->g + neighbours->h;
					openSet.emplace_back(neighbours);
					neighbours->isOpenSet = true;
				}
				else
				{
					// Compute G cost if current become the parent	
					float newG = current->g + TILE_SIZE;
					if (newG < neighbours->g)
					{
						// Adopt this node
						neighbours->parent = current;
						neighbours->g = newG;

						// F change because g change
						neighbours->f = neighbours->g + neighbours->h;
					}
				}
			}
		}
		if (openSet.empty())
		{
			break;
		}

		// Find Lowest cost tile in open set
		auto iter = std::min_element(
			begin(openSet),
			end(openSet),
			[](Tile* a, Tile* b) {return a->f < b->f; });

		// Set the current and move from open to closed set
		current = *iter;
		openSet.erase(iter);
		current->isOpenSet = false;
		current->isClosedSet = true;
	} while (current != &goal);

	return (current == &goal);
}

Tile& Grid::getStartTile()
{
	return *tiles[3][0];
}

Tile& Grid::getEndTile()
{
	return *tiles[3][15];
}

void Grid::selectTile(size_t row, size_t col)
{
	if (selectedTile)
	{
		selectedTile->toggleSelect();
	}

	selectedTile = tiles[row][col];
	selectedTile->toggleSelect();
}

void Grid::updatePathTiles(const Tile& start)
{
	Tile* t = start.parent;
	while (t != &getEndTile())
	{
		t->setTileState(Tile::TileState::Path);
		t = t->parent;
	}
}
