#pragma once
#include "MoveComponent.h"

class Vector2;
class TileRacing;
class Actor;

class NavComponent : public MoveComponent
{
public:
	NavComponent(Actor* owner, int updateOrder = 10);
	NavComponent() = delete;
	NavComponent(const NavComponent&) = delete;
	NavComponent& operator = (const NavComponent&) = delete;

	void update(float dt) override;
	void startPath(const TileRacing& startP);
	void turnTo(const Vector2& targetPositionP);

private:
	const TileRacing* nextNode;
};

