#ifndef CARTWHEEL_H
#define CARTWHEEL_H

#include "Movement.h"
#include "Observer.h"


class CartWheel: public Movement
{
private:
	bool locked;
	int direction;

public:
	void tick();
	void pause(){}
	void play(){}
	CartWheel(StickFigure *inParent, Observer *inController, int inDirection);
};

#endif