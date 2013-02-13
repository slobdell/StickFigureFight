#include <iostream>
#include "BicycleKick.h"
#include "BicycleKick2.h"

BicycleKick::BicycleKick(StickFigure *inParent, Observer *inController)
{
	damage=5;
	parent=inParent;
	myController=inController;
	ticksToCompletion=10;
	subsequentMove=NULL;
	this->copyAllStarts();

	endrForearmAngle=55;
	endrBicepAngle=-80;
	
	endlForearmAngle=-80;
	endlBicepAngle=-120;

	endbodyAngle=0;

	endlThighAngle=85;
	endlShinAngle=-5;

	endrThighAngle=-25;
	endrShinAngle=-70;

	this->createAllEnds();

	timer=0;
	numActions=2;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void BicycleKick::tick()
{
	if(timer==0)parent->yVelocity=3;
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
			
			myController->collisionDetect(this->getVertex("lFoot"), parent, this);
		}
	}
	else if(phase==2)
	{
		//parent->rotationAboutYAxis=0;
		//must swap only once
		if(!actionSwitches[phase-1])
		{

			this->reverseMovement();
			actionSwitches[phase-1]=true;
			subsequentMove=new BicycleKick2(parent, this);
			return;
		}
		
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

void BicycleKick::actionFinished(StickFigure *inStick)
{
	delete subsequentMove;
	subsequentMove=NULL;
}