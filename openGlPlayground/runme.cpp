#include <stdlib.h>
//#include <GL\GL.h>
//#include <GL\GLU.h>
#include <GL\glut.h>
#include <iostream>
#include "StickFigure.h"
#include "Controller.h"
#include <math.h>
#include "Drawable.h"


using namespace std;
const int width=480, height=320;
const float aspectRatio=(float)width/(float)height;
int counter=0;
int timer=0;
bool keyDown=false;

Controller *world;

float eye[3]={0.0f,20.0f,20.0f};
	float center[3]={0.0f, 20.0f, 0.0f};
	float up[3]={0.0f, 1.0f, 0.0f};

void keyPress(unsigned char key, int x, int y)
{
	std::cout<<(int)key<<"\n";
}
#include <windows.h>
void test()
{
	GLdouble pos3D_x, pos3D_y, pos3D_z;

// arrays to hold matrix information

GLdouble model_view[16];
glGetDoublev(GL_MODELVIEW_MATRIX, model_view);


GLdouble projection[16];
glGetDoublev(GL_PROJECTION_MATRIX, projection);


GLint viewport[4];
glGetIntegerv(GL_VIEWPORT, viewport);
	
// get 3D coordinates based on window coordinates
/*
gluUnProject(Gldouble winx, GlDouble winy, Gldouble Winz, modelMatrix[16], projMatrix[16], viewport[4],
	*objx, *objy, *objz);

gluProject(*/


gluUnProject(width/2, height/2, 0.01,
	model_view, projection, viewport,
	&pos3D_x, &pos3D_y, &pos3D_z);
//std::cout<<pos3D_x<<", "<<pos3D_y<<", "<<pos3D_z<<"\n";
}
void getKeyStates()
{
	if(GetAsyncKeyState(VK_LEFT))//53, 55 35
	{
		world->movePlayer(-1);
	}
	else if(GetAsyncKeyState(VK_RIGHT))//53, 55 35
	{
		world->movePlayer(1);
	}
	else
	{
		world->movePlayer(0);
	}
	if(GetAsyncKeyState(0x41))
	{
		bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
			world->playerAction('a');
		}
	}
	else if(GetAsyncKeyState(0x5a))
	{
		bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
			world->playerAction('z');
		}
	}
	else if(GetAsyncKeyState(0x53))
	{
		bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
			world->playerAction('s');
		}
	}
	else if(GetAsyncKeyState(0x44))
	{
		bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
			world->playerAction('d');
		}
	}
		else if(GetAsyncKeyState(/*0x58*/(int)'X'))
	{
		bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
			world->playerAction('x');
		}
	}
		else if(GetAsyncKeyState(/*0x58*/(int)'N'))
	{
		bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
			world->playerAction('n');
		}
	}
		else if(GetAsyncKeyState(/*0x58*/(int)'M'))
	{
		bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
			world->playerAction('m');
		}
	}
	else if(GetAsyncKeyState(0x46))
	{
		bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
			world->playerAction('f');
		}
	}
	else if(GetAsyncKeyState((int)' '))
	{
				bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
		
			world->playerAction(' ');
		}
	}
	else if(GetAsyncKeyState(VK_UP))
	{
				bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
		
			world->playerAction('.');
		}
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		//std::cout<<"got here";
				bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
		
			world->playerAction(',');
		}
	}
	else if(GetAsyncKeyState(0x43))
	{
		//std::cout<<"got here";
				bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
		
			world->playerAction('c');
		}
	}
	else if(GetAsyncKeyState(0x56))
	{
		//std::cout<<"got here";
				bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
		
			world->playerAction('v');
		}
	}
	else if(GetAsyncKeyState(0x42))
	{
		//std::cout<<"got here";
				bool oldVal=keyDown;
		keyDown=true;
		if(oldVal!=keyDown)//there was a change in state
		{
		
			world->playerAction('b');
		}
	}
	else
	{
		keyDown=false;
	}

}
void mainLoop(int extra)
{
	
	//std::cout<<eye[1]<<"\n";
	getKeyStates();
	world->tick();
	
	glutPostRedisplay();
	glutTimerFunc(30,mainLoop, 0);
}

void resize(int w, int h)
{
	float newAspect=(float)w/(float)h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, newAspect, 1.0f, 600.0f);//angle, aspect ratio, near, far clipping plane

	glClearColor(1.0,1.0,1.0,1.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(4);
}
float offset[3];
void display(void)
{
	
	
	
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
	//glPushMatrix();
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0, width, height, 0, 1, -1);
	//glLoadIdentity();
	//glDisable(GL_DEPTH_TEST);
	
	glColor3f(0,1,0);
	glBegin(GL_POLYGON);
	glVertex3f(-30,40,0);
	glVertex3f(-30,36,0);
	glVertex3f(-10,36,0);
	glVertex3f(-10,40,0);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(30,40,0);
	glVertex3f(30,36,0);
	glVertex3f(10,36,0);
	glVertex3f(10,40,0);
	glEnd();

	glColor3f(1,0,0);
	glBegin(GL_POLYGON);//right
	int player2Life=world->player2->stickFigure->getLife();
	glVertex3f(30,40,0);
	glVertex3f(30,36,0);
	glVertex3f(10+(20*player2Life/100),36,0);
	glVertex3f(10+(20*player2Life/100),40,0);
	glEnd();

	glBegin(GL_POLYGON);//left
	int player1Life=world->player1->stickFigure->getLife();
	//std::cout<<player1Life<<"\n";
	glVertex3f(-30+(20*player1Life/100),40,0);
	glVertex3f(-30+(20*player1Life/100),36,0);
	glVertex3f(-10,36,0);
	glVertex3f(-10,40,0);
	glEnd();
	//glPopMatrix();

	glLoadIdentity();	
	timer++;
	Singleton s=Singleton::getInstance();
	
	offset[0]=0;//20*s.fastCos(timer);
	offset[1]=5;//+5*s.fastCos(timer/10);
	offset[2]=50;//+10*s.fastSin(timer);

	//std::cout<<eye[0]+eye[1]+eye[2]+center[0]+center[1]+center[2]+up[0]+up[1]+up[2]<<"\n";
	gluLookAt(eye[0]+offset[0], eye[1]+offset[1], eye[2]+offset[2], center[0], center[1], center[2], up[0], up[1], up[2]);
	
	//std::cout<<"glulookat"<<"\n";	
	
	std::vector<Drawable *> allDrawables=world->getDrawables();
	for(unsigned int j=0;j<allDrawables.size();j++)
	{
		allDrawables[j]->draw();
	}
	
	glutSwapBuffers();
}

int main(int argc, char *argv[], char *envp)
{
	//reshape, display
	
	world=new Controller();
	
	

	//process stuff
	//render stuff
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(width,height);
	//glutInitWindowPosition(100,100);
	
	glutCreateWindow("This is a test");
	glutDisplayFunc(display);
	
	glutTimerFunc(0, mainLoop, 0);
	glClearColor(0,0,0,0);
	
    glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	gluPerspective(45.0f, aspectRatio, 1.0f, 600.0f);//angle, aspect ratio, near, far clipping plane
	//glOrtho(0, width, height, 0, 1, -1);
	//gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
	glMatrixMode(GL_MODELVIEW);
	//glOrtho(0, width, height, 0, 1, -1);
	//glDisable(GL_DEPTH_TEST);
	//gluPerspective(60,1.0,0.0,100.0);

	
	//test();
	glutMainLoop();
	//std::cout<<"got here";
	return 0;
}