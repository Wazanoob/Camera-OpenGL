#include "Ball.h"
#include "CircleCollisionComponent.h"
#include "MoveComponent.h"
#include "NoSpriteComponent.h"
#include "Game.h"
#include "Score.h"
#include "Paddle.h"

Ball::Ball() : Actor(), horizontalSpeed(300.f), verticalSpeed(300.f), playerScore(0), opponentScore(0)
{
	setScale(7.5f);
	setPosition({ 400,400 });

	inputComponent = new MoveComponent(this);
	inputComponent->setHorizontalSpeed(horizontalSpeed);
	inputComponent->setVerticalSpeed(verticalSpeed);

	drawComponent = new NoSpriteComponent(this, getPosition(), getScale());
	drawComponent->setDrawType(NoSpriteComponent::DrawType::Circle);

	circle = new CircleCollisionComponent(this);
	circle->setRadius(7.5f);
}

void Ball::updateActor(float dt)
{
	Actor::updateActor(dt);
	horizontalSpeed += .25f;
	verticalSpeed += .25f;

	checkForTile();

	for (Paddle* paddle : getGame().getPaddles())
	{
		detectPaddleCollisions(paddle);
	}

	drawComponent->setPosition(getPosition());
}

void Ball::checkForTile()
{
	float centerOfBall = getScale() / 2;
	float yBallCoord = getPosition().y;
	float xBallCoord = getPosition().x;

	if (yBallCoord > WINDOW_HEIGHT - centerOfBall)
	{
		Vector2 newPosition = { xBallCoord, WINDOW_HEIGHT - centerOfBall};
		setPosition(newPosition);
		inputComponent->reverseVerticalSpeed(-1);
	}
	else if (yBallCoord < centerOfBall)
	{
		Vector2 newPosition = { xBallCoord, centerOfBall};
		setPosition(newPosition);
		inputComponent->reverseVerticalSpeed(-1);
	}
	else if (xBallCoord > WINDOW_WIDTH - centerOfBall)
	{
		Vector2 newPosition = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
		setPosition(newPosition);
		resetBall();

		playerScore += 1;
		getGame().getScore()->setPlayerScore(playerScore);
	}
	else if (xBallCoord < centerOfBall)
	{
		Vector2 newPosition = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
		setPosition(newPosition);
		resetBall();

		opponentScore += 1;
		getGame().getScore()->setOpponentScore(opponentScore);
	}
}

void Ball::detectPaddleCollisions(Paddle* paddleP)
{
	float centerOfBall = getScale() / 2.f;
	float paddleThickness = paddleP->getWidth();
	float paddleHeight = paddleP->getHeight();

	Vector2 centerOfPaddle = paddleP->getPosition() + Vector2{ paddleThickness / 2, paddleHeight / 2 };

	Vector2 diff = getPosition() - centerOfPaddle;

	if (fabsf(diff.y) <= paddleHeight / 2 && fabsf(diff.x) <= paddleThickness / 2 + centerOfBall)
	{
		switch (paddleP == getGame().getPlayerPaddle())
		{
		case true:
			reverseSpeed(diff.x,diff.y, paddleThickness, centerOfBall);
			inputComponent->setHorizontalSpeed(horizontalSpeed);
			break;

		case false:
			reverseSpeed(-diff.x, diff.y, -paddleThickness, -centerOfBall);
			inputComponent->setHorizontalSpeed(-horizontalSpeed);
			break;
		}
	}
}

void Ball::reverseSpeed(float diffX, float diffY, float paddleThicknessP, float centerOfBallP)
{
	if (diffX >= 0)
	{
		inputComponent->reverseHorizontalSpeed(-1);

		Vector2 newPos = { getPosition().x + paddleThicknessP / 2 + centerOfBallP, getPosition().y };
		setPosition(newPos);

		float newAngleSpeed = (diffY * 1.5f) / 50 * verticalSpeed;
		inputComponent->setVerticalSpeed(newAngleSpeed);
		return;
	}

	inputComponent->reverseVerticalSpeed(-1);
}

void Ball::resetBall()
{
	horizontalSpeed = 250.f;
	verticalSpeed = 250.f;

	inputComponent->setVerticalSpeed(horizontalSpeed);

	// TO ITERATE LATER; SHOULD WAIT AFTER RESET AND HAVE A RANDOM DIRECTION
	inputComponent->reverseHorizontalSpeed(-1);
}
