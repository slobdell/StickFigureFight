#ifndef BASICINTELLIGENCE_H
#define BASICINTELLIGENCE_H

#include "ArtificialIntelligence.h"

class BasicIntelligence : public ArtificialIntelligence
{
private:
	int moveVal, oldMoveVal;
	float distance;
public:
	BasicIntelligence(StickFigure *inOpponent, StickFigure *inMe, Observer *inController);
	void think();
	void act();
	Movement *getNextMove();
	int getMovement();
};

#endif