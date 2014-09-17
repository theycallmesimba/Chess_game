//Copyright Brandon Buonacorsi 
//Date: 4/10/2014
//Property of Turtle Labs Inc.

#include <iostream>
#include <cctype>
#include "board.h"
#include "piece.h"
#include "moves.h"

Board::Board()
{
	//Constructs the first board and initializes
	//a 2D array with 32 pieces
}   //Board()

Board::~Board()
{
	//Desconstructs board
}   //~Board()

void Board::initializePieces(void)
{
	//Go through for each player and initialize
	//all of their 16 pieces
	for(int i = 0; i < 8; i++)
	{
		pieces[i].initialize("pawn", i + 8, 2);
	}
	pieces[8].initialize("rook", 0, 2);
	pieces[9].initialize("knight", 1, 2);
	pieces[10].initialize("bishop", 2, 2);
	pieces[11].initialize("king", 3, 2);
	pieces[12].initialize("queen", 4, 2);
	pieces[13].initialize("bishop", 5, 2);
	pieces[14].initialize("knight", 6, 2);
	pieces[15].initialize("rook", 7, 2);
	for(int i = 16; i < 24; i++)
	{
		pieces[i].initialize("pawn", i+32, 1);
	}
	pieces[24].initialize("rook", 56, 1);
	pieces[25].initialize("knight", 57, 1);
	pieces[26].initialize("bishop", 58, 1);
	pieces[27].initialize("king", 59, 1);
	pieces[28].initialize("queen", 60, 1);
	pieces[29].initialize("bishop", 61, 1);
	pieces[30].initialize("knight", 62, 1);
	pieces[31].initialize("rook", 63, 1);
}   //initializePieces()

void Board::setBlank(void)
{
	//Initialize the board first to be blank
	//which will allow to insert the pieces after
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			boardPos[i][j] = '*';
		}
	}
}   //setBlankBoard()

void Board::display(void)
{
	//Displays the boardPos array in its 2D representation
	cout << endl;
	cout << "      ABCDEFGH" << endl;
	for(int i = 0; i < 8; i++)
	{
		cout << "    " << 8-i << " ";
		
		for(int j = 0; j < 8; j++)
		{
			cout << boardPos[i][j]; 
		}
		cout << endl;
	}
	cout << endl;
}	//display()

void Board::update(void)
{
	//Updates the boardPos array with the most recent
	//positions of each players pieces
	int pos, row, col;
	char letter;
	
	for(int i = 0; i < 32; i++)
	{  
		//Checks if pieces are alive or not
		if(pieces[i].getAlive() == false){continue;}
		pos = pieces[i].getPosition();
		row = pos/8;
		col = pos%8;
		letter = pieces[i].getDisplayLetter();
		boardPos[row][col] = letter;
	}
}	//update()

int Board::getPieceIndex(int pos)
{
	for(int i = 0; i < 32; i++)
	{
		if(pieces[i].getPosition() == pos)
		{
			//Makes sure any pieceID returned is alive
			if(pieces[i].getAlive() == false)
			{
				continue;
			}
			return i;
		}
	}

	return -1;
}	//getPieceIndex()

void Board::setPiecePosition(int i, int newPos)
{
	pieces[i].setPosition(newPos);
}	//setPiecePosition()

int Board::getPlayer(int i)
{
	return pieces[i].getPlayer();
}	//getPlayer()

void Board::killPiece(int i)
{
	pieces[i].killPiece();
}	//killPiece()

bool Board::getAliveStatus(int pieceID)
{
	return pieces[pieceID].getAlive();
}	//getAliveStatus()

bool Board::checkValidMove(int i, int newPos)
{
	string type;
	int oldPos, player;
	bool isValid;

	type = pieces[i].getPieceType();
	oldPos = pieces[i].getPosition();
	player = pieces[i].getPlayer();

	if(type == "pawn"){isValid = moves.pawn(player, oldPos, newPos, pieces);}
	if(type == "rook"){isValid = moves.rook(oldPos, newPos, pieces);}
	if(type == "knight"){isValid = moves.knight(oldPos, newPos, pieces);}
	if(type == "bishop"){isValid = moves.bishop(oldPos, newPos, pieces);}
	if(type == "king"){isValid = moves.king(oldPos, newPos, pieces);}
	if(type == "queen"){isValid = moves.queen(oldPos, newPos, pieces);}

	return isValid;
}	//checkValidMove()

int Board::checkCheck(int curplyr)
{
	int kingloc;
	
	if(curplyr == 1)
	{
		//27 is 1st player's king ID
		kingloc = pieces[27].getPosition();
	}
	if(curplyr == 2)
	{
		//11 is 2nd player's king ID
		kingloc = pieces[11].getPosition();
	}
	for(int i = 0; i < 32; i++)
	{
		//skip over pieces that are curplyr's..
		if(pieces[i].getPlayer() == curplyr){continue;}
		//return 1 for check
		if(checkValidMove(i, kingloc)){return 1;}
	}
	
	return 0;
} //checkCheck()