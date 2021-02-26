#include "Player.h"
#ifndef GAMEBATTLE_H
#define GAMEBATTLE_H

class Game{

private:
	//Data Members
	Player player;
	Player computer;

public:
	//Constructor
	Game(string);

	//Member functions
	void gameLogic();
	void playerTurn(int,int);
	void computerTurn(int,int);
	void reveal(char);
	void AI(int&,int&);
	void endReveal();
};

#endif