#ifndef PLAYER_H
#define PLAYER_H
#include <queue>
#include "StickFigure.h"
#include "Movement.h"
#include "BasicIntelligence.h"

class Player
{
public:
	ArtificialIntelligence *artificialIntelligence;
	float oldX;
	std::queue<Movement*> moves;
	Movement *idleMove;
	StickFigure *stickFigure;
	Player(StickFigure *inStick);

};

#endif