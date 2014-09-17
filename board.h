//Copyright Brandon Buonacorsi 
//Date: 4/10/2014
//Property of Turtle Labs Inc.

#ifndef boardH
#define boardH
#include "piece.h"
#include "moves.h"

class Board
{
	char boardPos[8][8];
	Piece pieces[32]; 
	Moves moves;
public:
	Board();
	~Board();
	void initializePieces(void);
	void setBlank(void);
	void display(void);
	void update(void);
	int getPieceIndex(int pos);
	void setPiecePosition(int i, int newPos);
	int getPlayer(int i);
	void killPiece(int i);
	bool getAliveStatus(int pieceID);
	bool checkValidMove(int i, int newPos);
	int checkCheck(int curplyr);
};  //Class Board
#endif
