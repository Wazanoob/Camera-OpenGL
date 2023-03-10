#pragma once
#include "Actor.h"

class CircleCollisionComponent;

class Astroid : public Actor
{
public:
	Astroid();
	~Astroid();

	CircleCollisionComponent& getCollision() { return *collision; }

private:
	CircleCollisionComponent* collision;
};

