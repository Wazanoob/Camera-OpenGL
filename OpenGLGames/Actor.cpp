#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "Component.h"
#include "Maths.h"

Actor::Actor() :
	state(Actor::ActorState::Active),
	position(Vector3::zero),
	scale(1.0f),
	rotation(Quaternion::identity),
	mustRecomputeWorldTransform(true),
	game(Game::instance())
{
	game.addActor(this);
}

Actor::~Actor()
{
	game.removeActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!components.empty())
	{
		delete components.back();
	}
}

void Actor::setPosition(Vector3 positionP)
{
	position = positionP;
	mustRecomputeWorldTransform = true;
}

void Actor::setScale(float scaleP)
{
	scale = scaleP;
	mustRecomputeWorldTransform = true;
}

void Actor::setRotation(Quaternion rotationP)
{
	rotation = rotationP;
	mustRecomputeWorldTransform = true;
}

void Actor::setState(ActorState stateP)
{
	state = stateP;
}

Quaternion Actor::LookAt(const Vector3 originP, const Vector3 targetP)
{
	Vector3 forwardVector = targetP - originP;
	forwardVector.normalize();

	float dot = Vector3::dot(Vector3::unitX, forwardVector);

	if (Maths::abs(dot - (-1.0f)) < 0.000001f)
	{
		return Quaternion{ Vector3::unitZ.x, Vector3::unitZ.y, Vector3::unitZ.z, Maths::pi };
	}
	if (Maths::abs(dot - (1.0f)) < 0.000001f)
	{
		return Quaternion::identity;
	}

	float rotAngle = Maths::acos(dot);

	//std::cout << rotAngle << std::endl;

	Vector3 rotAxis = Vector3::cross(Vector3::unitX, forwardVector);
	rotAxis.normalize();

	return Quaternion{ rotAxis, rotAngle };
}

Vector3 Actor::getForward() const
{
	return Vector3::transform(Vector3::unitX, rotation);
}

Vector3 Actor::getRight() const
{
	return Vector3::transform(Vector3::unitY, rotation);
}

Vector3 Actor::getUp() const
{
	return Vector3::transform(Vector3::unitZ, rotation);
}

void Actor::computeWorldTransform()
{
	if (mustRecomputeWorldTransform)
	{
		mustRecomputeWorldTransform = false;
		worldTransform = Matrix4::createScale(scale);
		worldTransform *= Matrix4::createFromQuaternion(rotation);
		worldTransform *= Matrix4::createTranslation(position);

		for (auto component : components)
		{
			component->onUpdateWorldTransform();
		}
	}
}

void Actor::processInput(const Uint8* keyState)
{
	if (state == Actor::ActorState::Active)
	{
		for (auto component : components)
		{
			component->processInput(keyState);
		}
		actorInput(keyState);
	}
}

void Actor::actorInput(const Uint8* keyState)
{
}

void Actor::update(float dt)
{
	if (state == Actor::ActorState::Active)
	{
		computeWorldTransform();
		updateComponents(dt);
		updateActor(dt);
		computeWorldTransform();
	}
}

void Actor::updateComponents(float dt)
{
	for (auto component : components)
	{
		component->update(dt);
	}
}

void Actor::updateActor(float dt)
{
}

void Actor::addComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	components.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components))
	{
		components.erase(iter);
	}
}
