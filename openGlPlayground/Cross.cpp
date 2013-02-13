#include <iostream>
#include "Cross.h"

Cross::Cross(StickFigure *inParent, Observer *inController)
{
	damage=5;
	parent=inParent;
	myController=inController;
	ticksToCompletion=10;

	this->copyAllStarts();

	endlForearmAngle=-90;
	endlBicepAngle=40;

	endrForearmAngle=65;
	endrBicepAngle=20;

	endbodyAngle=40;



	endrThighAngle=-45;
	endrShinAngle=-0;

	endlThighAngle=30;
	endlShinAngle=-30;

	this->createAllEnds();

	timer=0;
	numActions=2;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void Cross::tick()
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
			
			myController->collisionDetect(this->getVertex("lHand"), parent, this);
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
	//parent->position[0]+=.2;
	if(parent->directionalRotationAboutYAxis==0)parent->position[0]+=.2;
	else parent->position[0]-=.2;
	                           
	parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	++timer;
	
}