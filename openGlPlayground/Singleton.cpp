#include <math.h>
#include <iostream>
#include "Singleton.h"


Singleton::Singleton()
{
	for(int angle=0;angle<360;angle++)
	{
		cos_lut[angle]=cos((float)angle*.0174532925);
		sin_lut[angle]=sin((float)angle*.0174532925);
	}
	rotationMatrix=new Matrix(3,3);
}

float Singleton::fastSin(float angle)
{
	return fastSin((int)angle);
}
float Singleton::fastCos(float angle)
{
	return fastCos((int)angle);
}
float Singleton::fastSin(int angle)
{
	angle%=360;
	float retVal=sin_lut[abs(angle)];
	
	if(angle<0)retVal*=-1;
	return retVal;
}
float Singleton::fastCos(int angle)
{
	angle%=360;
	return cos_lut[abs(angle)];
}


Matrix Singleton::rotateAboutAxis(Matrix *vector, int angle, char axis)
{
	loadMatrix(axis, angle);
	return (*rotationMatrix**vector);
}


void Singleton::loadMatrix(char axis, int angle)
{
	if(axis=='x')
	{
	rotationMatrix->setElement(0,0,1);
	rotationMatrix->setElement(0,1,0);
	rotationMatrix->setElement(0,2,0);

	rotationMatrix->setElement(1,0,0);
	rotationMatrix->setElement(1,1,fastCos(angle));
	rotationMatrix->setElement(1,2,-fastSin(angle));

	rotationMatrix->setElement(2,0,0);
	rotationMatrix->setElement(2,1,fastSin(angle));
	rotationMatrix->setElement(2,2,fastCos(angle));
	}
	if(axis=='y')
	{
	rotationMatrix->setElement(0,0,fastCos(angle));
	rotationMatrix->setElement(0,1,0);
	rotationMatrix->setElement(0,2,fastSin(angle));

	rotationMatrix->setElement(1,0,0);
	rotationMatrix->setElement(1,1,1);
	rotationMatrix->setElement(1,2,0);

	rotationMatrix->setElement(2,0,-fastSin(angle));
	rotationMatrix->setElement(2,1,0);
	rotationMatrix->setElement(2,2,fastCos(angle));
	}
	if(axis=='z')
	{
		rotationMatrix->setElement(0,0,fastCos(angle));
	rotationMatrix->setElement(0,1,-fastSin(angle));
	rotationMatrix->setElement(0,2,0);

	rotationMatrix->setElement(1,0,fastSin(angle));
	rotationMatrix->setElement(1,1,fastCos(angle));
	rotationMatrix->setElement(1,2,0);

	rotationMatrix->setElement(2,0,0);
	rotationMatrix->setElement(2,1,0);
	rotationMatrix->setElement(2,2,1);
	}
}