#pragma once
#include "Actor.h"

class CircleCollisionComponent;
class SpriteComponent;
class InputComponent;
class PaddleBrick;
class GridRacing;

class CarRacing : public Actor
{
public:
	CarRacing(bool isPlayerOne);

	void updateActor(float dt) override;

private:
	int checkForTile(int xCoord, int yCoord);

	CircleCollisionComponent* circle;
	SpriteComponent* spriteComponent;
	InputComponent* inputComponent;
	GridRacing* gridRacing;

	bool playerOne;
	float horizontalSpeed;
	float verticalSpeed;
};

