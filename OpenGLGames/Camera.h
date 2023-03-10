#pragma once
#include "Actor.h"
#include "Subject.h"

class Camera : public Actor, public Subject
{
public:
	enum class CameraType
	{
		FirstPerson,
		ThirdPerson,
		ThirdPersonCinematic
	};

	Camera();

	void updateActor(float deltaTime) override;
	void actorInput(const Uint8* keys) override;

	void setTarget(Actor* targetP) { target = targetP; }

private:
	void SetCameraTransform(float deltaTime);
	void CollisionDetection();

	class MoveComponent* moveComponent;
	CameraType cameraType;

	// Rotation Settings
	float mouseSensitivity;
	float pitch;
	float yaw;

	// Follow settings
	class Actor* target;
	Vector3 targetOffset;
	Vector3 moveVelocity;
	float movementSmoothTime;

	// Spring Arm
	float armLength;
	float maxSpringLength;
	float minSpringLength;
	Vector3 cameraOffset;
	Vector3 endPoint;
	Vector3 startPoint;
	Vector3 cameraArmPosition;

	Vector3 direction;

	// Collisions settings
	//bool doCollisionTest;
	//int collisionTestResolution;
	//float collisionSmoothTime;


	// Debugging
	bool isSpacePressed;
};