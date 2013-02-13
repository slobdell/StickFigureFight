#ifndef CROSS_H
#define CROSS_H

#include "Movement.h"
#include "Observer.h"


class Cross: public Movement
{
private:
	bool locked;
	

public:
	void tick();
	void pause(){}
	void play(){}
	Cross(StickFigure *inParent, Observer *inController);
};

#endif