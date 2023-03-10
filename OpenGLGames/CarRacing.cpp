#include "CarRacing.h"
#include "CircleCollisionComponent.h"
#include "TextComponent.h"
#include "SpriteComponent.h"
#include "AssetsManager.h"
#include "InputComponent.h"
#include "GridRacing.h"
#include "TileRacing.h"
#include "Game.h"
#include "Maths.h"
#include <math.h>
#include "Log.h"
#include <string.h>


CarRacing::CarRacing(bool isPlayerOne) : 
	Actor(),
	horizontalSpeed(100.f),
	verticalSpeed(100.f),
	gridRacing(nullptr),
	circle(nullptr),
	playerOne(isPlayerOne)
{
	inputComponent = new InputComponent(this);
	inputComponent->setMaxAngularSpeed(3.5f);
	inputComponent->setMaxVerticalSpeed(0.f);
	inputComponent->setMaxHorizontalSpeed(200.f);

	if (playerOne)
	{
		inputComponent->setClockwiseKey(SDL_SCANCODE_W);
		inputComponent->setCounterClockwiseKey(SDL_SCANCODE_S);
		inputComponent->setRotationKey(SDL_SCANCODE_A);
		inputComponent->setCounterRotationKey(SDL_SCANCODE_D);

		spriteComponent = new SpriteComponent(this, AssetsManager::getTexture("Car"));
	}
	else
	{
		inputComponent->setClockwiseKey(SDL_SCANCODE_UP);
		inputComponent->setCounterClockwiseKey(SDL_SCANCODE_DOWN);
		inputComponent->setRotationKey(SDL_SCANCODE_LEFT);
		inputComponent->setCounterRotationKey(SDL_SCANCODE_RIGHT);

		spriteComponent = new SpriteComponent(this, AssetsManager::getTexture("Car2"));
	}

	gridRacing = getGame().getGridRacing();
	setPosition(gridRacing->getStartPosition());
	setRotation(0.5 * Maths::pi);
}

void CarRacing::updateActor(float dt)
{
	Actor::updateActor(dt);

	if (inputComponent->getHorizontalSpeed() > 0)
	{
		float nextX = getPosition().x + getForward().x;
		float nextY = getPosition().y + getForward().y;

		if (checkForTile(nextX, nextY) == TRACK_WALL)
		{
			inputComponent->reverseCurrentHorizontalSpeed(-.75f);
			inputComponent->setCurrentAngularSpeed(0);

			float previousX = getPosition().x - getForward().x;
			float previousY = getPosition().y - getForward().y;
			Vector2 newPos{ previousX,previousY };

			setPosition(newPos);
		}
		else if (checkForTile(nextX, nextY) == TRACK_END && !gridRacing->endGame)
		{
			gridRacing->endGame = true;

			TextComponent* text = new TextComponent(this);
			if(playerOne)
				text->setText("Player One Win!");
			else
				text->setText("Player Two Win!");
		}
	}
	else if (inputComponent->getHorizontalSpeed() < 0)
	{
		float nextX = getPosition().x - getForward().x;
		float nextY = getPosition().y - getForward().y;

		if (checkForTile(nextX, nextY) == TRACK_WALL)
		{
			inputComponent->reverseCurrentHorizontalSpeed(-.75f);
			inputComponent->setCurrentAngularSpeed(0);


			float previousX = getPosition().x + getForward().x;
			float previousY = getPosition().y + getForward().y;
			Vector2 newPos{ previousX,previousY };

			setPosition(newPos);
		}
	}

}

int CarRacing::checkForTile(int xCoord, int yCoord)
{
	xCoord = floor(xCoord / TILE_WIDTH);
	yCoord = floor(yCoord / TILE_HEIGHT);

	if (xCoord <= 0 || xCoord >= TILE_COLS ||
		yCoord <= 0 || yCoord >= TILE_ROWS)
		return TRACK_WALL;

	int trackIndex = gridRacing->getTileIndex(fabs(yCoord - 19), xCoord);

	return(trackIndex);
}