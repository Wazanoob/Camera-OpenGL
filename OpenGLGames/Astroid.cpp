#include "Astroid.h"
#include "Random.h"
#include "Window.h"
#include "Maths.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "AssetsManager.h"
#include "CircleCollisionComponent.h"
#include "Game.h"

Astroid::Astroid()
{
	Vector2 randPos = Random::getVector(Vector2::zero, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
	setPosition(randPos);
	setRotation(Random::getFloatRange(0.0f, Maths::twoPi));

	// Having our own class for astroids allows to easily create their components structure
	SpriteComponent* sc = new SpriteComponent(this, AssetsManager::getTexture("Astroid"));
	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(150.f);

	collision = new CircleCollisionComponent(this);
	collision->setRadius(40.0f);

	getGame().addAstroid(this);
}

Astroid::~Astroid()
{
	getGame().removeAstroid(this);
}
