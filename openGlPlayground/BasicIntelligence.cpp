#include <iostream>

#include "BasicIntelligence.h"
#include "Movement.h"
#include "IdleMove.h"
#include "BasicPunch.h"
#include "BasicKick.h"
#include "UpperCut.h"
#include "Cross.h"
#include "BackKick.h"
#include "SpinPunch.h"
#include "Jump.h"
#include "CartWheel.h"
#include "SideKick.h"
#include "FlyingKnee.h"
#include "BicycleKick.h"
#include "HandKick.h"

BasicIntelligence::BasicIntelligence(StickFigure *inOpponent, StickFigure *inMe, Observer *inController)
{
	theController=inController;
	moveVal=0;
	opponent=inOpponent;
	me=inMe;
	nextMove=NULL;
	//player1->idleMove->pause();
	//	BasicKick *newKick=new BasicKick(player1->stickFigure, this);
	//	player1->moves.push(newKick);
}
void BasicIntelligence::think()
{
	oldMoveVal=moveVal;
	
	float randVal=rand()%100;//0 to 99
	if(randVal<95)//continue what we did last time
	{
		
	}
	else if(me->yVelocity==0 && me->position[1]==me->legHeight())
	{


		float rand0to3=rand()%4;
		if(rand0to3<=1)
		{
		if(me->directionalRotationAboutYAxis==0)moveVal=1;
		else moveVal=-1;
		}
		else if(rand0to3==2)
		{
if(me->directionalRotationAboutYAxis==0)moveVal=-1;
		else moveVal=1;
		}
		else moveVal=0;
	}
	randVal=rand()%100;//0 to 99
	if(randVal==1)
	{
		if(me->legHeight()==me->position[1])
			this->nextMove=new Jump(me, theController);
	}
	distance=me->position[0]-opponent->position[0];//+ means he's facing left
}
//(float)(rand()%10+10);
void BasicIntelligence::act()
{
	if(abs(distance)<10)
	{
			//if we're not already moving away
			if((me->directionalRotationAboutYAxis==0 && moveVal==1) ||
				(me->directionalRotationAboutYAxis==180 && moveVal==-1))moveVal=0;
			//make it possible to move away
			if(rand()%30==0)
			{
			if(me->directionalRotationAboutYAxis==0)moveVal=-1;
			else moveVal=1;
			}
	}
	if((abs(distance)<20 && rand()%30==0 ) && (me->legHeight()==me->position[1]))
	{
	  int anotherRand=rand()%10;
	  //std::cout<<anotherRand<<"\n";
	  switch (anotherRand)
	  {
	  case 0:
		nextMove=new UpperCut(me, theController); break;
	  case 1:
		nextMove=new SpinPunch(me, theController);break;
	  case 2:
		nextMove=new SideKick(me, theController,0);break;
	  case 3:
		nextMove=new FlyingKnee(me, theController);break;
	  case 4:
		nextMove=new Cross(me, theController);break;
	  case 5:
		nextMove=new BicycleKick(me, theController);break;
      case 6:
		nextMove=new BasicPunch(me, theController);break;
      case 7:
		nextMove=new BasicKick(me, theController);break;
      case 8:
		nextMove=new BasicPunch(me, theController);break;
      case 9:
		nextMove=new SideKick(me, theController,1);break;
	  }
	}
}
Movement *BasicIntelligence::getNextMove()
{
	Movement *temp=nextMove;
	nextMove=NULL;
	return temp;
}

int BasicIntelligence::getMovement()
{
	return moveVal;
}