#include "Laser.h"
#include "CircleCollisionComponent.h"
#include"SpriteComponent.h"
#include "MoveComponent.h"
#include "AssetsManager.h"
#include"Game.h"
#include"Astroid.h"

Laser::Laser() :
	Actor(),
	deathTimer(1.0f),
	collision(nullptr)
{
	SpriteComponent* sc = new SpriteComponent(this, AssetsManager::getTexture("Laser"));
	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(800.0f);
	collision = new CircleCollisionComponent(this);
	collision->setRadius(11.0f);
}

void Laser::updateActor(float dt)
{
	deathTimer -= dt;
	if (deathTimer <= 0.0f)
	{
		setState(Actor::ActorState::Dead);
	}
	else
	{
		auto astroids = getGame().getAstroids();
		for (Astroid* astroid : astroids)
		{
			if (Intersect(*collision, astroid->getCollision()))
			{
				setState(ActorState::Dead);
				astroid->setState(ActorState::Dead);
				break;
			}
		}
	}
}
