#include "NavComponent.h"
#include "Vector2.h"
#include "Actor.h"
#include "TileRacing.h"
#include "Maths.h"

NavComponent::NavComponent(Actor* owner, int updateOrder) :
	MoveComponent(owner, updateOrder),
	nextNode(nullptr)
{
}

void NavComponent::update(float dt)
{
	//if (nextNode)
	//{
	//	Vector2 dist = owner.getPosition() - nextNode->getPosition();
	//	if (Maths::nearZero(dist.length(), 2.f))
	//	{
	//		nextNode = nextNode->getParent();
	//		turnTo(nextNode->getPosition());
	//	}

	//	MoveComponent::update(dt);
	//}
}

void NavComponent::startPath(const TileRacing& startP)
{
	//nextNode = startP.getParent();
	//turnTo(nextNode->getPosition());
}

void NavComponent::turnTo(const Vector2& targetPositionP)
{
	//Vector2 dir = targetPositionP - owner.getPosition();
	//float angle = Maths::atan2(-dir.y, dir.x);
	//owner.setRotation(angle);
}
