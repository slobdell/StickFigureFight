#include <iostream>
#include "SpinPunch.h"

SpinPunch::SpinPunch(StickFigure *inParent, Observer *inController)
{
	damage=5;
	parent=inParent;
	myController=inController;
	ticksToCompletion=18;

	this->copyAllStarts();

	endlForearmAngle=-90;
	endlBicepAngle=-90;
	endlBicepZAngle=110;

	endbodyAngle=5;

	endrForearmAngle=50;
	endrBicepAngle=-85;

	endlThighAngle=20;
	endrThighAngle=-10;

	this->createAllEnds();

	timer=0;
	numActions=2;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void SpinPunch::tick()
{
	
	float stepVal=(float)ticksToCompletion/(float)numActions;
	//timer
	//ticksToCompletion
	//numActions
	int phase=(int)((float)numActions*(float)timer/(float)ticksToCompletion)+1;//need to round up
	
	float degreeTicks=-360.0/stepVal;

	if(phase==1)
	{
		parent->rotationAboutYAxis+=degreeTicks;
				if(!this->collisionHappened)
		{
			
			myController->collisionDetect(this->getVertex("lHand"), parent, this);
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
	
	                           
	//parent->position[0]+=.15;
	if(parent->directionalRotationAboutYAxis==0)parent->position[0]+=.15;
	else parent->position[0]-=.15;
	parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	++timer;
	
}