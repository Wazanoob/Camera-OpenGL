#include "PaddleBrick.h"
#include "NoSpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "AIComponent.h"
#include "Game.h"


PaddleBrick::PaddleBrick(Vector2 positionP) :
	Actor(),
	width(100),
	height(10),
	inputComponent(nullptr),
	opponentAIComponent(nullptr)
{
	setScale(10.f);
	setPosition(positionP);

	inputComponent = new InputComponent(this);
	inputComponent->setMaxAngularSpeed(0.f);
	inputComponent->setMaxVerticalSpeed(0.f);
	inputComponent->setMaxHorizontalSpeed(600.f);



	drawComponent = new NoSpriteComponent(this, positionP);
	drawComponent->setRectDimension(width, height);
	drawComponent->setDrawType(NoSpriteComponent::DrawType::Rectangle);
}

void PaddleBrick::updateActor(float dt)
{
	Actor::updateActor(dt);

	limitMovementZone();

	drawComponent->setPosition(getPosition());
}

void PaddleBrick::limitMovementZone()
{
	float yPaddleCoord = getPosition().y;
	float xPaddleCoord = getPosition().x;
	const float paddleWidth = drawComponent->getRectDimension().x;

	if (xPaddleCoord > WINDOW_HEIGHT - paddleWidth)
	{
		Vector2 newPosition = { WINDOW_HEIGHT - paddleWidth, yPaddleCoord};
		setPosition(newPosition);
	}
	else if (xPaddleCoord < 0)
	{
		Vector2 newPosition = { 0, yPaddleCoord };
		setPosition(newPosition);
	}
}

