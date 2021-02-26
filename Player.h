#include <string>
#include <iostream>
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player{

private:
	//Data Members
	string playerName;
	char playerBoard[10][10];
	char oppBoard[10][10];
	int ships[5];

public:
	//Constructors
	Player(string);
	Player();

	//Member Functions
	void displayBoard(string,bool);
	void changeBoard(char, int, int, char, int);
	void randomBoard();
	void setBoard();
	void markPlayBoard(int, int, char);
	void markOppBoard(int, int, char);
	bool checkBoard(int, int, int, char);
	bool endGame();
	char getPlayBoard(int, int);
	char getOppBoard(int, int);
	int getShips(int);
	string getName();
	
};


#endif