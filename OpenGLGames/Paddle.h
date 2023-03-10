#pragma once
#include "Actor.h"

class NoSpriteComponent;
class AIComponent;
class InputComponent;

class Paddle : public Actor
{
public:
	enum class PaddleController
	{
		Player,
		Opponent
	};

	Paddle(Vector2 positionP, PaddleController controllerP);

	void updateActor(float dt) override;
	float getWidth() { return width; }
	float getHeight() { return height; }

private:
	void limitMovementZone();

	float width;
	float height;

	PaddleController controller;
	NoSpriteComponent* drawComponent;
	AIComponent* opponentAIComponent;
	InputComponent* inputComponent;
};

