#pragma once
#include <SDL_stdinc.h>

class Actor;

class Component
{
public:
	Component(Actor* ownerP, int updateOrderP = 100);
	virtual ~Component();
	Component() = delete;
	Component(const Component&) = delete;
	Component& operator == (const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }

	virtual void processInput(const Uint8* keyState);
	virtual void update(float dt);
	virtual void onUpdateWorldTransform() {}

protected:
	Actor& owner;
	int updateOrder;
};

