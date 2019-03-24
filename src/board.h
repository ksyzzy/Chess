#ifndef BOARD
#define BOARD
#include "figures.h"
#include <iostream>
#include <vector>
#include <string>

class GameBoard {	
	private:
		Figure* board[8][8];
		std::vector<Figure*>figures;
		static GameBoard* boardptr;
		bool CheckForAlly(int,int,int);
		bool CheckForEnemy(int,int,int);
		bool IsOccupied(int,int);
		void PutFigure(Figure*, int, int);
		void AddFigure(Figure*);
		void RemoveFigure(Figure*);
		int GetPosX(Figure*);
		int GetPosY(Figure*, int);
		int CheckLineX(int, int, int);
		int CheckLineY(int, int, int);
		std::string CheckDiagonal (int, int);
		std::string DrawBoard();
		void ArrangeFigures();
	
	public:
		GameBoard();
		virtual ~GameBoard();
		
	friend class Figure;
	friend class Pawn;
	friend class Tower;
	friend class Knight;
	friend class Bishop;
	friend class Queen;
	friend class King;
	friend class BoardAnalyzer;
	friend std::ostream& operator<< (std::ostream& output, GameBoard& gameboard);
};
#endif