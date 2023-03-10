#pragma once
#include "Actor.h"

class CircleCollisionComponent;

class Laser : public Actor
{
public:
	Laser();

	void updateActor(float dt) override;

private:
	CircleCollisionComponent* collision;
	float deathTimer;
};

