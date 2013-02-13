#ifndef FLYINGKNEE_H
#define FLYINGKNEE_H

#include "Movement.h"
#include "Observer.h"


class FlyingKnee: public Movement
{
private:
	bool locked;
public:
	void tick();
	void pause(){}
	void play(){}
	FlyingKnee(StickFigure *inParent, Observer *inController);
};

#endif