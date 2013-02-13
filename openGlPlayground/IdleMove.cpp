#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "IdleMove.h"


float generateRandom()
{
	
	float toReturn=(float)(rand()%10+10);
		//std::cout<<toReturn<<"\n";
	return toReturn;
	
}

IdleMove::IdleMove(StickFigure *inParent)
{
	paused=false;
	parent=inParent;
	timer=0;
	rand1=generateRandom();
	rand2=generateRandom();
	rand3=generateRandom();
	rand4=generateRandom();
	rand5=generateRandom();
	rand6=generateRandom();
	rand7=generateRandom();
	rand8=generateRandom();
	
}



void IdleMove::tick()
{
	if(paused)return;
	parent->rotationAboutYAxis=0;
	parent->rotationAboutZAxis=0;

	parent->lBicepZAngle=10;
	parent->rBicepZAngle=10;
	parent->rThighZAngle=10;
	parent->lThighZAngle=10;

	
	float multiplier=1.0;
	if(parent->movement!=0)
	{
		multiplier=3;
	}
	parent->lBicepAngle=-85+abs(cos((float)timer/rand1)*30.0);
	
	parent->lForearmAngle=35+abs(sin((float)timer/rand2)*15.0);
	
	parent->rBicepAngle=-60+abs(sin((float)timer/rand3)*20.0);
	parent->rForearmAngle=35+abs(cos((float)timer/rand4)*15.0);

	parent->lThighAngle=20+abs(sin((float)timer*multiplier/rand5)*10.0);                        
	parent->lShinAngle=-(10+abs(sin((float)timer*multiplier/rand6)*30.0));  

	parent->rThighAngle=0+abs(cos((float)timer*multiplier/rand7)*10.0);                        
	parent->rShinAngle=-(10+abs(cos((float)timer*multiplier/rand8)*30.0));  

	parent->neckAngle=-5+abs(cos((float)timer/rand7)*15.0);
	parent->bodyAngle=1+abs(cos((float)timer/(10*rand7))*9.0);
	//std::cout<<parent->lShinAngle<<"\n";
	//float val=parent->legHeight();
	if(parent->yVelocity==0)
		parent->move(parent->position[0],parent->legHeight(),parent->position[2]);
	//height=sin(thighangle)*thighHeight + sin(shinAngle)*shinHeight
	//parent->rotationAboutYAxis+=1;
	//max-45, min=-86
	timer++;
}

