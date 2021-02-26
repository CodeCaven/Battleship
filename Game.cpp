#include "Game.h"
 
//Game constructor calls player constructors to create its 2 player objects
Game::Game(string id){
	Player play(id);
	Game::player = play;       
	Player play2;
	Game::computer = play2;      
}

//game logic function
void Game::gameLogic(){
	char cheat;
	char level;
	char temp;
	char row;
	char crandrow;
	int irow;
	int icol;
	int randrow;
	int randcol;
	bool gameOver = false;
	bool random = false;
	bool guess = false;
	bool comp = true;

	cout << "Press S to set your own board, Press R for a random board ";
	cin.sync();
	temp = cin.get();
	cin.sync();
	while (!(temp == 's' || temp == 'r')){
		cout << "Press S for Set, R for Random ";
		temp = cin.get();
		cin.sync();
	}
	
	if (temp == 's'){
		player.displayBoard("player",false);
		player.setBoard();
	}
	else if (temp == 'r'){
		player.randomBoard();
		player.displayBoard("player",false);
		this_thread::sleep_for(chrono::seconds(3));
	}

	cout << "Press E for Easy, Press H for Hard ";
	cin.sync();
	level = cin.get();
	cin.sync();
	while (!(level == 'e' || level == 'h')){
		cout << "Press E for Easy, H for Hard ";
		level = cin.get();
		cin.sync();
	}

	cout << "Would you like to play in Cheat Mode Y/N ";
	cin.sync();
	cheat = cin.get();
	cin.sync();
	while (!(cheat == 'y' || cheat == 'n')){
		cout << "Y or N to cheat  ";
		cheat = cin.get();
		cin.sync();
	}

	//Main game loop
	while (!random || !gameOver){ 
		srand(time(NULL));

			randrow = rand() % 10;
			randcol = rand() % 10;
			
		if (level == 'h'){
			AI(randrow, randcol);	
		}

		crandrow = randrow + 97;
		
		if (player.getPlayBoard(randrow, randcol) != '-' && player.getPlayBoard(randrow, randcol) != '*'){
			random = true;
		}
		else{
			random = false;
		}

		if (random){
			player.displayBoard("opp",false);
			if (cheat == 'y'){
				computer.displayBoard("player",true);
			}
			
			cout << player.getName() << " it is your go. Please enter a row ";
			cin.sync();
			row = cin.get();
			cin.sync();
			while (row - 97 < 0 || row - 97 > 9){
				cout << "Enter a row between A and J ";
				row = cin.get();
				cin.sync();	
			}
			irow = row - 97;
			
			cout << "Please enter a column ";
			while (!(cin >> icol) || icol < 0 || icol > 9){
				cout << "Enter a number between 0 and 9 ";
				cin.clear();
				cin.sync();
			}

			if (player.getOppBoard(irow, icol) == ' '){

				playerTurn(irow, icol);
				this_thread::sleep_for(chrono::seconds(2));
				player.displayBoard("opp", false);
				this_thread::sleep_for(chrono::seconds(2));
				

				if (player.endGame()){
					cout << "Congratulations " << player.getName() << " you win" << endl;
					comp = false;
					gameOver = true;
				}

				if (comp){
					
					cout << "The computers go... " << crandrow << " " << randcol << " ...";
					
					this_thread::sleep_for(chrono::seconds(2));
					computerTurn(randrow, randcol);
					this_thread::sleep_for(chrono::seconds(2));
					player.displayBoard("player", false);

					if (computer.endGame()){
						cout << "Sorry " << player.getName() << " you lost" << endl;
						endReveal();
						player.displayBoard("opp",false);
						gameOver = true;
					}
				}
			}
			else{
				cout << "You have already fired there! " << endl;
			}
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

//player turn function
void Game::playerTurn(int row,int col){


	if (computer.getPlayBoard(row, col) == 'A'){
		cout << "HIT!" << endl;
		player.markOppBoard(row, col, '*');
				
		if (player.getShips(0) == 5){
			cout << "You sunk my Aircraft carrier" << endl;
			reveal('A');
		}
	}
	else if (computer.getPlayBoard(row, col) == 'B'){
		cout << "HIT!" << endl;
		player.markOppBoard(row, col, '*');

		if (player.getShips(1) == 4){
			cout << "You sunk my Battleship" << endl;
			reveal('B');
		}
	}
	else if (computer.getPlayBoard(row, col) == 'D'){
		cout << "HIT!" << endl;
		player.markOppBoard(row, col, '*');
		
		if (player.getShips(2) == 3){
			cout << "You sunk my Destroyer" << endl;
			reveal('D');
		}
	}
	else if (computer.getPlayBoard(row, col) == 'S'){
		cout << "HIT!" << endl;
		player.markOppBoard(row, col, '*');
		
		if (player.getShips(3) == 3){
			cout << "You sunk my Submarine" << endl;
			reveal('S');
		}
	}
	else if (computer.getPlayBoard(row, col) == 'P'){
		cout << "HIT!" << endl;
		player.markOppBoard(row, col, '*');
		
		if (player.getShips(4) == 2){
			cout << "You sunk my Patrol Boat" << endl;
			reveal('P');
		}
	}
	else if (computer.getPlayBoard(row, col) == ' '){
		cout << "MISS!" << endl;
		player.markOppBoard(row, col, '-');
	}
}

//computer turn function
void Game::computerTurn(int row, int col){

	if (player.getPlayBoard(row, col) == 'A'){
		cout << "HIT!" << endl;
		player.markPlayBoard(row, col, '*');
		computer.markOppBoard(row, col, '*');
		if (computer.getShips(0) == 5){
			cout << "Your Aircraft carrier was sunk" << endl;
			
		}
	}
	else if (player.getPlayBoard(row, col) == 'B'){
		cout << "HIT!" << endl;
		player.markPlayBoard(row, col, '*');
		computer.markOppBoard(row, col, '*');
		if (computer.getShips(1) == 4){
			cout << "Your Battleship was sunk" << endl;
			
		}
	}
	else if (player.getPlayBoard(row, col) == 'D'){
		cout << "HIT!" << endl;
		player.markPlayBoard(row, col, '*');
		computer.markOppBoard(row, col, '*');
		if (computer.getShips(2) == 3){
			cout << "Your Destroyer was sunk" << endl;
			
		}
	}
	else if (player.getPlayBoard(row, col) == 'S'){
		cout << "HIT!" << endl;
		player.markPlayBoard(row, col, '*');
		computer.markOppBoard(row, col, '*');
		if (computer.getShips(3) == 3){
			cout << "Your Submarine was sunk" << endl;
			
		}
	}
	else if (player.getPlayBoard(row, col) == 'P'){
		cout << "HIT!" << endl;
		player.markPlayBoard(row, col, '*');
		computer.markOppBoard(row, col, '*');
		if (computer.getShips(4) == 2){
			cout << "Your Patrol Boat was sunk" << endl;
			
		}
	}
	else if (player.getPlayBoard(row, col) == ' '){
		cout << "MISS!" << endl;
		player.markPlayBoard(row, col, '-');
	}
}

//reveal sunken ship function
void Game::reveal(char letter){
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			if (computer.getPlayBoard(i, j) == letter){
				player.markOppBoard(i, j, letter);
			}
		}
	}	
}

//AI function
void Game::AI(int &row, int &col){
	int fire;
	
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){

			if (player.getPlayBoard(i, j) == 'A' || player.getPlayBoard(i, j) == 'D' || player.getPlayBoard(i, j) == 'S' || player.getPlayBoard(i, j) == 'B' || player.getPlayBoard(i, j) == 'P'){
				if (j < 1 && j >= 0 && i < 1 && i >= 0){
					do {
						fire = rand() % 9;

						if (fire == 0){
							row = i;
							col = j;
						}
						else if (fire == 1){
							row = i;
							col = j + 1;
						}
						else if (fire == 2){
							row = i;
							col = j + 2;
						}
						else if (fire == 3){
							row = i + 1;
							col = j;
						}
						else if (fire == 4){
							row = i + 1;
							col = j + 1;
						}
						else if (fire == 5){
							row = i + 1;
							col = j + 2;
						}
						else if (fire == 6){
							row = i + 2;
							col = j;
						}
						else if (fire == 7){
							row = i + 2;
							col = j + 1;
						}
						else if (fire == 8){
							row = i + 2;
							col = j + 2;
						}

					} while (player.getPlayBoard(row, col) == '*' || player.getPlayBoard(row, col) == '-');
				}
				else if (j > 8 && j <= 9 && i < 1 && i >= 0){
					do {
						fire = rand() % 9;

						if (fire == 0){
							row = i;
							col = j;
						}
						else if (fire == 1){
							row = i;
							col = j - 1;
						}
						else if (fire == 2){
							row = i;
							col = j - 2;
						}
						else if (fire == 3){
							row = i + 1;
							col = j;
						}
						else if (fire == 4){
							row = i + 1;
							col = j - 1;
						}
						else if (fire == 5){
							row = i + 1;
							col = j - 2;
						}
						else if (fire == 6){
							row = i + 2;
							col = j;
						}
						else if (fire == 7){
							row = i + 2;
							col = j - 1;
						}
						else if (fire == 8){
							row = i + 2;
							col = j - 2;
						}
					} while (player.getPlayBoard(row, col) == '*' || player.getPlayBoard(row, col) == '-');
				}
				else if (j < 1 && j >= 0 && i >8 && i <= 9){
					do {
						fire = rand() % 9;

						if (fire == 0){
							row = i;
							col = j;
						}
						else if (fire == 1){
							row = i;
							col = j + 1;
						}
						else if (fire == 2){
							row = i;
							col = j + 2;
						}
						else if (fire == 3){
							row = i - 1;
							col = j;
						}
						else if (fire == 4){
							row = i - 1;
							col = j + 1;
						}
						else if (fire == 5){
							row = i - 1;
							col = j + 2;
						}
						else if (fire == 6){
							row = i - 2;
							col = j;
						}
						else if (fire == 7){
							row = i - 2;
							col = j + 1;
						}
						else if (fire == 8){
							row = i - 2;
							col = j + 2;
						}
					} while (player.getPlayBoard(row, col) == '*' || player.getPlayBoard(row, col) == '-');
				}
				else if (j > 8 && j <= 9 && i > 8 && i <= 9){
					do {
						fire = rand() % 9;

						if (fire == 0){
							row = i;
							col = j;
						}
						else if (fire == 1){
							row = i;
							col = j - 1;
						}
						else if (fire == 2){
							row = i;
							col = j - 2;
						}
						else if (fire == 3){
							row = i - 1;
							col = j;
						}
						else if (fire == 4){
							row = i - 1;
							col = j - 1;
						}
						else if (fire == 5){
							row = i - 1;
							col = j - 2;
						}
						else if (fire == 6){
							row = i - 2;
							col = j;
						}
						else if (fire == 7){
							row = i - 2;
							col = j - 1;
						}
						else if (fire == 8){
							row = i - 2;
							col = j - 2;
						}
					} while (player.getPlayBoard(row, col) == '*' || player.getPlayBoard(row, col) == '-');
				}
				else if ((j < 1 && j >= 0) && (i > 0 && i < 9)){
					do {
						fire = rand() % 9;

						if (fire == 0){
							row = i;
							col = j;
						}
						else if (fire == 1){
							row = i;
							col = j + 1;
						}
						else if (fire == 2){
							row = i;
							col = j + 2;
						}
						else if (fire == 3){
							row = i + 1;
							col = j;
						}
						else if (fire == 4){
							row = i + 1;
							col = j + 1;
						}
						else if (fire == 5){
							row = i + 1;
							col = j + 2;
						}
						else if (fire == 6){
							row = i - 1;
							col = j;
						}
						else if (fire == 7){
							row = i - 1;
							col = j + 1;
						}
						else if (fire == 8){
							row = i - 1;
							col = j + 2;
						}
					} while (player.getPlayBoard(row, col) == '*' || player.getPlayBoard(row, col) == '-');
				}
				else if ((j > 8 && j <= 9) && (i > 0 && i < 9)){
					do {
						fire = rand() % 9;

						if (fire == 0){
							row = i;
							col = j;
						}
						else if (fire == 1){
							row = i;
							col = j - 1;
						}
						else if (fire == 2){
							row = i;
							col = j - 2;
						}
						else if (fire == 3){
							row = i + 1;
							col = j;
						}
						else if (fire == 4){
							row = i + 1;
							col = j - 1;
						}
						else if (fire == 5){
							row = i + 1;
							col = j - 2;
						}
						else if (fire == 6){
							row = i - 1;
							col = j;
						}
						else if (fire == 7){
							row = i - 1;
							col = j - 1;
						}
						else if (fire == 8){
							row = i - 1;
							col = j - 2;
						}
					} while (player.getPlayBoard(row, col) == '*' || player.getPlayBoard(row, col) == '-');
				}
				else if ((i > 8 && i <= 9) && (j > 0 && j < 9)){
					do {
						fire = rand() % 9;

						if (fire == 0){
							row = i;
							col = j;
						}
						else if (fire == 1){
							row = i;
							col = j + 1;
						}
						else if (fire == 2){
							row = i;
							col = j - 1;
						}
						else if (fire == 3){
							row = i - 1;
							col = j;
						}
						else if (fire == 4){
							row = i - 1;
							col = j + 1;
						}
						else if (fire == 5){
							row = i - 1;
							col = j - 1;
						}
						else if (fire == 6){
							row = i - 2;
							col = j;
						}
						else if (fire == 7){
							row = i - 2;
							col = j + 1;
						}
						else if (fire == 8){
							row = i - 2;
							col = j - 1;
						}
					} while (player.getPlayBoard(row, col) == '*' || player.getPlayBoard(row, col) == '-');
				}
				else if ((i < 1 && i >= 0) && (j > 0 && j < 9)){
					do {
						fire = rand() % 9;

						if (fire == 0){
							row = i;
							col = j;
						}
						else if (fire == 1){
							row = i;
							col = j + 1;
						}
						else if (fire == 2){
							row = i;
							col = j - 1;
						}
						else if (fire == 3){
							row = i + 1;
							col = j;
						}
						else if (fire == 4){
							row = i + 1;
							col = j + 1;
						}
						else if (fire == 5){
							row = i + 1;
							col = j - 1;
						}
						else if (fire == 6){
							row = i + 2;
							col = j;
						}
						else if (fire == 7){
							row = i + 2;
							col = j + 1;
						}
						else if (fire == 8){
							row = i + 2;
							col = j - 1;
						}
					} while (player.getPlayBoard(row, col) == '*' || player.getPlayBoard(row, col) == '-');
				}
				else if ((j > 0 && j < 9) && (i > 0 && i < 9)){
					do {
						fire = rand() % 9;

						if (fire == 0){
							row = i;
							col = j;
						}
						else if (fire == 1){
							row = i;
							col = j + 1;
						}
						else if (fire == 2){
							row = i;
							col = j - 1;
						}
						else if (fire == 3){
							row = i + 1;
							col = j;
						}
						else if (fire == 4){
							row = i + 1;
							col = j + 1;
						}
						else if (fire == 5){
							row = i + 1;
							col = j - 1;
						}
						else if (fire == 6){
							row = i - 1;
							col = j;
						}
						else if (fire == 7){
							row = i - 1;
							col = j - 1;
						}
						else if (fire == 8){
							row = i - 1;
							col = j + 1;
						}
					} while (player.getPlayBoard(row, col) == '*' || player.getPlayBoard(row, col) == '-');
				}

				j = 9;
				i = 9;
			}
		}
	}
}

//end reveal function
void Game::endReveal(){
	char ships[] = {'A','B','D','S','P'};
	int count[] = { 5, 4, 3, 3, 2 };

	for (int i = 0; i < 5; i++){
		if (player.getShips(i) != count[i]){
			reveal(ships[i]);
		}
	}
}