#ifndef BASICKICK_H
#define BASICKICK_H

#include "Movement.h"
#include "Observer.h"


class BasicKick: public Movement
{
private:
	bool locked;
	

public:
	void tick();
	void pause(){}
	void play(){}
	BasicKick(StickFigure *inParent, Observer *inController);
};

#endif