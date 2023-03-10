#pragma once
#include <vector>
#include "Observer.h"

class Actor;

class Subject
{
public:
	void addObserver(Observer* observerP);
	void removeObserver(Observer* observerP);

protected:
	void notify(const Actor& entity, Observer::Event event);

private:
	std::vector<Observer*> observers;
	int ObserverCount = 0;

};

