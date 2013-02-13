#include <iostream>
#include "BackKick.h"

BackKick::BackKick(StickFigure *inParent, Observer *inController)
{
	damage=5;
	parent=inParent;
	myController=inController;
	ticksToCompletion=18;

	this->copyAllStarts();
	endrForearmAngle=55;
	endrBicepAngle=-80;
	endbodyAngle=-55;

	endlForearmAngle=50;
	endlBicepAngle=-85;

	endlThighAngle=145;
	endlShinAngle=-5;

	endrThighAngle=0;
	endrShinAngle=0;

	this->createAllEnds();

	timer=0;
	numActions=2;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void BackKick::tick()
{
	
	float stepVal=(float)ticksToCompletion/(float)numActions;
	//timer
	//ticksToCompletion
	//numActions
	int phase=(int)((float)numActions*(float)timer/(float)ticksToCompletion)+1;//need to round up

	float degreeTicks=360.0/stepVal;

	if(phase==1)
	{
		parent->rotationAboutYAxis+=degreeTicks;
								if(!this->collisionHappened)
		{
			
			myController->collisionDetect(this->getVertex("lFoot"), parent, this);
		}
	}
	else if(phase==2)
	{
		parent->rotationAboutYAxis=0;
		//must swap only once
		if(!actionSwitches[phase-1])
		{
			this->reverseMovement();
		}
		actionSwitches[phase-1]=true;
	}
	else if(phase==3)
	{
		this->notifyObservers();
		return;
	}
	this->step(stepVal);
	if(parent->directionalRotationAboutYAxis==0)parent->position[0]+=.1;
	else parent->position[0]-=.1;
	                           
	parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	++timer;
	
}