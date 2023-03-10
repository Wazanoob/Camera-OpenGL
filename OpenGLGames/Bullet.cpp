#include "Bullet.h"
#include "SpriteComponent.h"
#include "CircleCollisionComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Enemy.h"
#include "AssetsManager.h"

Bullet::Bullet() : lifetime(1.0f)
{
	SpriteComponent* sc = new SpriteComponent(this, AssetsManager::getTexture("Projectile"));

	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(400.0f);

	circle = new CircleCollisionComponent(this);
	circle->setRadius(10.0f);

}

void Bullet::updateActor(float dt)
{
	Actor::updateActor(dt);

	// Once again, not opti We check if the bullet collide with any enemy on the level
	for (Enemy* e : getGame().getEnemies())
	{
		if (Intersect(*circle, e->getCircle()))
		{
			e->setState(ActorState::Dead);
			setState(ActorState::Dead);
		}
	}

	lifetime -= dt;
	if (lifetime <= 0.f)
	{
		setState(ActorState::Dead);
	}
}
