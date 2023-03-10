#pragma once
#include "Actor.h"
class Sphere : public Actor
{
public:
	Sphere(bool canMoveP);

	bool canMove;
};

