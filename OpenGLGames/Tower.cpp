#include "Tower.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AssetsManager.h"
#include "Maths.h"


Tower::Tower() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, AssetsManager::getTexture("Tower"), 200	);
	move = new MoveComponent(this);
	nextAttackTimer = ATTACK_TIME;
}

void Tower::updateActor(float dt)
{
	Actor::updateActor(dt);

	nextAttackTimer -= dt;
	if (nextAttackTimer <= 0.0f)
	{
		Enemy* e = getGame().getNearestEnemy(getPosition());
		if (e != nullptr)
		{
			Vector2 dir = e->getPosition() - getPosition();
			float dist = dir.length();

			if (dist < ATTACK_RANGE)
			{
				setRotation(Maths::atan2(-dir.y, dir.x));
				Bullet* b = new Bullet();
				b->setPosition(getPosition());
				b->setRotation(getRotation());
			}
		}
		nextAttackTimer += ATTACK_TIME;
	}
}
