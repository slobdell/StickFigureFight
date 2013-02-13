#ifndef HANDKICK_H
#define HANDKICK_H

#include "Movement.h"
#include "Observer.h"


class HandKick: public Movement,  public Observer
{
private:
	bool locked;
public:
	void tick();
	void pause(){}
	void play(){}
	HandKick(StickFigure *inParent, Observer *inController);
	void actionFinished(StickFigure *inStick);
};

#endif