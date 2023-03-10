#pragma once
#include "Actor.h"

class CircleCollisionComponent;
class NoSpriteComponent;
class MoveComponent;
class Paddle;

class Ball : public Actor
{
public:
	Ball();

	void updateActor(float dt) override;

private:
	void checkForTile();
	void detectPaddleCollisions(Paddle* paddleP);
	void reverseSpeed(float diffX, float diffY, float paddleThicknessP, float centerOfBallP);
	void resetBall();

	CircleCollisionComponent* circle;
	NoSpriteComponent* drawComponent;
	MoveComponent* inputComponent;

	int playerScore;
	int opponentScore;
	float horizontalSpeed;
	float verticalSpeed;
};

