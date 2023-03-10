#pragma once
#include "Actor.h"

class NoSpriteComponent;

class BackgroundBrick :
    public Actor
{
public:
	BackgroundBrick();

private:
	NoSpriteComponent* drawComponent;
};

