#include "Sphere.h"
#include "MeshComponent.h"
#include "InputComponent.h"
#include "AssetsManager.h"

Sphere::Sphere(bool canMoveP) : Actor(), canMove(canMoveP)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(AssetsManager::getMesh("Mesh_Sphere"));


	if (!canMove)
		return;
	InputComponent* moveComponent = new InputComponent(this);
	moveComponent->setMaxForwardSpeed(100.f);
}
