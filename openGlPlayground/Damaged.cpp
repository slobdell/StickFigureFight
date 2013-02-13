#include <iostream>
#include "Damaged.h"

Damaged::Damaged(StickFigure *inParent, Observer *inController)
{
	//std::cout<<"Damaged object created\n";
	parent=inParent;
	myController=inController;
	ticksToCompletion=12;

	this->copyAllStarts();

	endrForearmAngle=25;
	endrBicepAngle=-85;
	endlBicepZAngle=endrBicepZAngle=45;
	endbodyAngle=-40;
	endlForearmAngle=30;
	endlBicepAngle=-85;
	endlThighAngle=45;
	endlShinAngle=-5;
	this->createAllEnds();

	timer=0;
	numActions=2;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void Damaged::tick()
{
	
	float stepVal=(float)ticksToCompletion/(float)numActions;
	//timer
	//ticksToCompletion
	//numActions
	int phase=(int)((float)numActions*(float)timer/(float)ticksToCompletion)+1;//need to round up


	if(phase==1)
	{
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
	if(parent->directionalRotationAboutYAxis==0)parent->position[0]-=.2;
	else parent->position[0]+=.2;
	//parent->position[0]+=.1;                         
	//parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	++timer;
	
}