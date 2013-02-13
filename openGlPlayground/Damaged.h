#ifndef DAMAGED_H
#define DAMAGED_H

#include "Movement.h"
#include "Observer.h"


class Damaged: public Movement
{
private:
	bool locked;
	
public:
	void tick();
	void pause(){}
	void play(){}
	Damaged(StickFigure *inParent, Observer *inController);
};

#endif