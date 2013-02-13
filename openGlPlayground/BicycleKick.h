#ifndef BICYCLEKICK_H
#define BICYCLEKICK_H

#include "Movement.h"
#include "Observer.h"


class BicycleKick: public Movement,  public Observer
{
private:
	bool locked;
public:
	void tick();
	void pause(){}
	void play(){}
	BicycleKick(StickFigure *inParent, Observer *inController);
	void actionFinished(StickFigure *inStick);
};

#endif