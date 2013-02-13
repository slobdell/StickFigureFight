#include <iostream>
#include "BasicKick.h"

BasicKick::BasicKick(StickFigure *inParent, Observer *inController)
{
	damage=5;
	parent=inParent;
	myController=inController;
	ticksToCompletion=12;

	this->copyAllStarts();
	endrForearmAngle=55;
	endrBicepAngle=-80;
	endbodyAngle=15;
	endlForearmAngle=50;
	endlBicepAngle=-85;
	endrThighAngle=120;
	endrShinAngle=-5;

	endlThighAngle=-45;
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

void BasicKick::tick()
{
	
	float stepVal=(float)ticksToCompletion/(float)numActions;
	//timer
	//ticksToCompletion
	//numActions
	int phase=(int)((float)numActions*(float)timer/(float)ticksToCompletion)+1;//need to round up
	
	if(phase==1)
	{
							if(!this->collisionHappened)
		{
			
			myController->collisionDetect(this->getVertex("rFoot"), parent, this);
		}		
	}
	else if(phase==2)
	{
		
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
	//parent->position[0]+=.65;
	if(parent->directionalRotationAboutYAxis==0)parent->position[0]+=.65;
	else parent->position[0]-=.65;
	                           
	parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	++timer;
	
}