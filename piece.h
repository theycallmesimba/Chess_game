//Copyright Brandon Buonacorsi 
//Date: 12/21/2013
//Property of Turtle Labs Inc.

#ifndef pieceH
#define pieceH
#include <string>
using namespace std;

class Piece
{
	bool alive;
	string pieceType;
	int position;
	int player;
public:
	Piece();
	~Piece();
	void initialize(string type, int pos, int plyr);
	void setPosition(int newPos);
	string getPieceType(void);
	int getPosition(void);
	int getPlayer(void);
	char getDisplayLetter(void);
	bool getAlive(void);
	void killPiece(void);
};  //Class Piece
#endif