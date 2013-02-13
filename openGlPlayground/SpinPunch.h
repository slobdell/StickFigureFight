#ifndef SPINPUNCH_H
#define SPINPUNCH_H

#include "Movement.h"
#include "Observer.h"


class SpinPunch: public Movement
{
private:
	bool locked;
	

public:
	void tick();
	void pause(){}
	void play(){}
	SpinPunch(StickFigure *inParent, Observer *inController);
};

#endif