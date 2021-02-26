#include "Game.h"
#include "Player.h"

//Simon Caven 11966939 26/4/2015

int main(){
	string temp;
	cout << "    ***WELCOME TO BATTLESHIP***\n" << endl;
	cout << "Please enter your name ";
	cin >> temp;
	cout << endl << endl << "Welcome " << temp << " to Battleship." << endl;

	Game game(temp);
	game.gameLogic();
	
	cout << endl;
	system("pause");
	return 0;
}
