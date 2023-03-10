#pragma once
#include "Actor.h"

class TextComponent;

class Score : public Actor
{
public:
	Score();
	void setPlayerScore(int scoreP);
	void setOpponentScore(int scoreP);

private:
	TextComponent* text;
};

