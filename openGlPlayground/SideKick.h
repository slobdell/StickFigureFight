#ifndef SIDEKICK_H
#define SIDEKICK_H

#include "Movement.h"
#include "Observer.h"


class SideKick: public Movement
{
private:
	bool locked;
public:
	void tick();
	void pause(){}
	void play(){}
	SideKick(StickFigure *inParent, Observer *inController, int hiOrLo);
};

#endif