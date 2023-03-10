#include "Camera.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Maths.h"
#include "Achievements.h"

Camera::Camera() :
	Actor(),
	target(nullptr),
	moveComponent(nullptr),
	mouseSensitivity(500.f),
	pitch(0),
	yaw(0),
	targetOffset(Vector3{ -150.f, -150.f, 75.f }),
	moveVelocity(Vector3::zero),
	movementSmoothTime(5.f),
	armLength(100.f),
	maxSpringLength(500.f),
	minSpringLength(250.f),
	cameraOffset(Vector3{ 0.5f, 0.f, -0.3f }),
	endPoint(Vector3::zero),
	startPoint(Vector3::zero),
	cameraArmPosition(Vector3::zero),
	cameraType(CameraType::ThirdPerson),
	isSpacePressed(false)
{
	Achievements* achievements = new Achievements();

	addObserver(achievements);
	moveComponent = new MoveComponent(this);
}

void Camera::updateActor(float deltaTime)
{
	Actor::updateActor(deltaTime);

	// Compute new camera from this actor
	Vector3 cameraPosition = getPosition();
	Vector3 up = Vector3::unitZ;
	Vector3 cameraForward = getPosition() + getForward() * 100.0f;
	Matrix4 view = Matrix4::createLookAt(cameraPosition, cameraForward, up);
	getGame().getRenderer().setViewMatrix(view);

	// TO DO
	// Camera 3rd Person, Free Rotation, Zoom in/out
	// Camera 3rd Person Cinematic, always behind the player, Zoom in/out
	// Camera FPS, same Rotation as the player, no look at, no ArmLength


	// If target is null, get out
	if (!target)
		return;

	if (cameraType == CameraType::FirstPerson)
	{
		Vector3 newPosition = target->getPosition() + target->getForward() * 30.f;
		Quaternion newRotation = target->getRotation();
		setPosition(newPosition);
		setRotation(newRotation);
	}
	else
	{
		CollisionDetection();
		SetCameraTransform(deltaTime);
	}

}

void Camera::actorInput(const Uint8* keys)
{
	Vector2 mouseSpeed = getGame().getMouseSpeed();

	SDL_SetRelativeMouseMode(SDL_TRUE);

	if (cameraType == CameraType::ThirdPerson)
	{
		if (getGame().isClicking)
		{
			yaw += mouseSpeed.x * 0.005f;
		}
	}


	float currentDistance = Vector3(getPosition() - target->getPosition()).length();
	if (currentDistance > minSpringLength)
	{
		if (keys[SDL_SCANCODE_E])
		{
			notify(*this, Observer::Event::ACTOR_ZOOM_CAMERA);
			targetOffset *= 0.96f;
		}
	}
	if (currentDistance < maxSpringLength)
	{
		if (keys[SDL_SCANCODE_Q])
		{
			notify(*this, Observer::Event::ACTOR_ZOOM_CAMERA);
			targetOffset *= 1.04f;
		}
	}



	if (keys[SDL_SCANCODE_SPACE] && !isSpacePressed)
	{
		isSpacePressed = true;
		switch (cameraType)
		{
		case CameraType::FirstPerson:
			cameraType = CameraType::ThirdPerson;
			break;

		case CameraType::ThirdPerson:
		{
			cameraType = CameraType::ThirdPersonCinematic;
			yaw = 0;
			break;
		}
		case CameraType::ThirdPersonCinematic:
			cameraType = CameraType::FirstPerson;
			break;
		}

		notify(*this, Observer::Event::ACTOR_SWITCH_CAMERA);

	}
	else if (!keys[SDL_SCANCODE_SPACE])
	{
		isSpacePressed = false;
	}
}

void Camera::SetCameraTransform(float deltaTime)
{
	//float angleA = yaw * 180 / (float)M_PI;
	//float angleB = pitch * 180 / (float)M_PI;

	//float x = sin(angleA) *  cos(angleB);
	//float y = sin(angleA) * sin(angleB);
	//float z = cos(angleA);

	//Vector3 direction{ x,y,z };
	//setPosition(direction * 100.f);

	startPoint = target->getPosition();
	endPoint = target->getPosition() + target->getForward() * targetOffset + Vector3::unitZ * targetOffset;

	// Orbite around the player
	float cosY = cos(yaw);
	float sinX = sin(yaw);

	float x = cosY * (endPoint.x - target->getPosition().x) + -sinX * (endPoint.y - target->getPosition().y) + target->getPosition().x;
	float y = sinX * (endPoint.x - target->getPosition().x) + cosY * (endPoint.y - target->getPosition().y) + target->getPosition().y;
	Vector3 translate = Vector3{ x, y, endPoint.z };

	Vector3 newPosition = getPosition() + (translate - getPosition()) * movementSmoothTime * deltaTime;
	setPosition(newPosition);

	Quaternion lookat = LookAt(getPosition(), target->getPosition());
	setRotation(lookat);
}

void Camera::CollisionDetection()
{
	Vector3 collisionSimulationTest{ 100.f, 0.f, 75.f };

	float boxCollisionWidth = 50.f;
	float boxCollisionHeight = 50.f;
	float boxCollisionLength = 50.f;

	Vector3 diff = getPosition() - collisionSimulationTest;

	if (fabsf(diff.y) <= boxCollisionWidth / 2 
			&& fabsf(diff.x) <= boxCollisionLength / 2 
			&& fabsf(diff.z) <= boxCollisionHeight / 2)
	{
		// Collision Detection
	}
}
