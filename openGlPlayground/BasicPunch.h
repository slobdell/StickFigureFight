#ifndef BASICPUNCH_H
#define BASICPUNCH_H

#include "Movement.h"
#include "Observer.h"


class BasicPunch: public Movement
{
private:
	bool locked;
	

public:
	void tick();
	void pause(){}
	void play(){}
	BasicPunch(StickFigure *inParent, Observer *inController);
};

#endif