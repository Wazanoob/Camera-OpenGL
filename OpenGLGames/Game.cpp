#include "Game.h"
#include "Actor.h"
#include "Cube.h"
#include "Plane.h"
#include "Sphere.h"
#include "Timer.h"
#include "AssetsManager.h"
#include "MeshComponent.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	AssetsManager::loadShader("../Ressources/Shaders/Sprite.vert", "../Ressources/Shaders/Sprite.frag", "", "", "", "Sprite");
	AssetsManager::loadShader("../Ressources/Shaders/BasicMesh.vert", "../Ressources/Shaders/BasicMesh.frag", "", "", "", "BasicMesh");
	AssetsManager::loadShader("../Ressources/Shaders/Phong.vert", "../Ressources/Shaders/Phong.frag", "", "", "", "Phong");

	AssetsManager::loadTexture(renderer, "../Ressources/Textures/Default.png", "Default");
	AssetsManager::loadTexture(renderer, "../Ressources/Textures/Cube.png", "Cube");
	AssetsManager::loadTexture(renderer, "../Ressources/Textures/HealthBar.png", "HealthBar");
	AssetsManager::loadTexture(renderer, "../Ressources/Textures/Plane.png", "Plane");
	AssetsManager::loadTexture(renderer, "../Ressources/Textures/Radar.png", "Radar");
	AssetsManager::loadTexture(renderer, "../Ressources/Textures/Sphere.png", "Sphere");

	AssetsManager::loadMesh("../Ressources/Meshes/Cube.gpmesh", "Mesh_Cube");
	AssetsManager::loadMesh("../Ressources/Meshes/Plane.gpmesh", "Mesh_Plane");
	AssetsManager::loadMesh("../Ressources/Meshes/Sphere.gpmesh", "Mesh_Sphere");

	camera = new Camera();

	Cube* a = new Cube(false);
	a->setPosition(Vector3(200.f, 0.f, 50.f));
	a->setScale(25.0f);
	Quaternion q(Vector3::unitY, -Maths::piOver2);
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, 0));
	a->setRotation(q);

	Cube* c = new Cube(false);
	c->setPosition(Vector3(250.f, 50.f, 0.f));
	c->setScale(25.0f);
	c->setRotation(q);
	c->setSpeed(-0.02f);

	Cube* d = new Cube(false);
	d->setPosition(Vector3(250.f, 50.f, 50.f));
	d->setScale(25.0f);
	d->setRotation(q);
	d->setSpeed(0.015f);

	Sphere* b = new Sphere(false);
	b->setPosition(Vector3(100.f, 0.f, 75.f));
	b->setScale(3.0f);

	Cube* target = new Cube(true);
	target->setPosition(Vector3(-300.f, -100.f, 0.f));
	target->setScale(25.f);

	a->setTarget(b);
	c->setTarget(b);
	d->setTarget(b);
	
	camera->setTarget(target);

	// Floor and walls

	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Plane* p = new Plane();
			p->setPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	q = Quaternion(Vector3::unitX, Maths::piOver2);
	for (int i = 0; i < 10; i++)
	{
		Plane* p = new Plane();
		p->setPosition(Vector3(start + i * size, start - size, 0.0f));
		p->setRotation(q);

		p = new Plane();
		p->setPosition(Vector3(start + i * size, -start + size, 0.0f));
		p->setRotation(q);
	}

	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	// Forward/back walls
	for (int i = 0; i < 10; i++)
	{
		Plane* p = new Plane();
		p->setPosition(Vector3(start - size, start + i * size, 0.0f));
		p->setRotation(q);

		p = new Plane();
		p->setPosition(Vector3(-start + size, start + i * size, 0.0f));
		p->setRotation(q);
	}

	// Setup lights
	renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// UI elements
	Actor* ui = new Actor();
	ui->setPosition(Vector3(-350.0f, -350.0f, 0.0f));
	SpriteComponent* sc = new SpriteComponent(ui, AssetsManager::getTexture("HealthBar"));

	ui = new Actor();
	ui->setPosition(Vector3(375.0f, -275.0f, 0.0f));
	ui->setScale(0.75f);
	sc = new SpriteComponent(ui, AssetsManager::getTexture("Radar"));
}

void Game::processInput()
{
	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEMOTION: 
		{
			//Get mouse position
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			mousePosition.x = mouseX;
			mousePosition.y = mouseY;

			//Get mouse speed
			int xSpeed = event.motion.xrel;
			int ySpeed = -event.motion.yrel;
			mouseSpeed.x = xSpeed;
			mouseSpeed.y = ySpeed;
			break;
		}

		case SDL_MOUSEBUTTONDOWN:
			isClicking = true;
			break;

		case SDL_MOUSEBUTTONUP:
			isClicking = false;
			break;

		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				//Window::OnResize(event.window.data1, event.window.data2);
			}
			break;

		default:
			break;
		}
	}

	// Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;
}

void Game::update(float dt)
{
	// Update actors 
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor : pendingActors)
	{
		pendingActor->computeWorldTransform();
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	AssetsManager::clear();
}

void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}