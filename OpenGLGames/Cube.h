#pragma once
#include "Actor.h"
class Cube : public Actor
{
public:
	Cube(bool canMoveP);

	void setTarget(Actor* targetP);
	void setSpeed(float speedP) { speed = speedP; }

	void updateActor(float deltaTime) override;

private:
	bool canMove;
	Actor* target;
	float speed = 0.01f;
};

