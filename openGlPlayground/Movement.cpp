#include <iostream>
#include "Movement.h"


void swap(float &a, float &b)
{
	float temp;
	temp=a;
	a=b;
	b=temp;
}
void Movement::reverseMovement()
{
	for(int j=0;j<numAngles;j++)
		swap(startAngles[j], endAngles[j]);
	
}

void Movement::createAllEnds()
{
	endAngles=new float[numAngles];
	endAngles[0]=endrShinAngle;
	endAngles[1]=endrThighAngle;
	endAngles[2]=endlShinAngle;
	endAngles[3]=endlThighAngle;
	endAngles[4]=endbodyAngle;
	endAngles[5]=endneckAngle;
	endAngles[6]=endrForearmAngle;
	endAngles[7]=endrBicepAngle;
	endAngles[8]=endlForearmAngle;
	endAngles[9]=endlBicepAngle;
	endAngles[10]=endlThighZAngle;
	endAngles[11]=endrThighZAngle;
	endAngles[12]=endlBicepZAngle;
	endAngles[13]=endrBicepZAngle;
	     

	steps=new float[numAngles];
}
void Movement::step(float stepVal)
{
	for(int j=0;j<numAngles;j++)
		steps[j]=(endAngles[j]-startAngles[j])/stepVal;
	
	parent->rShinAngle+=steps[0];
	parent->rThighAngle+=steps[1];
	parent->lShinAngle+=steps[2];
	parent->lThighAngle+=steps[3];
	parent->bodyAngle+=steps[4];
	parent->neckAngle+=steps[5];
	
	parent->rForearmAngle+=steps[6];
	parent->rBicepAngle+=steps[7];
	parent->lForearmAngle+=steps[8];
	parent->lBicepAngle+=steps[9];

	parent->lThighZAngle+=steps[10];
	parent->rThighZAngle+=steps[11];;
	parent->lBicepZAngle+=steps[12];
	parent->rBicepZAngle+=steps[13];

}
void Movement::copyAllStarts()
{
	collisionHappened=false;
	numAngles=14;
	startAngles=new float[numAngles];
	endrShinAngle=startAngles[0]=startrShinAngle=parent->rShinAngle;
	endrThighAngle=startAngles[1]=startrThighAngle=parent->rThighAngle;
	endlShinAngle=startAngles[2]=startlShinAngle=parent->lShinAngle;
	endlThighAngle=startAngles[3]=startlThighAngle=parent->lThighAngle;
	endbodyAngle=startAngles[4]=startbodyAngle=parent->bodyAngle;
	endneckAngle=startAngles[5]=startneckAngle=parent->neckAngle;
	endrForearmAngle=startAngles[6]=startrForearmAngle=parent->rForearmAngle;
	endrBicepAngle=startAngles[7]=startrBicepAngle=parent->rBicepAngle;
	endlForearmAngle=startAngles[8]=startlForearmAngle=parent->lForearmAngle;
	endlBicepAngle=startAngles[9]=startlBicepAngle=parent->lBicepAngle;


	endlThighZAngle=startAngles[10]=startlThighZAngle=parent->lThighZAngle;
	endrThighZAngle=startAngles[11]=startrThighZAngle=parent->rThighZAngle;
	endlBicepZAngle=startAngles[12]=startlBicepZAngle=parent->lBicepZAngle;
	endrBicepZAngle=startAngles[13]=startrBicepZAngle=parent->rBicepZAngle;

	
}

float *Movement::getVertex(std::string inVal)
{
	Singleton s=Singleton::getInstance();
	
	Matrix *final;
	Matrix *vector;
	//possible inVals are:
	// rKnee, lKnee, rFoot, lFoot, rElbow, lElbow, rHand, 

	//left arm is negative x axis, right leg is negative x axis
		
	if(inVal=="lKnee")
	{
		vector=parent->getThigh();
		vector=&s.rotateAboutAxis(vector, parent->lThighAngle,'z');
		vector=&s.rotateAboutAxis(vector, parent->lThighZAngle,'x');
		vector=&s.rotateAboutAxis(vector, parent->directionalRotationAboutYAxis,'y');
		vector=&s.rotateAboutAxis(vector, parent->rotationAboutYAxis,'y');
		vector=&s.rotateAboutAxis(vector, parent->rotationAboutZAxis,'z');
		*vector+=*(parent->getPosition());
		final=vector;
	}
	else if(inVal=="rKnee")
	{
		vector=parent->getThigh();
		vector=&s.rotateAboutAxis(vector, parent->rThighAngle,'z');
		vector=&s.rotateAboutAxis(vector, -parent->rThighZAngle,'x');
		vector=&s.rotateAboutAxis(vector, parent->directionalRotationAboutYAxis,'y');
		vector=&s.rotateAboutAxis(vector, parent->rotationAboutYAxis,'y');
		vector=&s.rotateAboutAxis(vector, parent->rotationAboutZAxis,'z');
		*vector+=*(parent->getPosition());
		final=vector;
	}
	else if(inVal=="rFoot")
	{
		vector=parent->getShin();
		vector=&s.rotateAboutAxis(vector, parent->rShinAngle,'z');

		Matrix *vector2=parent->getThigh();
		final=&(*vector+*vector2);
		final=&s.rotateAboutAxis(final, parent->rThighAngle,'z');

		
		final=&s.rotateAboutAxis(final, -parent->rThighZAngle,'x');
		final=&s.rotateAboutAxis(final, parent->directionalRotationAboutYAxis,'y');
		final=&s.rotateAboutAxis(final, parent->rotationAboutYAxis,'y');
		final=&s.rotateAboutAxis(final, parent->rotationAboutZAxis,'z');
		*final+=*(parent->getPosition());

		//final=vector;

	}
	else if(inVal=="lFoot")
	{
		vector=parent->getShin();
		vector=&s.rotateAboutAxis(vector, parent->lShinAngle,'z');

		Matrix *vector2=parent->getThigh();
		final=&(*vector+*vector2);
		final=&s.rotateAboutAxis(final, parent->lThighAngle,'z');

		
		final=&s.rotateAboutAxis(final, parent->lThighZAngle,'x');
		final=&s.rotateAboutAxis(final, parent->directionalRotationAboutYAxis,'y');
		final=&s.rotateAboutAxis(final, parent->rotationAboutYAxis,'y');
		final=&s.rotateAboutAxis(final, parent->rotationAboutZAxis,'z');
		*final+=*(parent->getPosition());

		//final=vector;
	}
	else if(inVal=="rElbow")
	{
		vector=parent->getBicep();
		vector=&s.rotateAboutAxis(vector, parent->rBicepAngle,'z');

		vector=&s.rotateAboutAxis(vector, parent->rBicepZAngle,'x');

		Matrix *body=&s.rotateAboutAxis(parent->getTorso(), -parent->bodyAngle,'z');
		*vector+=*(body);
		vector=&s.rotateAboutAxis(vector, parent->directionalRotationAboutYAxis,'y');
		vector=&s.rotateAboutAxis(vector, parent->rotationAboutYAxis,'y');
		vector=&s.rotateAboutAxis(vector, parent->rotationAboutZAxis,'z');
		*vector+=*(parent->getPosition());
		final=vector;

	}
	else if(inVal=="lElbow")
	{
		vector=parent->getBicep();
		vector=&s.rotateAboutAxis(vector, parent->lBicepAngle,'z');

		vector=&s.rotateAboutAxis(vector, -parent->lBicepZAngle,'x');

		Matrix *body=&s.rotateAboutAxis(parent->getTorso(), -parent->bodyAngle,'z');
		*vector+=*(body);
		vector=&s.rotateAboutAxis(vector, parent->directionalRotationAboutYAxis,'y');
		vector=&s.rotateAboutAxis(vector, parent->rotationAboutYAxis,'y');
		vector=&s.rotateAboutAxis(vector, parent->rotationAboutZAxis,'z');
		*vector+=*(parent->getPosition());
		final=vector;
	}
	else if(inVal=="rHand")
	{
		vector=parent->getForearm();
		vector=&s.rotateAboutAxis(vector, parent->rForearmAngle,'z');

		Matrix *vector2=parent->getBicep();
		final=&(*vector+*vector2);
		final=&s.rotateAboutAxis(final, parent->rBicepAngle,'z');

		final=&s.rotateAboutAxis(final, parent->rBicepZAngle,'x');

		Matrix *body=&s.rotateAboutAxis(parent->getTorso(), -parent->bodyAngle,'z');
		*final+=*(body);
		final=&s.rotateAboutAxis(final, parent->directionalRotationAboutYAxis,'y');
		final=&s.rotateAboutAxis(final, parent->rotationAboutYAxis,'y');
		final=&s.rotateAboutAxis(final, parent->rotationAboutZAxis,'z');
		*final+=*(parent->getPosition());
	}
	else if(inVal=="lHand")//lhand is what currently does not work allegedly
	{
		vector=parent->getForearm();
		vector=&s.rotateAboutAxis(vector, parent->lForearmAngle,'z');

		Matrix *vector2=parent->getBicep();
		final=&(*vector+*vector2);
		final=&s.rotateAboutAxis(final, parent->lBicepAngle,'z');
		
		
		
		final=&s.rotateAboutAxis(final, -parent->lBicepZAngle,'x');

		Matrix *body=&s.rotateAboutAxis(parent->getTorso(), -parent->bodyAngle,'z');
		*final+=*(body);
		final=&s.rotateAboutAxis(final, parent->directionalRotationAboutYAxis,'y');
		final=&s.rotateAboutAxis(final, parent->rotationAboutYAxis,'y');
		final=&s.rotateAboutAxis(final, parent->rotationAboutZAxis,'z');

		
		*final+=*(parent->getPosition());
	}
	float *retVal=new float[3];
	retVal[0]=final->getElement(0,0);
	retVal[1]=final->getElement(1,0);
	retVal[2]=final->getElement(2,0);
	return retVal;
}
/*
	float torsoBottom[3];
	float torsoTop[3];
	float neck[3];
	float rElbow[3];
	float rKnee[3];
	float rFoot[3];
	float rForearm[3];
	float lElbow[3];
	float lKnee[3];
	float lFoot[3];
	float lForearm[3];
	*/