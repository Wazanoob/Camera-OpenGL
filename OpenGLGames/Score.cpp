#include "Score.h"
#include "TextComponent.h"

Score::Score() : Actor()
{
	text = new TextComponent(this);
}

void Score::setPlayerScore(int scoreP)
{
	text->setPlayerScore(scoreP);
}

void Score::setOpponentScore(int scoreP)
{
	text->setOpponentScore(scoreP);
}