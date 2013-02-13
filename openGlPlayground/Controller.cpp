#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "Controller.h"
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


Controller::Controller()
{
	minX=-36;
	maxX=36;
	time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);

	StickFigure *newMan=new StickFigure(-10,0,0);
	stickFigures.push_back(newMan);
	Movement *idleMove=new IdleMove(newMan);
	movements.push_back(idleMove);
	player1=new Player(newMan);
	player1->idleMove=idleMove;
	
	newMan=new StickFigure(10,0,0);
	//newMan->flipX();
	stickFigures.push_back(newMan);
	idleMove=new IdleMove(newMan);
	movements.push_back(idleMove);
	player2=new Player(newMan);
	player2->artificialIntelligence=new BasicIntelligence(player1->stickFigure, player2->stickFigure, this);
	player2->idleMove=idleMove;

	

	allPlayers.push_back(player1);
	allPlayers.push_back(player2);

	locked =false;
}

void Controller::movePlayer(int val)
{
	if(player1->stickFigure->yVelocity==0 && player1->stickFigure->position[1]==player1->stickFigure->legHeight())
		player1->stickFigure->movement=val;	

}
//int counter2=0;
void Controller::applyGravity()
{
	float gravity=-.25;
	for(unsigned int j=0;j<stickFigures.size();j++)
	{
		StickFigure *current=stickFigures[j];
		if(current->position[1]>current->legHeight() || current->yVelocity>0)
		{
			//apply gravity
			//std::cout<<counter2++<<"\n";
			current->yVelocity+=gravity;
			current->position[1]+=current->yVelocity;
			
		}
		else
		{
			
			current->yVelocity=0;
			//reset downward velocity to 0
			//TODO: apply a shock movement to absorb velocity
		}
	}
}
void Controller::harmlessCollisionDetect()
{
	float acceptableDistanceX=1.5;
	float acceptableDistanceY=player1->stickFigure->getTorso()->getElement(1,0)+player1->stickFigure->getNeck()->getElement(1,0)+1.5;

	float player1Direction=player1->stickFigure->position[0]-player1->oldX;
	float player2Direction=player2->stickFigure->position[0]-player2->oldX;

	float xDistance=player1->stickFigure->position[0]-player2->stickFigure->position[0];
	xDistance=abs(xDistance);
	float yDistance=player1->stickFigure->position[1]-player2->stickFigure->position[1];
	yDistance=abs(yDistance);

	if(xDistance<acceptableDistanceX && yDistance<acceptableDistanceY)
	{
			xDistance=player1->oldX-player2->oldX;
			if(!(xDistance<acceptableDistanceX && yDistance<acceptableDistanceY))
			{
			player1->stickFigure->position[0]=player1->oldX;
			player2->stickFigure->position[0]=player2->oldX;
			}
	}
	

	//now also check direction of each dude
	//directionalRotationAboutYAxis
	xDistance=player1->stickFigure->position[0]-player2->stickFigure->position[0];
	if(xDistance<0)
	{
		player1->stickFigure->directionalRotationAboutYAxis=0;
		player2->stickFigure->directionalRotationAboutYAxis=180;
	}
	else
	{
		player1->stickFigure->directionalRotationAboutYAxis=180;
		player2->stickFigure->directionalRotationAboutYAxis=0;
	}


}
void Controller::tick()
{
	player2->artificialIntelligence->think();
	
	player1->oldX=player1->stickFigure->position[0];
	player2->oldX=player2->stickFigure->position[0];
	
	//check boundaries
	if(player1->stickFigure->position[0]<minX)player1->stickFigure->position[0]=minX;
	if(player2->stickFigure->position[0]<minX)player2->stickFigure->position[0]=minX;
	if(player1->stickFigure->position[0]>maxX)player1->stickFigure->position[0]=maxX;
	if(player2->stickFigure->position[0]>maxX)player2->stickFigure->position[0]=maxX;
	//std::cout<<player1->stickFigure->getPosition()->getElement(0,0)<<"\n";
	for(unsigned int j=0;j<movements.size();j++)
	{
		Movement *current=movements[j];
		current->tick();
		
	}
	for(unsigned int j=0;j<stickFigures.size();j++)
	{
		StickFigure *current=stickFigures[j];
		current->move();
	}
	this->applyGravity();
	harmlessCollisionDetect();
	player2->artificialIntelligence->act();
	Movement *newAction=player2->artificialIntelligence->getNextMove();
	if(newAction!=NULL)
	{
		player2->idleMove->pause();
		//Jump *newJump=new Jump(player1->stickFigure, this);
		player2->moves.push(newAction);
		this->startNextMove(player2);
		if(player2->moves.size()>3)
			{
				Movement *toRemove=player2->moves.front();
				player2->moves.pop();
				delete toRemove;
		    }
	}
	//if(player1->stickFigure->yVelocity==0 && player1->stickFigure->position[1]==player1->stickFigure->legHeight())
	player2->stickFigure->movement=player2->artificialIntelligence->getMovement();	

}

bool Controller::startNextMove(Player *inPlayer)
{
	//std::cout<<inPlayer->stickFigure->isLocked()<<"\n";
		if(!(inPlayer->stickFigure->isLocked()) && !(inPlayer->moves.empty()))
		{
			
			inPlayer->stickFigure->lock();
			movements.push_back(inPlayer->moves.front());
			inPlayer->moves.pop();
			return true;
		}
		return false;
}

void Controller::actionFinished(StickFigure *inStick)
{
	//find the action with this parent and delete it
	Movement *toRemove=NULL;
	int indexToDelete;
	for(unsigned int j=0;j<this->movements.size();j++)
	{
		if(movements[j]->getParent()==inStick)
		{
			toRemove=movements[j];
			
			indexToDelete=j;
		}
	}
	movements.erase(movements.begin()+indexToDelete);
	delete toRemove;
	inStick->unlock();
	//grab the next move, if there is no next move, start idlemove

	//find the player who owns the stick figure to restart the idle movement
	Player *stickOwner=NULL;
	for(unsigned int j=0;j<allPlayers.size();j++)
	{
		if(allPlayers[j]->stickFigure==inStick)
		{
			stickOwner=allPlayers[j];
		}
	}
	stickOwner->idleMove->play();
	stickOwner->idleMove->tick();
	stickOwner->idleMove->pause();//resets the stick man
	bool anotherMoveStarted=this->startNextMove(stickOwner);
	if(!anotherMoveStarted)
	  stickOwner->idleMove->play();
	
}
#include "Damaged.h"
void Controller::collisionDetect(float *vertex, StickFigure *inStick, Collidable *inObject)
{
	//add a function for collision detection at the stick figure
	//	  determine first if there's a colission
	//I guess find the movement associated with the owner and get the amount of damage dealt

	
	Player *stickOwner=NULL;


	for(unsigned int j=0;j<stickFigures.size();j++)
	{
		StickFigure *current=stickFigures[j];
		if(current!=inStick)
		{
			bool hitConnected=current->collisionDetect(vertex);
			if(!hitConnected)continue;
			for(unsigned int k=0;k<allPlayers.size();k++)
	        {
				if(allPlayers[k]->stickFigure==current)
				{
					stickOwner=allPlayers[k];
				}
			}

			//int damageApplied=inMove->collide();
			int damageDealt=inObject->collide();	//Every movement is a collidable, this simply raises a bool flag to true to insure only 1 hiy
													//Every movement has an associated damage amount
			//current->life-=damageDealt;
			//std::cout<<damageDealt<<"\n";
			current->adjustHealth(-1*damageDealt);
			Damaged *hit=new Damaged(current, this);
			movements.push_back(hit);
			


			stickOwner->idleMove->pause();
		}
	}
	//this->applyGravity();
	
}
void Controller::playerAction(char code)
{
	//stop the IdleMove action
		//need a list of all actions already associated with the stickfigure
		//as long as the list is empty we can start anew
	if(code=='a')
	{
		player1->idleMove->pause();
		BasicPunch *newPunch=new BasicPunch(player1->stickFigure, this);
		//movements.push_back(newPunch);
		player1->moves.push(newPunch);
	}
	else if(code=='.')
	{
		player1->idleMove->pause();
		
		CartWheel *cartWheel=new CartWheel(player1->stickFigure, this, 1);
		//movements.push_back(cartWheel);
		player1->moves.push(cartWheel);
	}
	else if(code==',')
	{
		//std::cout<<"WORKED";
		player1->idleMove->pause();
		CartWheel *cartWheel=new CartWheel(player1->stickFigure, this, -1);
		//movements.push_back(cartWheel);
		player1->moves.push(cartWheel);
	}
	else if(code=='s')
	{
		player1->idleMove->pause();
		Cross *newKick=new Cross(player1->stickFigure, this);
		//movements.push_back(newKick);
		player1->moves.push(newKick);
	}
		else if(code=='d')
	{
		player1->idleMove->pause();
		UpperCut *newKick=new UpperCut(player1->stickFigure, this);
		player1->moves.push(newKick);
	}
	else if(code=='z')
	{
		player1->idleMove->pause();
		BasicKick *newKick=new BasicKick(player1->stickFigure, this);
		player1->moves.push(newKick);
	}
	else if(code=='x')
	{
		player1->idleMove->pause();
		BackKick *newKick=new BackKick(player1->stickFigure, this);
		//BicycleKick *newKick=new BicycleKick(player1->stickFigure, this);
		player1->moves.push(newKick);
	}
	else if(code=='n')
	{
		player1->idleMove->pause();
		//BackKick *newKick=new BackKick(player1->stickFigure, this);
		BicycleKick *newKick=new BicycleKick(player1->stickFigure, this);
		player1->moves.push(newKick);
	}
	else if(code=='m')
	{
		player1->idleMove->pause();
		HandKick *newKick=new HandKick(player1->stickFigure, this);
		//BicycleKick *newKick=new BicycleKick(player1->stickFigure, this);
		player1->moves.push(newKick);
	}
	else if(code=='f')
	{
		player1->idleMove->pause();
		SpinPunch *newKick=new SpinPunch(player1->stickFigure, this);
		player1->moves.push(newKick);
	}
		else if(code=='c')
	{
		player1->idleMove->pause();
		SideKick *newKick=new SideKick(player1->stickFigure, this, 0);
		player1->moves.push(newKick);
	}
			else if(code=='v')
	{
		player1->idleMove->pause();
		SideKick *newKick=new SideKick(player1->stickFigure, this, 1);
		//FlyingKnee *newKick=new FlyingKnee(player1->stickFigure, this);
		player1->moves.push(newKick);
		//player1->moves.p
		//movements.push_back(newKick);
	}
		else if(code=='b')
	{
		player1->idleMove->pause();
		//SideKick *newKick=new SideKick(player1->stickFigure, this, 1);
		FlyingKnee *newKick=new FlyingKnee(player1->stickFigure, this);
		player1->moves.push(newKick);
		//player1->moves.p
		//movements.push_back(newKick);
	}
	else if (code==' ')
	{
		player1->idleMove->pause();
		Jump *newJump=new Jump(player1->stickFigure, this);
		player1->moves.push(newJump);
	}
		//must first determine if there's a move in progress

		this->startNextMove(player1);
		
		if(player1->moves.size()>3)
			{
				Movement *toRemove=player1->moves.front();
				player1->moves.pop();
				delete toRemove;
		    }
//movements.push_back(newKick);
}
std::vector <Drawable *> Controller::getDrawables()
{
	std::vector<Drawable *>toReturn;
	
	for(unsigned int j=0;j<stickFigures.size();j++)
	{
		StickFigure *currentStickFigure=stickFigures[j];
		Drawable *a=dynamic_cast<Drawable *>(currentStickFigure);
		toReturn.push_back(a);
	}
	
	return toReturn;
	 
}