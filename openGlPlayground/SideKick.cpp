#include <iostream>
#include "SideKick.h"

SideKick::SideKick(StickFigure *inParent, Observer *inController, int hiOrLo)
{
	damage=5;
	parent=inParent;
	myController=inController;
	ticksToCompletion=14;

	this->copyAllStarts();
	endlForearmAngle=0;
	endlBicepAngle=-80;
	endlBicepZAngle=50;
	endbodyAngle=10;

	endrForearmAngle=50;
	endrBicepAngle=-85;

	endrThighAngle=0;
	endrShinAngle=-5;

	if(hiOrLo==1)endrThighZAngle=120;
	else if(hiOrLo==0)endrThighZAngle=60;

	endlThighAngle=0;
	endlShinAngle=0;

	this->createAllEnds();

	timer=0;
	numActions=2;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void SideKick::tick()
{
	
	float stepVal=(float)ticksToCompletion/(float)numActions;
	//timer
	//ticksToCompletion
	//numActions
	int phase=(int)((float)numActions*(float)timer/(float)ticksToCompletion)+1;//need to round up

	float degreeTicks=90.0/stepVal;

	if(phase==1)
	{
		parent->rotationAboutYAxis+=degreeTicks;
	if(parent->directionalRotationAboutYAxis==0)parent->position[0]+=.4;
	else parent->position[0]-=.4;
						if(!this->collisionHappened)
		{
			
			myController->collisionDetect(this->getVertex("rFoot"), parent, this);
		}
	}
	else if(phase==2)
	{
	if(parent->directionalRotationAboutYAxis==0)parent->position[0]-=.4;
	else parent->position[0]+=.4;
		parent->rotationAboutYAxis-=degreeTicks;
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
	
	                           
	parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	++timer;
	
}