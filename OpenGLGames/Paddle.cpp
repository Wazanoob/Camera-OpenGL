#include "Paddle.h"
#include "NoSpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "AIComponent.h"
#include "Game.h"


Paddle::Paddle(Vector2 positionP, PaddleController controllerP) :
	Actor(),
	width(10),
	height(100),
	controller(controllerP),
	inputComponent(nullptr),
	opponentAIComponent(nullptr)
{
	setScale(10.f);
	setPosition(positionP);

	if (controller == PaddleController::Player)
	{
		inputComponent = new InputComponent(this);
	}
	else
	{
		opponentAIComponent = new AIComponent(this);
	}

	drawComponent = new NoSpriteComponent(this, getPosition(), getScale());
	drawComponent->setRectDimension(width, height);
	drawComponent->setDrawType(NoSpriteComponent::DrawType::Rectangle);
}

void Paddle::updateActor(float dt)
{
	Actor::updateActor(dt);

	limitMovementZone();

	drawComponent->setPosition(getPosition());
}

void Paddle::limitMovementZone()
{
	float yPaddleCoord = getPosition().y;
	float xPaddleCoord = getPosition().x;
	const float paddleHeight = drawComponent->getRectDimension().y;

	if (yPaddleCoord > WINDOW_HEIGHT - paddleHeight)
	{
		Vector2 newPosition = { xPaddleCoord, WINDOW_HEIGHT - paddleHeight};
		setPosition(newPosition);
	}
	else if (yPaddleCoord < 0)
	{
		Vector2 newPosition = { xPaddleCoord, 0 };
		setPosition(newPosition);
	}
}
