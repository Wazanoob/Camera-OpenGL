#pragma once
#include "Actor.h"

const int TILE_WIDTH = 40;
const int TILE_HEIGHT = 40;

class SpriteComponent;

class TileRacing : public Actor
{
public:
	enum class TileType
	{
		Forest,
		Road,
		Wall,
		Start,
		End
	};

	TileRacing(Vector2 positionP, TileType tileTypeP);


private:
	SpriteComponent* spriteComponent;
	TileType tileType;
};

