#include "Subject.h"
#include <iostream>

void Subject::addObserver(Observer* observerP)
{
	observers.emplace_back(observerP);
	ObserverCount += 1;
}

void Subject::removeObserver(Observer* observerP)
{
	auto iter = std::find(begin(observers), end(observers), observerP);
	observers.erase(iter);
}

void Subject::notify(const Actor& entity, Observer::Event event)
{
	for (int i = 0; i < ObserverCount; i++)
	{
		observers[i]->onNotify(entity, event);
	}
}
