//Copyright Brandon Buonacorsi 
//Date: 4/10/2014
//Property of Turtle Labs Inc.

#include <iostream>
#include <string>
#include "board.cpp"
#include "piece.cpp"
#include "moves.cpp"
using namespace std;

void welcomeScreen(void);
void playerTurn(Board* board, int player);
int getPosition(string pieceInput);
int returnPieceIndex(Board* board, int player);
int returnNewPosition(Board* board, int pieceIndex, int player);

int main()
{
	//Initialize game start sequence
	welcomeScreen();
	Board board;
	board.initializePieces();
	board.setBlank();
	board.update();

	//Loop through player turns until there is a winner
	while(1)
	{
		playerTurn(&board, 1);
		//Check king status of player 1
		if(!board.getAliveStatus(27))
		{
			cout << "Player 1 has won the game!!! Congrats!" << endl;
			break;
		}
		playerTurn(&board, 2);
		//Check king status of player 2
		if(!board.getAliveStatus(11))
		{
			cout << "Player 2 has won the game!!! Congrats!" << endl;
			break;
		}
	}

	return 0;
}  	//main()

void welcomeScreen(void)
{
	//Displays a simple welcome screen of text
	cout << endl << "Welcome to Chess!" << endl;
	cout << "Player 1 will be designated by lowercase letters.\n";
	cout << "Player 2 will be designated by uppercase letters.\n";
	cout << "\nHit enter to begin the game.";
	//Waits for user to hit enter
	cin.ignore(1);
}  	//welcomeScreen()

void playerTurn(Board* board, int player)
{
	//A player's general turn sequence
	int newPosition, pieceIndex;
	
	cout << endl << "Player " << player << "'s turn:" << endl;
	
	//Check for check/checkmate
	//Returns 1 for check, 2 for mate, 0 else
	if(board->checkCheck(player) == 1)
	{
		cout << "***You are in check***\n";
	}
	if(board->checkCheck(player) == 2)
	{
		cout << "***You are in checkmate***\n";
		//Kill player's king
		if(player == 2){board->pieces[11].killPiece();}
		if(player == 1){board->pieces[27].killPiece();}
		return;
	}

	//Display current board
	board->display();
	while(1)
	{
		pieceIndex = returnPieceIndex(board, player);
		newPosition = returnNewPosition(board, pieceIndex, player);
		if(newPosition != 100){break;}
	}
	//Moves the piece's position ont the board
	board->setPiecePosition(pieceIndex, newPosition);
	//Reset blank board
	board->setBlank();
	//Update board with all the pieces current positions
	//This updates the moved piece's new position
	board->update();
}	//playerTurn()

int getPosition(string pieceInput)
{
	//Takes the inputed position string and converts
	//it to the appropriate position number
	int pos;

	for(int i = 0; i < 26; i++)
	{
		//The two upper lets you put in lower case positions
		if(toupper(pieceInput[0]) == 'A' + i)
		{
			pos = 8*(8-(pieceInput[1] - '0')) + (i+1);
		}
	}

	if(pieceInput.length() > 2){pos = 100;}
	if(pieceInput[1] - '0' > 8){pos = 100;}
	if(pieceInput[1] - '0' < 1){pos = 100;}

	//For some reason, returning pos-1 makes it work...
	//Otherwise it moves the wrong piece
	return pos-1;
}	//getPosition()

//Gets piece ID that the player wants to move
int returnPieceIndex(Board* board, int player)
{
	string pieceInput;
	bool validChoice;
	int oldPosition, pieceID;

	cout << "Enter piece to move (e.x. C2): ";
	while(validChoice != true)
	{
		//Get user input to move a piece
		cin >> pieceInput;
		//Convert input into a position #
		oldPosition = getPosition(pieceInput);
		//Make sure position is on board
		if(oldPosition >= 64)
		{
			cout << "Pick a valid spot on the board! Repick: ";
			continue;
		}
		//Use position to find the piece ID at the position
		pieceID = board->getPieceIndex(oldPosition);
		//Check to make sure piece selection is valid
		if(pieceID == -1)
		{
			cout << "There is no piece in that space! Repick: ";
			continue;
		}
		if(board->getPlayer(pieceID) != player)
		{
			cout << "That is not your piece to move! Repick: ";
			continue;
		}
		validChoice = true;
	}

	return pieceID;
}	//returnPieceIndex()

//Gets the new position to move the piece to 
int returnNewPosition(Board* board, int pieceIndex, int player)
{
	string positionInput;
	bool validChoice = false;
	int newPosition, pieceID;

	cout << "Enter location to move piece to\n(Enter 00 to undo piece choice): ";
	while(validChoice != true)
	{
		//Get user input for new location
		cin >> positionInput;
		//Allow for player to undo their pieceID choice
		if(positionInput[0] == '0' && positionInput[1] == '0')
		{
			//100 is an arbitrary number
			return 100;
		}
		//Convert user input to position #
		newPosition = getPosition(positionInput);
		//Make sure position is on board
		if(newPosition >= 64)
		{
			cout << "Pick a valid spot on the board! Repick: ";
			continue;
		}
		pieceID = board->getPieceIndex(newPosition);
		//Checks for valid move
		if(board->checkValidMove(pieceIndex, newPosition) != true)
		{
			cout << "Your piece cannot move that way! Repick: ";
			continue;
		}
		//Checks if space is occuped
		if(pieceID != -1)
		{
			if(board->getPlayer(pieceID) == player)
			{
				cout << "You cannot take your own piece! Repick: ";
				continue;
			}
			if(board->getPlayer(pieceID) != player)
			{
				board->killPiece(pieceID);
				validChoice = true;
				continue;
			}
		}
		validChoice = true;
	}

	return newPosition;
}	//returnNewPosition()