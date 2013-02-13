#include <iostream>
#include "BicycleKick2.h"

BicycleKick2::BicycleKick2(StickFigure *inParent, Observer *inController)
{
	damage=5;
	parent=inParent;
	myController=inController;
	ticksToCompletion=14;
	subsequentMove=NULL;
	this->copyAllStarts();

	endlForearmAngle=55;
	endlBicepAngle=-80;
	
	endrForearmAngle=-80;
	endrBicepAngle=-120;

	endbodyAngle=0;

	endrThighAngle=85;
	endrShinAngle=-5;

	endlThighAngle=-25;
	endlShinAngle=-70;

	this->createAllEnds();

	timer=0;
	numActions=2;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void BicycleKick2::tick()
{
	//if(timer==0)parent->yVelocity=3;
	if(this->subsequentMove!=NULL)
	{
		subsequentMove->tick();
		return;
	}
	float stepVal=(float)ticksToCompletion/(float)numActions;
	//timer
	//ticksToCompletion
	//numActions
	int phase=(int)((float)numActions*(float)timer/(float)ticksToCompletion)+1;//need to round up

	float degreeTicks=360.0/stepVal;

	if(phase==1)
	{
		//parent->rotationAboutYAxis+=degreeTicks;
				if(!this->collisionHappened)
		{
			
			myController->collisionDetect(this->getVertex("rFoot"), parent, this);
		}
	}
	else if(phase==2)
	{
		//parent->rotationAboutYAxis=0;
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
	//parent->position[0]+=.1;
	if(parent->directionalRotationAboutYAxis==0)parent->position[0]+=.1;
	else parent->position[0]-=.1;
	                           
	//parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	++timer;
	
}