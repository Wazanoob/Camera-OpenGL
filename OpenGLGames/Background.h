#pragma once
#include "Actor.h"

class NoSpriteComponent;

class Background : public Actor
{
public:
	Background();

private:
	NoSpriteComponent* drawComponent;
};

