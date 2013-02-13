#include <iostream>

#include <math.h>

//#include "IdleMove.h"
//using namespace std;
#include "StickFigure.h"
#include "IdleMove.h"
#include "BasicPunch.h"

void StickFigure::initComponents()
{
	life=100;
	yVelocity=0;
	rotationAboutYAxis=0;
	//flipped=false;
	directionalRotationAboutYAxis=0;
	locked=false;
     position[0]=2;
	 position[1]=0;
	 position[2]=0;

	 torsoBottom[0]=0;
	 torsoBottom[1]=0;
	 torsoBottom[2]=0;

	 torsoTop[0]=0;
	 torsoTop[1]=5;
	 torsoTop[2]=0;

	 

	 neck[0]=0;
	 neck[1]=1;
	 neck[2]=0;

	 

	 rElbow[0]=3;
	 rElbow[1]=0;
	 rElbow[2]=0;

	 
	 //arm to leg is 34/40
	 //5.27
	 rForearm[0]=0;
	 rForearm[1]=2.7;
	 rForearm[2]=0;

	 rKnee[0]=0;
	 rKnee[1]=-3;
	 rKnee[2]=0;

	 rFoot[0]=0;
	 rFoot[1]=-3.2;
	 rFoot[2]=0;
	
	 rBicepAngle=-70;
	 rForearmAngle=45;

	 //begin left stuff
	 lElbow[0]=3;
	 lElbow[1]=0;
	 lElbow[2]=0;
	 
	 lForearm[0]=0;
	 lForearm[1]=2.7;
	 lForearm[2]=0;

	 lKnee[0]=0;
	 lKnee[1]=-3;
	 lKnee[2]=0;

	 lFoot[0]=0;
	 lFoot[1]=-3.2;
	 lFoot[2]=0;
	
	 lBicepAngle=-80;//0 degrees means perpendicular to body straight out
	 lForearmAngle=15;//0 means right angle with bicep
	 bodyAngle=10;

	 movement=0;//-1,0, or 1

	 neckAngle=-10;
	 rShinAngle=-30;
	 lShinAngle=-30;

	 rThighAngle=30;
	 lThighAngle=15;

     lThighZAngle=10;
	 rThighZAngle=10;
	 lBicepZAngle=10;
	 rBicepZAngle=10;
	 rotationAboutZAxis=0;
	 oldCoords=NULL;
}
StickFigure::StickFigure(float x, float y, float z)
{
	initComponents();
	position[0]=x;
	position[1]=y;
	position[2]=z;
}
StickFigure::StickFigure()
{
	initComponents(); 
}
void StickFigure::move()
{
	float moveVal=.4;
	if(movement==-1)
	{
		position[0]-=moveVal;
	}
	else if(movement==1)
	{
		position[0]+=moveVal;
	}
	
}
float StickFigure::legHeight()
{
	
	Singleton s=Singleton::getInstance();
	
	float lVal=abs(s.fastCos(lThighAngle)*lKnee[1])
		+abs(s.fastCos(lShinAngle)*lFoot[1]);
	float rVal=abs(s.fastCos(rThighAngle)*rKnee[1])
		+abs(s.fastCos(rShinAngle)*rFoot[1]);
	//std::cout<<s.fastCos(rShinAngle)<<"\n";
	//if(lVal>rVal)return lVal;
	return rVal;
}
void StickFigure::move(float x, float y, float z)
{
	position[0]=x;
	position[1]=y;
	position[2]=z;
}
bool StickFigure::collisionDetect(float *coordinates)
{
	oldCoords=coordinates;
	Singleton s=Singleton::getInstance();
	float acceptableDistance=1.5;
	//drawCircle(neck[0], neck[1]+1.5, neck[2],1.5);
	//need to figure out actual neck position
	Matrix *headPosition=new Matrix(3,1);
	Matrix *body=&s.rotateAboutAxis(this->getTorso(),-this->bodyAngle,'z');
	body=&s.rotateAboutAxis(body, this->rotationAboutYAxis,'y');
	body=&s.rotateAboutAxis(body, this->rotationAboutZAxis,'z');
	Matrix *torsoTop=new Matrix(*body);
	*torsoTop+=*this->getPosition();
	//save this coordinate
	float x=(coordinates[0]-torsoTop->getElement(0,0));
	float y=(coordinates[1]-torsoTop->getElement(1,0));
	float z=(coordinates[2]-torsoTop->getElement(2,0));

	float distanceFromTorsoTop=(x*x+y*y+z*z);


	Matrix *torsoBottom=this->getPosition();
	x=(coordinates[0]-torsoBottom->getElement(0,0));
	y=(coordinates[1]-torsoBottom->getElement(1,0));
	z=(coordinates[2]-torsoBottom->getElement(2,0));
	
	float distanceFromTorsoBottom=(x*x+y*y+z*z);

	//std::cout<<distanceFromTorsoTop+distanceFromTorsoBottom<<"\n";
	float acceptableTorsoDistance=40;
	float acceptableKneeDistance=10;
	
	//std::cout<<"Coordinate: "<<coordinates[0]<<", "<<coordinates[1]<<", "<<coordinates[2]<<"\n";
	//std::cout<<"Torso Top: "<<torsoTop->getElement(0,0)<<", "<<torsoTop->getElement(1,0)<<", "<<torsoTop->getElement(2,0)<<"\n";
	//std::cout<<"Torso Bottom: "<<torsoBottom->getElement(0,0)<<", "<<torsoBottom->getElement(1,0)<<", "<<torsoBottom->getElement(2,0)<<"\n";
	//std::cout<<"Distance: "<<sqrt(distanceFromTorsoTop)<<", "<<sqrt(distanceFromTorsoBottom)<<"\n";
	
	//std::cout<<distanceFromTorsoTop+distanceFromTorsoBottom<<"\n";
	
	float torsoDistance=distanceFromTorsoTop+distanceFromTorsoBottom;
	//std::cout<<"Distance: "<<torsoDistance<<"\n";
	//std::cout<<"\n";
	//std::cout<<torsoDistance<<"\n";
	
	if(torsoDistance<acceptableTorsoDistance)return true;

	Matrix *knee=this->getThigh();
			
	knee=&s.rotateAboutAxis(knee, this->lThighAngle,'z');
	knee=&s.rotateAboutAxis(knee, this->lThighZAngle,'x');
	knee=&s.rotateAboutAxis(knee, this->rotationAboutYAxis,'y');
	knee=&s.rotateAboutAxis(knee, this->rotationAboutZAxis,'z');
	*knee+=*this->getPosition();
	x=(coordinates[0]-knee->getElement(0,0));
	y=(coordinates[1]-knee->getElement(1,0));
	z=(coordinates[2]-knee->getElement(2,0));
	float distanceFromKnee=(x*x+y*y+z*z);
	
	if(distanceFromKnee<acceptableKneeDistance)return true;

	knee=this->getThigh();
	knee=&s.rotateAboutAxis(knee, this->rThighAngle,'z');
	knee=&s.rotateAboutAxis(knee, this->rThighZAngle,'x');
	knee=&s.rotateAboutAxis(knee, this->rotationAboutYAxis,'y');
	knee=&s.rotateAboutAxis(knee, this->rotationAboutZAxis,'z');
	*knee+=*this->getPosition();
	x=(coordinates[0]-knee->getElement(0,0));
	y=(coordinates[1]-knee->getElement(1,0));
	z=(coordinates[2]-knee->getElement(2,0));
	distanceFromKnee=(x*x+y*y+z*z);
	if(distanceFromKnee<acceptableKneeDistance)return true;
	
	
	

	headPosition->setElement(0,0,neck[0]);
	headPosition->setElement(1,0,neck[1]+1.5);
	headPosition->setElement(2,0,neck[2]);
	headPosition=&s.rotateAboutAxis(headPosition,this->neckAngle,'z');
	*headPosition+=*body;
	headPosition=&s.rotateAboutAxis(headPosition,this->rotationAboutYAxis,'y');
	headPosition=&s.rotateAboutAxis(headPosition,this->rotationAboutZAxis,'z');
	*headPosition+=*this->getPosition();

	x=(coordinates[0]-headPosition->getElement(0,0));
	y=(coordinates[1]-headPosition->getElement(1,0));
	z=(coordinates[2]-headPosition->getElement(2,0));
	float distanceFromHead=(x*x+y*y+z*z);
	//std::cout<<sqrt(distance)<<"\n";

	if(distanceFromHead<acceptableDistance*acceptableDistance)
	{
		return true;
	}
	return false;
}

void StickFigure::drawCircle(float x, float y, float z, float radius)
{
	Singleton s=Singleton::getInstance();
	glTranslatef(x,y,z);
	glBegin(GL_LINE_LOOP);
	for(float j=0;j<360;j++)
	{
		int toUse=j;
		float innerX=radius*s.fastCos(toUse);
		float innerY=radius*s.fastSin(toUse);
		glVertex3f(innerX,innerY,0);
		
	}
	glEnd();

}

void StickFigure::drawNeckAndHead()
{
	glTranslatef(torsoTop[0], torsoTop[1], torsoTop[2]);
	glRotatef(neckAngle,0,0,1);



	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(neck[0],neck[1],neck[2]);
	glEnd();
	drawCircle(neck[0], neck[1]+1.5, neck[2],1.5);
}

void StickFigure::drawLeg(float *kneeArray, float *footArray, float thighAngle, float shinAngle)
{
	glRotatef(thighAngle,0,0,1);
	glBegin(GL_LINES);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(kneeArray[0],kneeArray[1],kneeArray[2]);
	
	glEnd();
	glPushMatrix();//start shin
	glTranslatef(kneeArray[0],kneeArray[1],kneeArray[2]);
	glRotatef(shinAngle,0,0,1);
	glBegin(GL_LINES);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(footArray[0],footArray[1],footArray[2]);
	glEnd();
	glPopMatrix();//end shin
}


void StickFigure::drawRightLeg()
{
	//glPushMatrix();
	//glTranslatef(torsoTop[0], torsoTop[1], torsoTop[2]);
	
	//glPushMatrix();//bicep
	//glRotatef(this->rBicepZAngle,-1,0,0);
	glPushMatrix();
	glTranslatef(torsoBottom[0], torsoBottom[1], torsoBottom[2]);
	glPushMatrix();
	glRotatef(this->rThighZAngle,-1,0,0);
	drawLeg(this->rKnee, this->rFoot, this->rThighAngle, this->rShinAngle);
	glPopMatrix();
	glPopMatrix();
}

void StickFigure::drawLeftLeg()
{
	glPushMatrix();
	glTranslatef(torsoBottom[0], torsoBottom[1], torsoBottom[2]);
	glPushMatrix();
	glRotatef(this->lThighZAngle,1,0,0);
	drawLeg(this->lKnee, this->lFoot, this->lThighAngle, this->lShinAngle);
	glPopMatrix();
	glPopMatrix();
}


void StickFigure::drawArm(float *elbowArray, float *forearmArray, float bicepAngle, float forearmAngle)
{
	glRotatef(bicepAngle,0,0,1);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(elbowArray[0],elbowArray[1],elbowArray[2]);
	glEnd();
	glPushMatrix();//forearm
	glTranslatef(elbowArray[0],elbowArray[1],elbowArray[2]);
	glRotatef(forearmAngle,0,0,1);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(forearmArray[0],forearmArray[1],forearmArray[2]);
	glEnd();
	glPopMatrix();//end forearm
}
void StickFigure::drawRightArm()
{
	//glRotatef(10,0,1,0);
	glPushMatrix();
	glTranslatef(torsoTop[0], torsoTop[1], torsoTop[2]);
	
	glPushMatrix();//bicep
	glRotatef(this->rBicepZAngle,1,0,0);
	drawArm(rElbow, rForearm, rBicepAngle, rForearmAngle);
	glPopMatrix();
	glPopMatrix();
}

void StickFigure::drawLeftArm()
{
	//glRotatef(-25,0,1,0);
	glPushMatrix();
	glTranslatef(torsoTop[0], torsoTop[1], torsoTop[2]);
	
	glPushMatrix();//bicep
	glRotatef(this->lBicepZAngle,-1,0,0);
	
	drawArm(lElbow, lForearm, lBicepAngle, lForearmAngle);
	glPopMatrix();
	glPopMatrix();
}
int StickFigure::getLife()
{
  return life;
}

void StickFigure::drawBody()
{
	glPushMatrix();
	
	glTranslatef(position[0],position[1],position[2]);

	glPushMatrix();
	//glLoadIdentity();
	glRotatef(this->rotationAboutZAxis,0,0,1);//rotate the dude around
	glPushMatrix();
	glRotatef(this->rotationAboutYAxis,0,1,0);//pitch the dude forward

	//if(flipped)glRotatef(180,0,1,0);
	glRotatef(directionalRotationAboutYAxis,0,1,0);
	glPushMatrix();
	glRotatef(bodyAngle,0,0,-1);
	glBegin(GL_LINES);
	glVertex3f(torsoBottom[0], torsoBottom[1], torsoBottom[2]);//bottom torso
	glVertex3f(torsoTop[0], torsoTop[1], torsoTop[2]);//top torso
    glEnd();

	glPushMatrix();//neck
	drawNeckAndHead();
	glPopMatrix();
	
	glPushMatrix();//rotate the arms out
	drawRightArm();
	drawLeftArm();
	glPopMatrix();//end entire arm w/rotation
	glPopMatrix();//end torso
	glPushMatrix();//start thigh
	drawRightLeg();
	drawLeftLeg();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();//end thigh
}
bool debug=false;
void StickFigure::draw()
{
	glColor3f(0.0f,0.0f,0.0f);
	glPushMatrix();
	if(debug && oldCoords!=NULL)this->drawCircle(oldCoords[0],oldCoords[1],oldCoords[2],1);
	glPopMatrix();
	glPushMatrix();//torso
	glLineWidth(3);
	drawBody();
	glPopMatrix();

}


Matrix *StickFigure::getPosition()
{
		Matrix *ret=new Matrix(3,1);
	ret->setElement(0,0,this->position[0]);
	ret->setElement(1,0,this->position[1]);
	ret->setElement(2,0,this->position[2]);
	return ret;
}
Matrix *StickFigure::getShin()
{
	Matrix *ret=new Matrix(3,1);
	ret->setElement(0,0,this->lFoot[0]);
	ret->setElement(1,0,this->lFoot[1]);
	ret->setElement(2,0,this->lFoot[2]);
	return ret;
}
Matrix *StickFigure::getThigh()
{
	Matrix *ret=new Matrix(3,1);
	ret->setElement(0,0,this->lKnee[0]);
	ret->setElement(1,0,this->lKnee[1]);
	ret->setElement(2,0,this->lKnee[2]);
	return ret;
}
Matrix *StickFigure::getTorso()
{
	Matrix *ret=new Matrix(3,1);
	ret->setElement(0,0,this->torsoTop[0]);
	ret->setElement(1,0,this->torsoTop[1]);
	ret->setElement(2,0,this->torsoTop[2]);
	return ret;
}
Matrix *StickFigure::getBicep()
{
	Matrix *ret=new Matrix(3,1);
	ret->setElement(0,0,this->lElbow[0]);
	ret->setElement(1,0,this->lElbow[1]);
	ret->setElement(2,0,this->lElbow[2]);
	return ret;
}
Matrix *StickFigure::getForearm()
{
	Matrix *ret=new Matrix(3,1);
	ret->setElement(0,0,this->lForearm[0]);
	ret->setElement(1,0,this->lForearm[1]);
	ret->setElement(2,0,this->lForearm[2]);
	
	return ret;
}
Matrix *StickFigure::getNeck()
{
	Matrix *ret=new Matrix(3,1);
	ret->setElement(0,0,this->neck[0]);
	ret->setElement(1,0,this->neck[1]);
	ret->setElement(2,0,this->neck[2]);
	return ret;
}
	 
	 