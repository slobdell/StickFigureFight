#include <iostream>
#include "CartWheel.h"

float upwardVal=2.15;

CartWheel::CartWheel(StickFigure *inParent, Observer *inController, int inDirection)
{
	damage=0;
	direction=inDirection;
	parent=inParent;
	myController=inController;
	ticksToCompletion=28;
	
	this->copyAllStarts();

	endrForearmAngle=endlForearmAngle=-90;
	endrBicepAngle=endlBicepAngle=90;
	
	endbodyAngle=0;

	endrShinAngle=endlShinAngle=endlThighAngle=endrThighAngle=0;
	endlThighZAngle=endrThighZAngle=40;

	endlBicepZAngle=25;
	endrBicepZAngle=25;
	
	

	this->createAllEnds();
	
	//std::cout<<parent->yVelocity<<"\n";
	//std::cout<<"got here"<<"\n";

	timer=0;
	numActions=3;
	locked=false;
	actionSwitches=new bool[numActions];
	for(int j=0;j<numActions;j++)actionSwitches[j]=false;
}
//endAngle for every piece
//ticksToCompletion

void CartWheel::tick()
{
	if(timer==0)this->parent->yVelocity=upwardVal;
	//std::cout<<parent->yVelocity<<"\n";
	float stepVal=(float)ticksToCompletion/(float)numActions;
	int phase=(int)((float)numActions*(float)timer/(float)ticksToCompletion)+1;//need to round up
	float yRotation=90;
	float zRotation=-360 * direction;
	float degreeTicks=yRotation/stepVal;
	float degreeTicks2=zRotation/ticksToCompletion;

	if(ticksToCompletion/2==timer)this->parent->yVelocity=upwardVal;
	parent->rotationAboutZAxis+=degreeTicks2;
	if(phase==1)
	{
			parent->rotationAboutYAxis+=degreeTicks;
			this->step(stepVal);
	}
	else if(phase==2)
	{
		
	}
	else if(phase==3)
	{
		this->step(stepVal);
		parent->rotationAboutYAxis-=degreeTicks;
		//must swap only once
		if(!actionSwitches[phase-1])
		{
			this->reverseMovement();
		}
		actionSwitches[phase-1]=true;
	}
	else if(phase==4)
	{
		parent->rotationAboutZAxis=0;
		parent->rotationAboutYAxis=0;
		this->notifyObservers();
		return;
	}
	
	//parent->position[0]+=1.4 * direction;
	if(parent->directionalRotationAboutYAxis==0)parent->position[0]+=1.4 * direction;
	else parent->position[0]-=1.4 * direction;

	//parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	++timer;
	
}