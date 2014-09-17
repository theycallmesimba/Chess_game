//Copyright Brandon Buonacorsi 
//Date: 4/10/2014
//Property of Turtle Labs Inc.

#include <iostream>
#include <cctype>
#include "moves.h"

Moves::Moves()
{
	//Constructs the moves class with function to check
	//for valid piece movements
}   //Moves()

Moves::~Moves()
{
	//Desconstructs Moves
}   //~Moves()

bool Moves::pawn(int player, int oldPos, int newPos, Piece pieces[])
{
	int oldRow, oldCol, newRow, newCol;

	oldRow = oldPos/8;
	oldCol = oldPos%8;
	newRow = newPos/8;
	newCol = newPos%8;

	if(player == 2)
	{
		//Checks to make sure pawn is moving only forward one space
		if(oldRow+1 == newRow && oldCol == newCol)
		{
			for(int i = 0; i < 32; i++)
			{	
				//Check so pawn doesn't move through a piece
				if((newRow)*8+newCol == pieces[i].getPosition()) 
				{return false;}
			}
			return true;
		}
		//Checks if pawn is moving only forward two spaces
		if(oldRow+2 == newRow && oldCol == newCol && oldRow == 1)
		{
			for(int i = 0; i < 32; i++)
			{	
				//Check so pawn doesn't move through a piece
				if(((newRow)*8+newCol == pieces[i].getPosition()) ||
					((newRow-1)*8+newCol == pieces[i].getPosition()))
				{return false;}
			}
			return true;
		}
		//Checks for diagonal attack movement
		if((oldCol+1 == newCol && oldRow+1 == newRow) ||
			(oldCol-1 == newCol && oldRow+1 == newRow))
		{
			//Checks to make sure there is a piece to attack
			for(int i = 0; i < 32; i++)
			{
				if(newPos == pieces[i].getPosition())
				{return true;}
			}
			return false;
		}
		return false;
	}
	if(player == 1)
	{
		//Checks to make sure pawn is moving only forward one space
		if(oldRow-1 == newRow && oldCol == newCol)
		{
			for(int i = 0; i < 32; i++)
			{	
				//Check so pawn doesn't move through a piece
				if((newRow)*8+newCol == pieces[i].getPosition()) 
				{return false;}
			}
			return true;
		}
		//Checks if pawn is moving only forward two spaces
		if(oldRow-2 == newRow && oldCol == newCol && oldRow == 6)
		{
			for(int i = 0; i < 32; i++)
			{	
				//Check so pawn doesn't move through a piece
				if(((newRow)*8+newCol == pieces[i].getPosition()) ||
					((newRow+1)*8+newCol == pieces[i].getPosition()))
				{return false;}
			}
			return true;
		}
		//Checks for diagonal attack movement
		if((oldCol+1 == newCol && oldRow-1 == newRow) ||
			(oldCol-1 == newCol && oldRow-1 == newRow))
		{
			//Checks to make sure there is a piece to attack
			for(int i = 0; i < 32; i++)
			{
				if(newPos == pieces[i].getPosition())
				{return true;}
			}
			return false;
		}
		return false;
	}
}	//pawn()

bool Moves::knight(int oldPos, int newPos, Piece pieces[])
{
	int oldRow, oldCol, newRow, newCol;

	oldRow = oldPos/8;
	oldCol = oldPos%8;
	newRow = newPos/8;
	newCol = newPos%8;

	//Checks for knight's 8 degrees of freedom
	if((oldRow+2 == newRow && oldCol-1 == newCol) ||
		(oldRow+2 == newRow && oldCol+1 == newCol) ||
		(oldRow+1 == newRow && oldCol+2 == newCol) ||
		(oldRow-1 == newRow && oldCol+2 == newCol) ||
		(oldRow-2 == newRow && oldCol+1 == newCol) ||
		(oldRow-2 == newRow && oldCol-1 == newCol) ||
		(oldRow-1 == newRow && oldCol-2 == newCol) ||
		(oldRow+1 == newRow && oldCol-2 == newCol))
	{
		return true;
	}

	return false;
}	//knight()

bool Moves::king(int oldPos, int newPos, Piece pieces[])
{	
	//Checks for king's 8 degrees of freedom
	return ((oldPos+1 == newPos) ||
		(oldPos-1 == newPos) ||
		(oldPos+8 == newPos) ||
		(oldPos-8 == newPos) ||
		(oldPos+7 == newPos) ||
		(oldPos-7 == newPos) ||
		(oldPos+9 == newPos) ||
		(oldPos-9 == newPos));
}	//king()

bool Moves::rook(int oldPos, int newPos, Piece pieces[])
{
	int oldRow, oldCol, newRow, newCol;

	oldRow = oldPos/8;
	oldCol = oldPos%8;
	newRow = newPos/8;
	newCol = newPos%8;
	
	for(int i = 1; i < 8; i++)
	{
		//Checks for just row movement
		//Checks that no piece is in the way
		if((oldRow+i == newRow || oldRow-i == newRow)
		 	&& oldCol == newCol)
		{
			for(int j = 1; j < i; j++)
			{
				for(int k = 0; k < 32; k++)
				{	
					if(((oldRow+j)*8 + oldCol) == pieces[k].getPosition() ||
						((oldRow-j)*8 + oldCol) == pieces[k].getPosition())
					{
						return false;
					}
				}
			}
			return true;
		}
		//Checks for just column movement
		//Checks that no piece is in the way
		if((oldCol+i == newCol || oldCol-i == newCol) 
			&& oldRow == newRow)
		{
			for(int j = 1; j < i; j++)
			{
				for(int k = 0; k < 32; k++)
				{	
					if(((oldRow)*8 + oldCol + j) == pieces[k].getPosition() ||
						((oldRow)*8 + oldCol + j) == pieces[k].getPosition())
					{
						return false;
					}
				}
			}
			return true;
		}
	}
	
	return false;
}	//rook()

bool Moves::bishop(int oldPos, int newPos, Piece pieces[])
{
	int dist, isValid=1;

	// diagonal path will have |oldPos-newPos| mods 7 or 9 = to 0
	// check every piece's position, comparing it to current position i on bishop's path
	// set isValid to 0 if conflicting position is found

	if(oldPos<newPos) {
		dist = newPos-oldPos;
		if(dist%7 == 0)
		{
			for(int i=oldPos+7; i<newPos; i+=7)
			{
				for(int j=0; j<32; j++) {
					if(pieces[j].getPosition() == i)
						isValid = 0;
				}
				return isValid;
			}
			//this return accounts for cases of 
			//just moving one diagonal space
			return isValid;
		}
		if(dist%9 == 0)
		{
			for(int i=oldPos+9; i<newPos; i+=9)
			{
				for(int j=0; j<32; j++) {
					if(pieces[j].getPosition() == i)
						isValid = 0;
				}
				return isValid;
			}
			return isValid;
		}		
	}

	if(oldPos>newPos) {
		dist = oldPos-newPos;
		if(dist%7 == 0)
		{
			for(int i=oldPos-7; i>newPos; i-=7)
			{
				for(int j=0; j<32; j++) {
					if(pieces[j].getPosition() == i)
						isValid = 0;
				}
				return isValid;
			}
			return isValid;
		}
		if(dist%9 == 0)
		{
			for(int i=oldPos-9; i>newPos; i-=9)
			{
				for(int j=0; j<32; j++) {
					if(pieces[j].getPosition() == i)
						isValid = 0;
				}
				return isValid;
			}
			return isValid;
		}
	}

	// not valid position
	return false;
}	//bishop()

bool Moves::queen(int oldPos, int newPos, Piece pieces[])
{
	return rook(oldPos, newPos, pieces) || bishop(oldPos, newPos, pieces);
}	//queen()