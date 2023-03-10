#pragma once
#include "Observer.h"
#include  <map>

class Achievements : public Observer
{
public:
	Achievements();

	virtual void onNotify(const Actor& actorP, Event event) override;

private:
	enum class Achievement
	{
		CameraSwitch,
		CameraZoom
	};

	std::map<Achievement, bool> achievementState;

	void unlock(Achievement achievementP);
};

