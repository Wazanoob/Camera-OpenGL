#include "Plane.h"
#include "MeshComponent.h"
#include "AssetsManager.h"

Plane::Plane() : Actor()
{
	setScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(AssetsManager::getMesh("Mesh_Plane"));
}
