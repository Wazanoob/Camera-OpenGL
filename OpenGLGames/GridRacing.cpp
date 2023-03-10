#include "GridRacing.h"
#include "TileRacing.h"

GridRacing::GridRacing()
{
	for (int i = 0; i < TILE_ROWS; i++)
	{
		for (int j = 0; j < TILE_COLS; j++)
		{
			switch (gridTiles[i][j])
			{
			case 0:
			{
				float xCoord = j * TILE_WIDTH;
				float yCoord = -i * TILE_HEIGHT;

				Vector2 position{ xCoord + TILE_WIDTH, yCoord + 800};
				TileRacing* tileRacing = new TileRacing(position, TileRacing::TileType::Road);
				break;
			}
			case 1:
			{
				float xCoord = j * TILE_WIDTH;
				float yCoord = -i * TILE_HEIGHT;

				Vector2 position{ xCoord + TILE_WIDTH, yCoord + 800};
				TileRacing* tileRacing = new TileRacing(position, TileRacing::TileType::Wall);
				break;
			}
			case 2:
			{
				float xCoord = j * TILE_WIDTH;
				float yCoord = -i * TILE_HEIGHT;

				Vector2 position{ xCoord + TILE_WIDTH, yCoord + 800};

				TileRacing* tileRacing = new TileRacing(position, TileRacing::TileType::Forest);
				break;
			}
			case 3:
			{
				float xCoord = j * TILE_WIDTH;
				float yCoord = -i * TILE_HEIGHT;

				Vector2 position{ xCoord + TILE_WIDTH, yCoord + 800};

				TileRacing* tileRacing = new TileRacing(position, TileRacing::TileType::Start);
				break;
			}
			case 4:
			{
				float xCoord = j * TILE_WIDTH;
				float yCoord = -i * TILE_HEIGHT;

				Vector2 position{ xCoord + TILE_WIDTH, yCoord + 800};

				TileRacing* tileRacing = new TileRacing(position, TileRacing::TileType::End);
				break;
			}
			}

		}
	}
}

GridRacing::~GridRacing()
{
}

Vector2 GridRacing::getStartPosition()
{
	for (int i = 0; i < TILE_COLS; i++)
	{
		for (int j = 0; j < TILE_ROWS; j++)
		{
			if (gridTiles[i][j] == 3)
			{
				float xCoord = j * TILE_WIDTH;
				float yCoord = -i * TILE_HEIGHT;

				Vector2 position{ xCoord + TILE_WIDTH, yCoord + 800 + TILE_HEIGHT};
				gridTiles[i][j] = TRACK_ROAD;

				return position;
			}
		}
	}
}
