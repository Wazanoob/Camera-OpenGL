#pragma once
#include "Actor.h"

class CircleCollisionComponent;
class NoSpriteComponent;
class MoveComponent;
class PaddleBrick;
class GridBrick;

class BallBrick :
    public Actor
{
public:
	BallBrick();

	void updateActor(float dt) override;

private:
	void checkForTile();
	void detectPaddleCollisions();
	void detectBricksCollisions();
	void reverseSpeed(float diffX, float diffY, float paddleThicknessP, float centerOfBallP);
	void resetBall();
	void speedUpBall(float amount);

	CircleCollisionComponent* circle;
	NoSpriteComponent* drawComponent;
	MoveComponent* inputComponent;
	GridBrick* gridBrick;

	float horizontalSpeed;
	float verticalSpeed;
};

