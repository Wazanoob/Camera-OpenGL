#pragma once

class Actor;

class Observer
{
public:

	enum class Event
	{
		ACTOR_SWITCH_CAMERA,
		ACTOR_ZOOM_CAMERA
	};

	virtual ~Observer() {};
	virtual void onNotify(const Actor& actorP, Event event) = 0;
};

