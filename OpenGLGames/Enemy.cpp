#include "Enemy.h"
#include "Game.h"
#include "Grid.h"
#include "Tile.h"
#include "AssetsManager.h"
#include "NavComponent.h"
#include "CircleCollisionComponent.h"
#include "SpriteComponent.h"
#include "Maths.h"
#include "Log.h"
#include <string>


Enemy::Enemy() : 
	Actor(), circle(nullptr)
{
	getGame().getEnemies().emplace_back(this);

	SpriteComponent* sc = new SpriteComponent(this, AssetsManager::getTexture("Airplane"));
	setPosition(getGame().getGrid().getStartTile().getPosition());
	
	NavComponent* nc = new NavComponent(this);
	nc->setForwardSpeed(150.0f);
	nc->startPath(getGame().getGrid().getStartTile());

	circle = new CircleCollisionComponent(this);
	circle->setRadius(25.0f);
}

Enemy::~Enemy()
{
	std::vector<Enemy*>& enemies = getGame().getEnemies();
	auto iter = std::find(begin(enemies), end(enemies), this);
	enemies.erase(iter);
}

void Enemy::updateActor(float dt)
{
	Actor::updateActor(dt);

	Vector2 dist = getPosition() - getGame().getGrid().getEndTile().getPosition();

	if (Maths::nearZero(dist.length(), 10.f))
	{
		setState(ActorState::Dead);
	}
}
