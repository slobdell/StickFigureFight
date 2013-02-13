#ifndef OBSERVER_H
#define OBSERVER_H

#include "StickFigure.h"
#include "Collidable.h"

class Observer
{
public:
	virtual void actionFinished(StickFigure *inStick){}
	virtual void collisionDetect(float *vertex, StickFigure *inStick,Collidable *inObject){}
};
#endif