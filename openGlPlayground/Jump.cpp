#include <iostream>
#include "Jump.h"

Jump::Jump(StickFigure *inParent, Observer *inController)
{
	parent=inParent;
	myController=inController;
	ticksToCompletion=28;

	this->copyAllStarts();

	if(parent->movement==0)
	{
	endrForearmAngle=-90;
	endrBicepAngle=90;
     endrBicepZAngle=60;
	endlBicepZAngle=60;
	endbodyAngle=0;
	endlForearmAngle=-90;
	endlBicepAngle=90;
	endlThighAngle=20;
	endlShinAngle=0;
	endrThighAngle=-20;
	endrShinAngle=0;
	}
	else if(parent->movement==1)
	{
	endlForearmAngle=endrForearmAngle=70;
	endlBicepAngle=endrBicepAngle=-80;
     endrBicepZAngle=10;
	endlBicepZAngle=10;
	endbodyAngle=35;

	endrThighAngle=endlThighAngle=120;
	endrShinAngle=endlShinAngle=-120;
	endneckAngle=45;
	}
	else if(parent->movement==-1)
	{
		endneckAngle=-45;
			endlForearmAngle=endrForearmAngle=0;
	endlBicepAngle=endrBicepAngle=120;
     endrBicepZAngle=10;
	endlBicepZAngle=10;
	endbodyAngle=-35;

	endrThighAngle=endlThighAngle=120;
	endrShinAngle=endlShinAngle=-120;
	}
	
	

	this->createAllEnds();

	timer=0;
	numActions=2;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void Jump::tick()
{
	if(timer==0)this->parent->yVelocity=3.5;
	float stepVal=(float)ticksToCompletion/(float)numActions;
	int phase=(int)((float)numActions*(float)timer/(float)ticksToCompletion)+1;//need to round up

	float degreeTicks=360.0/ticksToCompletion;
	float moveVal=.75;
	if(parent->movement==-1){moveVal*=-1;}
	else if(parent->movement==1){degreeTicks*=-1;}
	else {degreeTicks=0; moveVal=0;}
	
	if(phase==1)
	{
		//parent->rotationAboutYAxis+=degreeTicks;
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
		parent->rotationAboutZAxis=0;
		this->notifyObservers();
		return;
	}
	parent->rotationAboutZAxis+=degreeTicks;
	
	parent->position[0]+=moveVal;
	this->step(stepVal);
	++timer;
	
}