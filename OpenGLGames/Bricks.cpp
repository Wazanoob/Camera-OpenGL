#include "Bricks.h"
#include "NoSpriteComponent.h"

Bricks::Bricks(Vector2 positionP, BrickType typeP) :
	Actor(),
	drawComponent(nullptr),
	brickType(typeP)
{
	drawComponent = new NoSpriteComponent(this, positionP);
	drawComponent->setRectDimension(BRICK_WIDTH - GAP_BETWEEN_BRICKS, BRICK_HEIGHT - GAP_BETWEEN_BRICKS);
	drawComponent->setDrawType(NoSpriteComponent::DrawType::Rectangle);

	setPosition(positionP);

	switch (brickType)
	{
	case BrickType::Default:
		break;
	case BrickType::Unbreakble:
		drawComponent->setColor(128, 128, 128, 255);
		break;
	case BrickType::HardBrick:
		drawComponent->setColor(207, 75, 255, 255);
		break;
	case BrickType::Bonus:
		drawComponent->setColor(124, 252, 0, 255);
		break;
	}
}

void Bricks::setType()
{
	brickType = BrickType::Default;
	drawComponent->setColor(207, 159, 255, 255);
}

void Bricks::updateActor(float dt)
{
}
