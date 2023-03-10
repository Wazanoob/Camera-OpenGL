#include "Background.h"
#include "NoSpriteComponent.h"
#include "SpriteComponent.h"
#include "AssetsManager.h"
#include "Game.h"

Background::Background() : 
	Actor(),
	drawComponent(nullptr)
{
	Actor* background = new Actor();
	Vector2 backgroundPosition{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
	background->setPosition(backgroundPosition);
	SpriteComponent* sc = new SpriteComponent(background, AssetsManager::getTexture("PongBackground"));

	float xCoordCenterOfScreen = WINDOW_WIDTH / 2;
	const float wallHeight = 10.f;
	const float wallThickness = 5.f;

	const int numberOfWalls = 24;

	vector<NoSpriteComponent*> walls;
	walls.resize(numberOfWalls);

	for (int i = 0; i < numberOfWalls; i++)
	{
		Vector2 middleWallPosition{ xCoordCenterOfScreen, ((WINDOW_HEIGHT * i) / numberOfWalls + wallHeight / 2) };

		walls[i] = new NoSpriteComponent(this, middleWallPosition);
		walls[i]->setRectDimension(wallThickness, wallHeight);
		walls[i]->setDrawType(NoSpriteComponent::DrawType::Rectangle);
	}
}
