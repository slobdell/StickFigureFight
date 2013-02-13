#ifndef JUMP_H
#define JUMP_H

#include "Movement.h"
#include "Observer.h"


class Jump: public Movement
{
private:
	bool locked;
public:
	void tick();
	void pause(){}
	void play(){}
	Jump(StickFigure *inParent, Observer *inController);
};

#endif