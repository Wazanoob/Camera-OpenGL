#include "GridBrick.h"
#include "BallBrick.h"
#include "Bricks.h"
#include "NoSpriteComponent.h"
#include "CircleCollisionComponent.h"
#include "MoveComponent.h"
#include "Random.h"
#include "Bonus.h"

GridBrick::GridBrick()
{
	// 14 rows, 10 columns
	tiles.resize(GRID_COLS);
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i].resize(GRID_ROWS);
	}

	// Create the wall
	AddBricks();
}

GridBrick::~GridBrick()
{
	tiles.clear();
}

void GridBrick::hitBrick(int i, int j)
{
	switch (tiles[i][j]->getType())
	{
	case Bricks::BrickType::Unbreakble:
		return;
	case Bricks::BrickType::Bonus:
	{
		//Drop MultiBall or expend paddle
		Vector2 pos = tiles[i][j]->getPosition();
		Bonus* drawComponent = new Bonus(pos);
		RemoveBrick(i, j);
		break;
	}
	case Bricks::BrickType::Default:
	{
		RemoveBrick(i, j);
		break;
	}
	case Bricks::BrickType::HardBrick:
		tiles[i][j]->setType();
		break;
	}
}

void GridBrick::AddBricks()
{
	for (size_t i = 0; i < GRID_COLS; i++)
	{
		for (size_t j = 0; j < GRID_ROWS; j++)
		{
			DrawBricks(i, j);
		}
	}
}

void GridBrick::DrawBricks(int i, int j)
{
	if (j == 2)
	{
		if (i == 4 || i == 12)
		{
			float xCoord = i * BRICK_WIDTH;
			float yCoord = j * BRICK_HEIGHT;

			Vector2 position{ xCoord, yCoord };

			tiles[i][j] = new Bricks(position, Bricks::BrickType::Default);
		}
	}

	if (j == 3)
	{
		if (i == 5 || i == 11)
		{
			float xCoord = i * BRICK_WIDTH;
			float yCoord = j * BRICK_HEIGHT;

			Vector2 position{ xCoord, yCoord };

			tiles[i][j] = new Bricks(position, Bricks::BrickType::Default);
		}
	}

	if (j == 4)
	{
		if (i > 3 && i < 13)
		{
			float xCoord = i * BRICK_WIDTH;
			float yCoord = j * BRICK_HEIGHT;

			Vector2 position{ xCoord, yCoord };

			tiles[i][j] = new Bricks(position, Bricks::BrickType::Default);
		}
	}

	if (j == 5)
	{
		if (i > 2 && i < 14)
		{
			float xCoord = i * BRICK_WIDTH;
			float yCoord = j * BRICK_HEIGHT;

			Vector2 position{ xCoord, yCoord };

			tiles[i][j] = new Bricks(position, Bricks::BrickType::Default);
		}
	}

	if (j == 6)
	{
		if (i > 1 && i < 15)
		{
			if (i == 6 || i == 10)
			{
				float xCoord = i * BRICK_WIDTH;
				float yCoord = j * BRICK_HEIGHT;

				Vector2 position{ xCoord, yCoord };

				tiles[i][j] = new Bricks(position, Bricks::BrickType::Bonus);
			}
			else
			{
				float xCoord = i * BRICK_WIDTH;
				float yCoord = j * BRICK_HEIGHT;

				Vector2 position{ xCoord, yCoord };

				tiles[i][j] = new Bricks(position, Bricks::BrickType::Default);
			}
		}
	}

	if (j == 7 || j == 8 || j == 9)
	{
		if ((i > 3 && i < 13))
		{
			float xCoord = i * BRICK_WIDTH;
			float yCoord = j * BRICK_HEIGHT;

			Vector2 position{ xCoord, yCoord };

			tiles[i][j] = new Bricks(position, Bricks::BrickType::Default);
		}

		if (i == 2 || i == 14)
		{
			float xCoord = i * BRICK_WIDTH;
			float yCoord = j * BRICK_HEIGHT;

			Vector2 position{ xCoord, yCoord };

			tiles[i][j] = new Bricks(position, Bricks::BrickType::HardBrick);
		}
	}

	if (j == 10)
	{
		if (i > 3 && i < 13)
		{
			float xCoord = i * BRICK_WIDTH;
			float yCoord = j * BRICK_HEIGHT;

			Vector2 position{ xCoord, yCoord };

			tiles[i][j] = new Bricks(position, Bricks::BrickType::Default);
		}
	}

	if (j == 11)
	{
		if (i == 4 || i == 12)
		{
			float xCoord = i * BRICK_WIDTH;
			float yCoord = j * BRICK_HEIGHT;

			Vector2 position{ xCoord, yCoord };

			tiles[i][j] = new Bricks(position, Bricks::BrickType::Default);
		}
	}

	if (j == 12)
	{
		if ((i > 4 && i < 7) || i > 9 && i < 12)
		{
			float xCoord = i * BRICK_WIDTH;
			float yCoord = j * BRICK_HEIGHT;

			Vector2 position{ xCoord, yCoord };

			tiles[i][j] = new Bricks(position, Bricks::BrickType::Default);
		}
	}

	if (j == 16)
	{
		if (i > 3 && i < 13)
		{
			float xCoord = i * BRICK_WIDTH;
			float yCoord = j * BRICK_HEIGHT;

			Vector2 position{ xCoord, yCoord };

			tiles[i][j] = new Bricks(position, Bricks::BrickType::Unbreakble);
		}
	}
}

void GridBrick::RemoveBrick(int i, int j)
{
	tiles[i][j]->setState(ActorState::Dead);
	tiles[i][j] = nullptr;
}
