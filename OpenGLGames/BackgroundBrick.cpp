#include "BackgroundBrick.h"
#include "NoSpriteComponent.h"
#include "SpriteComponent.h"
#include "AssetsManager.h"
#include "Game.h"

BackgroundBrick::BackgroundBrick() :
	Actor(),
	drawComponent(nullptr)
{
	Actor* background = new Actor();
	Vector2 backgroundPosition{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	background->setPosition(backgroundPosition);
	SpriteComponent* sc = new SpriteComponent(background, AssetsManager::getTexture("PongBackground"));


	Actor* backgroundStars = new Actor();
	Vector2 backgroundStarsPosition{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	backgroundStars->setPosition(backgroundStarsPosition);
	SpriteComponent* sc2 = new SpriteComponent(backgroundStars, AssetsManager::getTexture("Stars"));
}
