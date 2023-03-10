#pragma once
#include "Actor.h"

class NoSpriteComponent;

const float BRICK_WIDTH = 50.f;
const float BRICK_HEIGHT = 25.f;
const float GAP_BETWEEN_BRICKS = 2.f;

class Bricks : public Actor
{
public:
	enum class BrickType
	{
		Default,
		HardBrick,
		Unbreakble,
		Bonus
	};

    Bricks(Vector2 positionP, BrickType typeP);

	BrickType getType() { return brickType; }
	void setType();
    void updateActor(float dt) override;

private:
    NoSpriteComponent* drawComponent;
	BrickType brickType;
};

