#include "BallBrick.h"
#include "CircleCollisionComponent.h"
#include "MoveComponent.h"
#include "NoSpriteComponent.h"
#include "Game.h"
#include "Maths.h"
#include <math.h>
#include "Log.h"
#include <string.h>
#include "PaddleBrick.h"
#include "GridBrick.h"
#include "Bricks.h"

BallBrick::BallBrick() : Actor(), horizontalSpeed(300.f), verticalSpeed(300.f), gridBrick(nullptr)
{
	setScale(7.5f);
	setPosition({ WINDOW_HEIGHT / 2, WINDOW_WIDTH - 107.5f });

	inputComponent = new MoveComponent(this);
	inputComponent->setHorizontalSpeed(horizontalSpeed);
	inputComponent->setVerticalSpeed(verticalSpeed);

	drawComponent = new NoSpriteComponent(this, getPosition(), getScale());
	drawComponent->setDrawType(NoSpriteComponent::DrawType::Circle);

	circle = new CircleCollisionComponent(this);
	circle->setRadius(7.5f);

	gridBrick = getGame().getGridBrick();
}

void BallBrick::updateActor(float dt)
{
	Actor::updateActor(dt);

	speedUpBall(0.25f);

	checkForTile();

	detectPaddleCollisions();
	detectBricksCollisions();

	drawComponent->setPosition(getPosition());
}

void BallBrick::checkForTile()
{
	float centerOfBall = getScale() / 2;
	float yBallCoord = getPosition().y;
	float xBallCoord = getPosition().x;

	if (yBallCoord > WINDOW_WIDTH - centerOfBall)
	{
		setState(ActorState::Dead);
	}
	else if (yBallCoord < centerOfBall)
	{
		Vector2 newPosition = { xBallCoord, centerOfBall };
		setPosition(newPosition);
		inputComponent->reverseVerticalSpeed(-1);
	}
	else if (xBallCoord > WINDOW_HEIGHT - centerOfBall)
	{
		Vector2 newPosition = { WINDOW_HEIGHT - centerOfBall, yBallCoord };
		setPosition(newPosition);
		inputComponent->reverseHorizontalSpeed(-1);

	}
	else if (xBallCoord < centerOfBall)
	{
		Vector2 newPosition = { centerOfBall, yBallCoord };
		setPosition(newPosition);
		inputComponent->reverseHorizontalSpeed(-1);
	}
}

void BallBrick::detectPaddleCollisions()
{
	PaddleBrick* paddleP = getGame().getPaddleBrick();

	float centerOfBall = getScale() / 2.f;
	float paddleThickness = paddleP->getWidth();
	float paddleHeight = paddleP->getHeight();
	Vector2 centerOfPaddle = paddleP->getPosition() + Vector2{ paddleThickness / 2, paddleHeight / 2 };

	Vector2 diff = getPosition() - centerOfPaddle;

	if (fabsf(diff.y) <= paddleHeight / 2 && fabsf(diff.x) <= paddleThickness / 2 + centerOfBall && verticalSpeed >= 0)
	{
		speedUpBall(0.25f);
		reverseSpeed(diff.x, diff.y, paddleHeight, centerOfBall);
	}
}

void BallBrick::detectBricksCollisions()
{
	int xCoord = floor(getPosition().x / BRICK_WIDTH);
	int yCoord = floor(getPosition().y / BRICK_HEIGHT);

	if (xCoord < 0 || yCoord < 0 || yCoord >= GRID_ROWS || xCoord >= GRID_COLS)
		return;

	if (gridBrick && gridBrick->getBricks(xCoord, yCoord) != nullptr)
	{
		speedUpBall(0.25f);

		float previousPosX = getPosition().x - inputComponent->getHorizontalSpeed() * 0.05f;
		float previousPosY = getPosition().y - inputComponent->getVerticalSpeed() * 0.05f;
		int previousCoordX = floor(previousPosX / BRICK_WIDTH);
		int previousCoordY = floor(previousPosY / BRICK_HEIGHT);

		bool bothTestedFailed = true;

		if (previousCoordX != xCoord)
		{
			if (previousCoordX < GRID_COLS && gridBrick->getBricks(previousCoordX, yCoord) == nullptr)
			{
				inputComponent->reverseHorizontalSpeed(-1);
				bothTestedFailed = false;
			}		
		}
		
		if (previousCoordY != yCoord)
		{
			if (previousCoordY < GRID_ROWS && gridBrick->getBricks(xCoord, previousCoordY) == nullptr)
			{
				inputComponent->reverseVerticalSpeed(-1);
				bothTestedFailed = false;
			}
			else if (previousCoordY == GRID_ROWS)
			{
				inputComponent->reverseVerticalSpeed(-1);
				bothTestedFailed = false;
			}
		}

		if (bothTestedFailed)
		{
			inputComponent->reverseHorizontalSpeed(-1);
			inputComponent->reverseVerticalSpeed(-1);
		}

		gridBrick->hitBrick(xCoord, yCoord);
	}
}

void BallBrick::reverseSpeed(float diffX, float diffY, float paddleThicknessP, float centerOfBallP)
{
	inputComponent->reverseVerticalSpeed(-1);

	Vector2 newPos = { getPosition().x, getPosition().y - paddleThicknessP / 2 - centerOfBallP };
	setPosition(newPos);

	float newAngleSpeed = (diffX) / 150 * verticalSpeed;
	inputComponent->setHorizontalSpeed(newAngleSpeed);
}

void BallBrick::resetBall()
{
	horizontalSpeed = 250.f;
	verticalSpeed = 250.f;

	inputComponent->setVerticalSpeed(horizontalSpeed);

	// TO ITERATE LATER; SHOULD WAIT AFTER RESET AND HAVE A RANDOM DIRECTION
	inputComponent->reverseHorizontalSpeed(-1);
}

void BallBrick::speedUpBall(float amount)
{
	if (horizontalSpeed >= 0)
	{
		horizontalSpeed += amount;
	}
	else
		horizontalSpeed -= amount;

	if (verticalSpeed >= 0)
	{
		verticalSpeed += amount;
	}
	else
		verticalSpeed -= amount;
}
