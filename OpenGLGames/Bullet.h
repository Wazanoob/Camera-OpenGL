#pragma once
#include "Actor.h"

class CircleCollisionComponent;

class Bullet : public Actor
{
public:
	Bullet();
	
	void updateActor(float dt) override;

private:
	CircleCollisionComponent* circle;
	float lifetime;
};

