#ifndef BICYCLEKICK2_H
#define BICYCLEKICK2_H

#include "Movement.h"
#include "Observer.h"


class BicycleKick2: public Movement
{
private:
	bool locked;
public:
	void tick();
	void pause(){}
	void play(){}
	BicycleKick2(StickFigure *inParent, Observer *inController);
};

#endif