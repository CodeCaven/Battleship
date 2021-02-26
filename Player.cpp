#include "Player.h"
#include "Game.h"


//default constructor for computer
Player::Player(){
	playerName = "Computer";

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			playerBoard[i][j] = ' ';
			oppBoard[i][j] = ' ';
		}
	}
	randomBoard();

	for (int i = 0; i < 5; i++){
		ships[i] = 0;
	}
}

//constructor for player
Player::Player(string name){
	playerName = name;

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			playerBoard[i][j] = ' ';
			oppBoard[i][j] = ' ';
		}
	}

	for (int i = 0; i < 5; i++){
		ships[i] = 0;
	}
}

//display board function
void Player::displayBoard(string select,bool cheat){
	
	const int COL = 10;
	const int ROW = 10;
	int count;
	int top[10];
	char bottom[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

	if (select == "player"){
		if (cheat){
			cout << " ***COMPUTERS FLEET***" << endl << endl;
		}
		else{
			cout << "***YOUR FLEET***" << endl << endl;
		}
	}
	else{
		cout << "***HITS AND MISSES***" << endl << endl;
	}

	cout << "   ";
	for (int i = 0; i < 10; i++){
		top[i] = i;
		cout << top[i] << "  ";
	}
	cout << endl;

	for (int i = 0; i < ROW; i++){
		count = 0;
		cout << bottom[i] << "  ";
		for (int j = 0; j < COL; j++){
			if (select == "player"){
				cout << playerBoard[i][j] << "  ";
			}
			else if (select == "opp"){
				cout << oppBoard[i][j] << "  ";
			}
			count++;
			if (count == 10){
				cout << endl << endl;
			}
		}
	}
}

//change board function
void Player::changeBoard(char letter, int row, int col, char arrow,int off){
	playerBoard[row][col] = letter;
	if (arrow == 'u'){
		for (int i = 1; i < (5 - off); i++){
			playerBoard[row - i][col] = letter;
		}
	}
	else if (arrow == 'd'){
		for (int i = 1; i < (5 - off); i++){
			playerBoard[row + i][col] = letter;
		}
	}
	else if (arrow == 'r'){
		for (int i = 1; i < (5 - off); i++){
			playerBoard[row][col + i] = letter;
		}
	}
	else if (arrow == 'l'){
		for (int i = 1; i < (5 - off); i++){
			playerBoard[row][col - i] = letter;
		}
	}
}

//random board function 
void Player::randomBoard(){
	
	int row;
	int col;
	int idirection;
	int offset[] = { 0, 1, 2, 2, 3 };
	char letter[] = { 'A', 'B', 'S', 'D', 'P' }; 
	char cdirection;
	bool loop;
	bool valid = false;
	
	srand(time(NULL));
	for (int i = 0; i < 5; i++){
		loop = true;
		while (loop){
			
			row = rand() % 10;
			col = rand() % 10;
			
			if (playerBoard[row][col] != 'A' || playerBoard[row][col] != 'B' || playerBoard[row][col] != 'D' || playerBoard[row][col] != 'S' || playerBoard[row][col] != 'P' ){
				if (col < (4 - offset[i]) && col >= 0 && row < (4 - offset[i]) && row >= 0){
					idirection = rand() % 2;
					if (idirection == 0){
						cdirection = 'd';
					}
					else if (idirection == 1){
						cdirection = 'r';
					}
					if (!checkBoard(row, col, offset[i], cdirection)){
						changeBoard(letter[i], row, col, cdirection, offset[i]);
						loop = false;
					}
				}
					
				else if (col > (5 + offset[i]) && col <= 9 && row < (4 - offset[i]) && row >= 0){
					idirection = rand() % 2;
					if (idirection == 0){
						cdirection = 'd';
					}
					else if (idirection == 1){
						cdirection = 'l';
					}
					if (!checkBoard(row, col, offset[i], cdirection)){
						changeBoard(letter[i], row, col, cdirection, offset[i]);
						loop = false;
					}
				}
				else if (col < (4 - offset[i]) && col >= 0 && row >(5 + offset[i]) && row <= 9){
					idirection = rand() % 2;
					if (idirection == 0){
						cdirection = 'u';
					}
					else if (idirection == 1){
						cdirection = 'r';
					}
					if (!checkBoard(row, col, offset[i], cdirection)){
						changeBoard(letter[i], row, col, cdirection, offset[i]);
						loop = false;
					}
				}
				else if (col > (5 + offset[i]) && col <= 9 && row > (5 + offset[i]) && row <= 9){
					idirection = rand() % 2;
					if (idirection == 0){
						cdirection = 'u';
					}
					else if (idirection == 1){
						cdirection = 'l';
					}
					if (!checkBoard(row, col, offset[i], cdirection)){
						changeBoard(letter[i], row, col, cdirection, offset[i]);
						loop = false;
					}
				}
				else if (col < (4 - offset[i]) && col >= 0 && row >(3 - offset[i]) && row < (6 + offset[i])){
					idirection = rand() % 3;
					if (idirection == 0){
						cdirection = 'd';
					}
					else if (idirection == 1){
						cdirection = 'r';
					}
					else if (idirection == 2){
						cdirection = 'u';
					}

					if (!checkBoard(row, col, offset[i], cdirection)){
						changeBoard(letter[i], row, col, cdirection, offset[i]);
						loop = false;
					}
				}
				else if (col > (5 + offset[i]) && col <= 9 && row > (3 - offset[i]) && row < (6 + offset[i])){
					idirection = rand() % 3;
					if (idirection == 0){
						cdirection = 'd';
					}
					else if (idirection == 1){
						cdirection = 'l';
					}
					else if (idirection == 2){
						cdirection = 'u';
					}

					if (!checkBoard(row, col, offset[i], cdirection)){
						changeBoard(letter[i], row, col, cdirection, offset[i]);
						loop = false;
					}
				}
				else if (col > (3 - offset[i]) && col < (6 + offset[i]) && row < (5 + offset[i]) && row <= 0){
					idirection = rand() % 3;
					if (idirection == 0){
						cdirection = 'l';
					}
					else if (idirection == 1){
						cdirection = 'r';
					}
					else if (idirection == 2){
						cdirection = 'u';
					}

					if (!checkBoard(row, col, offset[i], cdirection)){
						changeBoard(letter[i], row, col, cdirection, offset[i]);
						loop = false;
					}
				}
				else if (col > (3 - offset[i]) && col < (6 + offset[i]) && row < (4 - offset[i]) && row >= 0){
					idirection = rand() % 3;
					if (idirection == 0){
						cdirection = 'd';
					}
					else if (idirection == 1){
						cdirection = 'r';
					}
					else if (idirection == 2){
						cdirection = 'l';
					}

					if (!checkBoard(row, col, offset[i], cdirection)){
						changeBoard(letter[i], row, col, cdirection, offset[i]);
						loop = false;
					}
				}
				else if (col > (3 - offset[i]) && col < (6 + offset[i]) && row >(3 - offset[i]) && row < (6 + offset[i])){
					idirection = rand() % 4;
					if (idirection == 0){
						cdirection = 'd';
					}
					else if (idirection == 1){
						cdirection = 'r';
					}
					else if (idirection == 2){
						cdirection = 'l';
					}
					else if (idirection == 2){
						cdirection = 'u';
					}

					if (!checkBoard(row, col, offset[i], cdirection)){
						changeBoard(letter[i], row, col, cdirection, offset[i]);
						loop = false;
					}
				}
												
			}
			
		}
	}
}

//check board function
bool Player::checkBoard(int row, int col, int off, char direction){
	if (direction == 'u'){
		for (int i = 0; i < (5 - off); i++){
			if (playerBoard[row - i][col] != ' '){
				return true;
			}
		}
	}
	else if (direction == 'd'){
		for (int i = 0; i < (5 - off); i++){
			if (playerBoard[row + i][col] != ' '){
				return true;
			}
		}
	}
	else if (direction == 'l'){
		for (int i = 0; i < (5 - off); i++){
			if (playerBoard[row][col - i] != ' '){
				return true;
			}
		}
	}
	else if (direction == 'r'){
		for (int i = 0; i < (5 - off); i++){
			if (playerBoard[row][col + i] != ' '){
				return true;
			}
		}
	}
	return false;
}

//set board function
void Player::setBoard(){
	int irow;
	int icol;
	int offset[] = { 0, 1, 2, 2, 3 };
	char row;
	char col;
	char letter[] = { 'A', 'B', 'S', 'D', 'P' };
	char repeat;
	char direction;
	bool valid;
	bool keep;
	string line[5];
	line[0] = "Where would you like to place your Aircraft Carrier? ";
	line[1] = "Where would you like to place your Battleship? ";
	line[2] = "Where would you like to place your Submarine? ";
	line[3] = "Where would you like to place your Destroyer? ";
	line[4] = "Where would you like to place your Patrol Boat? ";

	for (int i = 0; i < 5; i++){
		cout << line[i] << endl;
		keep = false;
		while (!keep){
			valid = false;
			while (!valid){
				// Input validation
				cout << "Please enter a row " << endl;
				cin.sync();
				row = cin.get();
				cin.sync();
				while (row - 97 < 0 || row - 97 > 9){
					cout << "Enter a row between A and J " << endl;
					row = cin.get();
					cin.sync();
				}
				irow = row - 97;

				cout << "Please enter a column " << endl;
				while (!(cin >> icol) || icol < 0 || icol > 9){
					cout << "Enter a number between 0 and 9 " << endl;
					cin.clear();
					cin.sync();
				}
				// Selection statements 
				if ((playerBoard[irow][icol] == 'A') || (playerBoard[irow][icol] == 'B') || (playerBoard[irow][icol] == 'S') || (playerBoard[irow][icol] == 'D') || (playerBoard[irow][icol] == 'P')){
					cout << "Invalid Selection" << endl;
				}
				else if (icol < (4 - offset[i]) && icol >= 0 && irow < (4 - offset[i]) && irow >= 0){
					cout << endl << "Press D for Down , R for Right ";
					cin.sync();
					direction = cin.get();
					cin.sync();
					while (!(direction == 'd' || direction == 'r')){
						cout << endl << "Press D for Down , R for Right ";
						direction = cin.get();
						cin.sync();
					}
					valid = true;
				}
				else if (icol >(5 + offset[i]) && icol <= 9 && irow < (4 - offset[i]) && irow >= 0){
					cout << endl << "Press D for Down , L for Left ";
					cin.sync();
					direction = cin.get();
					cin.sync();
					while (!(direction == 'd' || direction == 'l')){
						cout << endl << "Press D for Down , L for Left ";
						direction = cin.get();
						cin.sync();
					}
					valid = true;
				}
				else if (icol < (4 - offset[i]) && icol >= 0 && irow >(5 + offset[i]) && irow <= 9){
					cout << endl << "Press U for Up , R for Right ";
					cin.sync();
					direction = cin.get();
					cin.sync();
					while (!(direction == 'u' || direction == 'r')){
						cout << endl << "Press U for Up , R for Right ";
						direction = cin.get();
						cin.sync();
					}
					valid = true;
				}
				else if (icol > (5 + offset[i]) && icol <= 9 && irow > (5 + offset[i]) && irow <= 9){
					cout << endl << "Press U for Up , L for Left ";
					cin.sync();
					direction = cin.get();
					cin.sync();
					while (!(direction == 'u' || direction == 'l')){
						cout << endl << "Press U for Up , L for Left ";
						direction = cin.get();
						cin.sync();
					}
					valid = true;
				}
				else if ((icol < (4 - offset[i]) && icol >= 0) && (irow >(3 - offset[i]) && irow < (6 + offset[i]))){
					cout << endl << "Press U for Up , R for Right , D for Down ";
					cin.sync();
					direction = cin.get();
					cin.sync();
					while (!(direction == 'u' || direction == 'r' || direction == 'd')){
						cout << endl << "Press U for Up , R for Right , D for Down ";
						direction = cin.get();
						cin.sync();
					}
					valid = true;
				}
				else if ((icol >(5 + offset[i]) && icol <= 9) && (irow > (3 - offset[i]) && irow < (6 + offset[i]))){
					cout << endl << "Press U for Up , L for Left , D for Down ";
					cin.sync();
					direction = cin.get();
					cin.sync();
					while (!(direction == 'u' || direction == 'l' || direction == 'd')){
						cout << endl << "Press U for Up , L for Left , D for Down ";
						direction = cin.get();
						cin.sync();
					}
					valid = true;
				}
				else if ((irow >(5 + offset[i]) && irow <= 9) && (icol > (3 - offset[i]) && icol < (6 + offset[i]))){
					cout << endl << "Press U for Up , L for Left , R for Right ";
					cin.sync();
					direction = cin.get();
					cin.sync();
					while (!(direction == 'u' || direction == 'l' || direction == 'r')){
						cout << endl << "Press U for Up , L for Left , R for Right ";
						direction = cin.get();
						cin.sync();
					}
					valid = true;
				}
				else if ((irow < (4 - offset[i]) && irow >= 0) && (icol >(3 - offset[i]) && icol < (6 + offset[i]))){
					cout << endl << "Press L for Left , R for Right , D for Down ";
					cin.sync();
					direction = cin.get();
					cin.sync();
					while (!(direction == 'l' || direction == 'r' || direction == 'd')){
						cout << endl << "Press L for Left , R for Right , D for Down ";
						direction = cin.get();
						cin.sync();
					}
					valid = true;
				}
				else if ((icol >(3 - offset[i]) && icol < (6 + offset[i])) && (irow >(3 - offset[i]) && irow < (6 + offset[i]))){
					cout << endl << "Press L for Left , R for Right , D for Down , U for Up ";
					cin.sync();
					direction = cin.get();
					cin.sync();
					while (!(direction == 'l' || direction == 'r' || direction == 'd' || direction == 'u')){
						cout << endl << "Press L for Left , R for Right , D for Down , U for Up ";
						direction = cin.get();
						cin.sync();
					}
					valid = true;
				}
				else{
					cout << "Invalid selection" << endl;
				}
				// Checks for valid board placements
				if (valid == true){
					if (checkBoard(irow, icol, offset[i] ,direction)){
						valid = false;
						cout << "Invalid Direction" << endl;
					}
				}
				// Confirms users selection or repeats
				if (valid == true){
					changeBoard(letter[i], irow, icol, direction, offset[i]);
					displayBoard("player",false);

					cout << "Is this okay ? ";
					cin.sync();
					repeat = cin.get();
					cin.sync();
					
					if (repeat == 'n'){
						changeBoard(' ', irow, icol, direction, offset[i]);
						displayBoard("player",false);
						valid = false;
					}
					else{
						keep = true;
					}
				}
			}
		}
	}
}

//end game function
bool Player::endGame(){
	if (ships[0] == 5 && ships[1] == 4 && ships[2] == 3 && ships[3] == 3 && ships[4] == 2){
		return true;
	}
	return false;
}

//returns the player board
char Player::getPlayBoard(int row, int col){
	return playerBoard[row][col];
}

//returns the opponents board
char Player::getOppBoard(int row, int col){
	return oppBoard[row][col];
}

//marks the players board
void Player::markPlayBoard(int row, int col, char letter){
	playerBoard[row][col] = letter;
}

//marks the oppenent board
void Player::markOppBoard(int row, int col, char letter){
	oppBoard[row][col] = letter;
}

//returns players name
string Player::getName(){
	return playerName;
}

//changes and returns the ships data member
int Player::getShips(int index){
	ships[index] = ships[index] + 1;
	return ships[index];
}

