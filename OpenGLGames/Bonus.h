#pragma once
#include "Actor.h"

class NoSpriteComponent;

class Bonus : public Actor
{
public:
	Bonus(Vector2 positionP);

	void updateActor(float dt) override;


private:
	void detectPaddleCollisions();

	NoSpriteComponent* drawComponent;
};

