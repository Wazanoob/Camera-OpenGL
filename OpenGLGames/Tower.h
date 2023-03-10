#pragma once
#include "Actor.h"

class MoveComponent;

class Tower : public Actor
{
public:
	Tower();

	void updateActor(float dt) override;

private:
	MoveComponent* move;
	float nextAttackTimer;

	const float ATTACK_TIME = 2.5f;
	const float ATTACK_RANGE = 100.0f;
};

