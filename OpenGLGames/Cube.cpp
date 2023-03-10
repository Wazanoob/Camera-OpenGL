#include "Cube.h"
#include "MeshComponent.h"
#include "AssetsManager.h"
#include "InputComponent.h"

Cube::Cube(bool canMoveP) : target(nullptr), canMove(canMoveP)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(AssetsManager::getMesh("Mesh_Cube"));

	if (!canMove)
		return;
	InputComponent* moveComponent = new InputComponent(this);
	moveComponent->setMaxForwardSpeed(100.f);
}

void Cube::setTarget(Actor* targetP)
{
	target = targetP;
}

void Cube::updateActor(float deltaTime)
{
	if (!target)
		return;

	Vector3 targetPosition = target->getPosition();
	Vector3 actorPosition = getPosition();

	float adjX = cos(speed);
	float adjY = sin(speed);

	float x = adjX * (getPosition().x - targetPosition.x) + -adjY * (getPosition().y - targetPosition.y) + targetPosition.x;
	float y = adjY * (getPosition().x - targetPosition.x) + adjX * (getPosition().y - targetPosition.y) + targetPosition.y;

	Vector3 translate = Vector3{ x, y, getPosition().z };

	setPosition(translate);

	Quaternion lookRotation(LookAt(actorPosition, targetPosition));
	setRotation(lookRotation);
}
