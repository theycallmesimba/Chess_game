//Copyright Brandon Buonacorsi 
//Date: 4/10/2014
//Property of Turtle Labs Inc.

#ifndef movesH
#define movesH
#include "moves.h"

class Moves
{
public:
	Moves();
	~Moves();
	bool pawn(int player, int oldPos, int newPos, Piece pieces[32]);
	bool knight(int oldPos, int newPos, Piece pieces[32]);
	bool king(int oldPos, int newPos, Piece pieces[32]);
	bool rook(int oldPos, int newPos, Piece pieces[32]);
	bool bishop(int oldPos, int newPos, Piece pieces[32]);
	bool queen(int oldPos, int newPos, Piece pieces[32]);
}; //Class Moves
#endif