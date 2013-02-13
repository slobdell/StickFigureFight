#ifndef IDLEMOVE_H
#define IDLEMOVE_H

#include "Movement.h"


class IdleMove: public Movement
{
private:
	float rand1, rand2, rand3, rand4, rand5, rand6, rand7, rand8;
public:
	IdleMove(StickFigure *inParent);
	void tick();

};

#endif