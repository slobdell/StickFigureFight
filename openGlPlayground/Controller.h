#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "StickFigure.h"
#include "Drawable.h"
#include "Collidable.h"
#include "Movement.h"
#include "Player.h"
#include "Observer.h"


class Controller : public Observer
{
private:

	std::vector <StickFigure *>stickFigures; 
	std::vector <Movement *>movements; 
	std::vector <Player *> allPlayers;
	bool locked;
	int maxX, minX;
	
	void harmlessCollisionDetect();
public:
	Player *player1;
	Player *player2;
	void collisionDetect(float *vertex, StickFigure *inStick, Collidable *inObject);
	bool startNextMove(Player *inPlayer);
	bool isLocked(){return locked;}
	void lock(){locked=true;}
	void unlock(){locked=false;}
	Controller();
	void tick();
	void applyGravity();
	void actionFinished(StickFigure *inStick);//ideally a PLAYER
	void movePlayer(int val);
	void playerAction(char code);
	std::vector <Drawable *>getDrawables();
	
};

#endif