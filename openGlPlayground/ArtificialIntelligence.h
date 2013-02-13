#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H


#include "Movement.h"
#include "StickFigure.h"

class ArtificialIntelligence
{
protected:
	Movement *nextMove;
	StickFigure *opponent, *me;
	Observer *theController;
public:
	virtual void think(){}
	virtual void act(){}
	virtual Movement* getNextMove(){return NULL;}
	virtual int getMovement(){return 0;}
};

#endif