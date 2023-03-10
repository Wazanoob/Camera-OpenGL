#pragma once
#include "Actor.h"

class NoSpriteComponent;
class AIComponent;
class InputComponent;

class PaddleBrick : public Actor
{
public:
	PaddleBrick(Vector2 positionP);

	void updateActor(float dt) override;
	float getWidth() { return width; }
	float getHeight() { return height; }

private:
	void limitMovementZone();

	float width;
	float height;

	NoSpriteComponent* drawComponent;
	AIComponent* opponentAIComponent;
	InputComponent* inputComponent;
};

