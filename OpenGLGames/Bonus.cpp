#include "Bonus.h"
#include "NoSpriteComponent.h"
#include "CircleCollisionComponent.h"
#include "MoveComponent.h"
#include "PaddleBrick.h"
#include "Game.h"
#include "BallBrick.h"

Bonus::Bonus(Vector2 positionP) : Actor()
{
	setScale(7.5f);
	setPosition(positionP);

	drawComponent = new NoSpriteComponent(this, getPosition(), getScale());
	drawComponent->setDrawType(NoSpriteComponent::DrawType::Circle);
	drawComponent->setColor(124, 252, 0, 255);

	CircleCollisionComponent* circle = new CircleCollisionComponent(this);
	circle->setRadius(20.f);

	MoveComponent* mc = new MoveComponent(this);
	mc->setHorizontalSpeed(0);
	mc->setVerticalSpeed(100.f);
}

void Bonus::updateActor(float dt)
{
	Actor::updateActor(dt);

	detectPaddleCollisions();

	drawComponent->setPosition(getPosition());

}

void Bonus::detectPaddleCollisions()
{
	PaddleBrick* paddleP = getGame().getPaddleBrick();

	float centerOfBall = getScale() / 2.f;
	float paddleThickness = paddleP->getWidth();
	float paddleHeight = paddleP->getHeight();
	Vector2 centerOfPaddle = paddleP->getPosition() + Vector2{ paddleThickness / 2, paddleHeight / 2 };

	Vector2 diff = getPosition() - centerOfPaddle;

	if (fabsf(diff.y) <= paddleHeight / 2 && fabsf(diff.x) <= paddleThickness / 2 + centerOfBall)
	{
		Vector2 position = getGame().getBallBrick()->getPosition();

		BallBrick* ball = new BallBrick();
		BallBrick* ball2 = new BallBrick();
		ball->setPosition(position);
		ball2->setPosition(position);

		setState(ActorState::Dead);
	}
}
