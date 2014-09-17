//Copyright Brandon Buonacorsi 
//Date: 12/21/2013
//Property of Turtle Labs Inc.

#include <iostream>
#include "piece.h"

Piece::Piece(void)
{
	//Constructs a piece which has three attributes:
	//type, position, player
}  	//Piece()

Piece::~Piece()
{
	//Deconstructs piece
} 	//~Piece()

void Piece::initialize(string type, int pos, int plyr)
{
	//Sets the pieces values
	alive = true;
	pieceType = type;
	position = pos;
	player = plyr;
}  	//initialize()

void Piece::setPosition(int newPos)
{
	position = newPos;
}	//setPosition()

string Piece::getPieceType(void)
{
	return(pieceType);
}   //getPieceType()

int Piece::getPosition(void)
{
	return(position);
}  	//getPosition()

int Piece::getPlayer(void)
{
	return(player);
}   //getPlayer()

char Piece::getDisplayLetter(void)
{
	//Simply returns the right letter display for the board
	char let;
	
	if(pieceType == "pawn"){let = 'p';}
	if(pieceType == "rook"){let = 'r';}
	if(pieceType == "knight"){let = 'n';}
	if(pieceType == "bishop"){let = 'b';}
	if(pieceType == "queen"){let = 'q';}
	if(pieceType == "king"){let = 'k';}
	if(player == 2)
	{
		let = toupper(let);
	}
	
	return let;
}	//getLetter()

bool Piece::getAlive(void)
{
	return alive;
}	//getAlive()

void Piece::killPiece(void)
{
	alive = false;
}	//killPiece()