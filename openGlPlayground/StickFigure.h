#ifndef STICKFIGURE_H
#define STICKFIGURE_H


#include <GL\glut.h>
#include "Drawable.h"
#include "Singleton.h"
#include "Matrix.h"


//using namespace std;
class StickFigure : public Drawable
{
private:
	//std::vector <Movement *> movements;
	
	//bool flipped;
	bool locked;
	int life;
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


	
	void drawBody();
	void drawNeckAndHead();
	void drawRightArm();
	void drawLeftArm();
	void drawRightLeg();
	void drawLeftLeg();
	void drawArm(float *elbowArray, float *forearmArray, float bicepAngle, float forearmAngle);
	void drawLeg(float *kneeArray, float *footArray, float thighAngle, float shinAngle);
	void initComponents();
	float *oldCoords;
public:
	float directionalRotationAboutYAxis;
	bool collisionDetect(float *coordinates);
	void drawCircle(float x, float y, float z, float radius);
	void lock(){locked=true;}
	void unlock(){locked=false;}
	bool isLocked(){return locked;}

	int getLife();
	float rotationAboutYAxis;
	float rotationAboutZAxis;
	int movement;
	//void flipX();
	StickFigure(float x, float y, float z);
	void move(float x, float y, float z);
	float yVelocity;
	float bodyAngle;
	float legHeight();
	float position[3];
	float rBicepAngle;
	float rForearmAngle;
	float lBicepAngle;
	float lForearmAngle;
	float neckAngle;
	float rShinAngle;
	float lShinAngle;
	float rThighAngle;
	float lThighAngle;

	float lThighZAngle;
	float rThighZAngle;
	float lBicepZAngle;
	float rBicepZAngle;
	
	StickFigure();
	void draw();
	void move();
	void adjustHealth(int inVal){life+=inVal;}
	Matrix *getShin();
	Matrix *getThigh();
	Matrix *getTorso();
	Matrix *getBicep();
	Matrix *getForearm();
	Matrix *getNeck();
	Matrix *getPosition();
	//Matrix getHeadCenter();
	//Matrix getHeadRadius();

	

	
};

#endif