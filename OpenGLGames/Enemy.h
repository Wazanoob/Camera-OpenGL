#pragma once
#include "Actor.h"

class CircleCollisionComponent;

class Enemy : public Actor
{
public:
	Enemy();
	virtual ~Enemy();

	void updateActor(float dt) override;

	CircleCollisionComponent& getCircle() { return *circle; }

private:
	CircleCollisionComponent* circle;
};

