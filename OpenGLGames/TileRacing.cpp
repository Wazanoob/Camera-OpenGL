#include "TileRacing.h"
#include "AssetsManager.h"
#include "SpriteComponent.h"

TileRacing::TileRacing(Vector2 positionP, TileType tileTypeP) :
	Actor(),
	spriteComponent(nullptr),
	tileType(tileTypeP)
{
	switch (tileType)
	{
	case TileType::Forest:
		spriteComponent = new SpriteComponent(this, AssetsManager::getTexture("Forest"));
		break;
	case TileType::Road:
		spriteComponent = new SpriteComponent(this, AssetsManager::getTexture("Road"));
		break;
	case TileType::Start:
		spriteComponent = new SpriteComponent(this, AssetsManager::getTexture("Road"));
		break;
	case TileType::Wall:
		spriteComponent = new SpriteComponent(this, AssetsManager::getTexture("Wall"));
		break;
	case TileType::End:
		spriteComponent = new SpriteComponent(this, AssetsManager::getTexture("Start"));
		break;
	}

	setPosition(positionP);
}
