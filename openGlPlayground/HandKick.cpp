#include <iostream>
#include "HandKick.h"
//#include "BicycleKick2.h"

HandKick::HandKick(StickFigure *inParent, Observer *inController)
{
	parent=inParent;
	myController=inController;
	ticksToCompletion=100;
	subsequentMove=NULL;
	this->copyAllStarts();

	endrForearmAngle=-90;
	endrBicepAngle=-90;
	endrBicepZAngle=165;
	//parent->rotationAboutYAxis=90;

	endlForearmAngle=-45;
	endlBicepAngle=-45;
	endlBicepZAngle=45;

	endbodyAngle=0;

	endrThighAngle=0;
	endrShinAngle=-5;

	endlThighAngle=85;
	endlShinAngle=-105;

	this->createAllEnds();

	timer=0;
	numActions=2;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void HandKick::tick()
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

	float degreeTicks=-90/stepVal;
	float degreeTicks2=-165/stepVal;
	if(phase==1)
	{
		parent->rotationAboutYAxis+=degreeTicks;
		parent->rotationAboutZAxis+=degreeTicks2;
	}
	else if(phase==2)
	{
		parent->rotationAboutYAxis-=degreeTicks;
		parent->rotationAboutZAxis+=degreeTicks2;
		//must swap only once
		if(!actionSwitches[phase-1])
		{

			this->reverseMovement();
			actionSwitches[phase-1]=true;
			//subsequentMove=new BicycleKick2(parent, this);
			//return;
		}
		
	}
	else if(phase==3)
	{
		parent->rotationAboutYAxis=0;
		this->notifyObservers();
		return;
	}
	this->step(stepVal);
	//parent->position[0]+=.1;
	                           
	//parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	++timer;
	
}

void HandKick::actionFinished(StickFigure *inStick)
{
	delete subsequentMove;
	subsequentMove=NULL;
}