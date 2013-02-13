#ifndef UPPERCUT_H
#define UPPERCUT_H

#include "Movement.h"
#include "Observer.h"


class UpperCut: public Movement
{
private:
	bool locked;
	

public:
	void tick();
	void pause(){}
	void play(){}
	UpperCut(StickFigure *inParent, Observer *inController);
};

#endif