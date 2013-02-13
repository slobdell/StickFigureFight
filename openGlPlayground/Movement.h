#ifndef MOVEMENT_H
#define MOVEMENT_H



#include <string>
#include "StickFigure.h"
#include "Observer.h"
#include "Matrix.h"
#include "Collidable.h"

class Movement : public Collidable
{
protected:
	StickFigure *parent;
	Movement *subsequentMove;
	bool paused;
	int timer;
	Observer *myController;
	int numActions;
	bool *actionSwitches;
	float endlBicepAngle,
	 endlForearmAngle,
	 endrBicepAngle,
	 endrForearmAngle,
	 endlThighAngle,
	 endlShinAngle,
	 endrThighAngle,
	 endrShinAngle,
	 endneckAngle,
	 endbodyAngle,
	 startlBicepAngle,
	 startlForearmAngle,
	 startrBicepAngle,
	 startrForearmAngle,
	 startlThighAngle,
	 startlShinAngle,
	 startrThighAngle,
	 startrShinAngle,
	 startneckAngle,
	 startbodyAngle,
	startlThighZAngle,
	 startrThighZAngle,
	 startlBicepZAngle,
	 startrBicepZAngle,
	 endlThighZAngle,
	 endrThighZAngle,
	 endlBicepZAngle,
	 endrBicepZAngle;


	int ticksToCompletion;
	void copyAllStarts();
	void reverseMovement();//reverses the movement
	
	float *startAngles;
	float *endAngles;
	float *steps;
	int numAngles;
	//chapman in 5-101
	void createAllEnds();
	void step(float stepVal);
	float *getVertex(std::string inVal);
	bool collisionHappened;
	int damage;
public:
	
	int collide(){collisionHappened=true; return damage;}
	virtual void tick(){}
	void pause(){paused=true;}
	void play(){paused=false;}
	StickFigure *getParent(){return parent;}
	void notifyObservers(){myController->actionFinished(parent);}
	
};



#endif