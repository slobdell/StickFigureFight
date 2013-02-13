#ifndef BACKKICK_H
#define BACKKICK_H

#include "Movement.h"
#include "Observer.h"


class BackKick: public Movement
{
private:
	bool locked;
public:
	void tick();
	void pause(){}
	void play(){}
	BackKick(StickFigure *inParent, Observer *inController);
};

#endif