#include <iostream>
#include "FlyingKnee.h"

FlyingKnee::FlyingKnee(StickFigure *inParent, Observer *inController)
{
	damage=5;
	parent=inParent;
	myController=inController;
	ticksToCompletion=18;
	
	this->copyAllStarts();
	endlForearmAngle=endrForearmAngle=-50;
	endlBicepAngle=endrBicepAngle=-100;
	endrBicepZAngle=endlBicepZAngle=30;
	endbodyAngle=5;

	
	endlThighAngle=100;
	endlShinAngle=-120;

	endrThighAngle=-20;
	endrShinAngle=-10;

	this->createAllEnds();

	timer=0;
	numActions=3;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void FlyingKnee::tick()
{
	if(timer==0)parent->yVelocity=2.4;
	float stepVal=(float)ticksToCompletion/(float)numActions;
	//timer
	//ticksToCompletion
	//numActions
	int phase=(int)((float)numActions*(float)timer/(float)ticksToCompletion)+1;//need to round up

	float degreeTicks=360.0/stepVal;
	
		if(!this->collisionHappened)
		{
			
			myController->collisionDetect(this->getVertex("lKnee"), parent, this);
		}
	
	if(phase==1)
	{
		this->step(stepVal);
	//	parent->rotationAboutYAxis+=degreeTicks;
		
	}
	else if(phase==2)
	{
	//	parent->rotationAboutYAxis=0;
		//must swap only once
		
	}
	else if(phase==3)
	{
		this->step(stepVal);
		if(!actionSwitches[phase-1])
		{
			this->reverseMovement();
		}
		actionSwitches[phase-1]=true;
	}
	else if(phase==4)
	{
		this->notifyObservers();
		return;
	}
	
	//parent->position[0]+=.75;
	if(parent->directionalRotationAboutYAxis==0)parent->position[0]+=.75;
	else parent->position[0]-=.75;
	                           
	//parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	++timer;
	
}