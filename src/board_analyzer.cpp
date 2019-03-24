#include "board_analyzer.h"
#include "board.h"
#include "figures.h"
#include <iostream>
#include <cstdlib>

BoardAnalyzer::BoardAnalyzer() {
	isGameInSession = false;
	command = "";
	BeginOperation();
}

BoardAnalyzer::~BoardAnalyzer() {
	
}

void BoardAnalyzer::BeginOperation() {
	while (command != "exit") {
		if (!isGameInSession) {
			BeginSession();
		}
		std::cout << "If don't want to play again, type 'exit'. If you do, type whatever you want\n";
		std::cout << ">";
		std::cin >> command;
	}
}

void BoardAnalyzer::BeginSession() {
	GameBoard Chessboard;
	Pawn *p1 = new Pawn(1);
	Pawn *p2 = new Pawn(1);
	Pawn *p3 = new Pawn(1);
	Pawn *p4 = new Pawn(1);
	Pawn *p5 = new Pawn(1);
	Pawn *p6 = new Pawn(1);
	Pawn *p7 = new Pawn(1);
	Pawn *p8 = new Pawn(1);
	Pawn *p9 = new Pawn(2);
	Pawn *p10 = new Pawn(2);
	Pawn *p11 = new Pawn(2);
	Pawn *p12 = new Pawn(2);
	Pawn *p13 = new Pawn(2);
	Pawn *p14 = new Pawn(2);
	Pawn *p15 = new Pawn(2);
	Pawn *p16 = new Pawn(2);
	King *k1 = new King(1);
	King *k2 = new King(2);
	Queen *q1 = new Queen(1);
	Queen *q2 = new Queen(2);
	Bishop *b1 = new Bishop(1);
	Bishop *b2 = new Bishop(1);
	Bishop *b3 = new Bishop(2);
	Bishop *b4 = new Bishop(2);
	Knight *n1 = new Knight(1);
	Knight *n2 = new Knight(1);
	Knight *n3 = new Knight(2);
	Knight *n4 = new Knight(2);
	Tower *t1 = new Tower(1);
	Tower *t2 = new Tower(1);
	Tower *t3 = new Tower(2);
	Tower *t4 = new Tower(2);
	std::cout << "Each player is expected to enter the following command '<wherefrom><whereto>' i.e. 'G2B2'\n";
	GameBoard::boardptr->ArrangeFigures();
	std::cout << Chessboard;
	isConclusionReached = false;
	analyzed = false;
	ForceMoveAnalysis();
	bool legitMove = false;
	while (!isConclusionReached) {
		do {
			if (analyzed) {
				std::cout << "That's not a legit move, please try another\n";
			}
			analyzed = false;
			std::cout << "White makes a move\n";
			std::cout << ">";
			std::cin >> command;
			if (isCorrectCommand(command)) {
				analyzed = true;
			}
			else {
				analyzed = false;
				std::cout << "That's not a correct command\n";
			}
			if (analyzed) {
				legitMove = isLegitMove(command, 1);
			}
		} while (!legitMove);
		ForceMoveAnalysis();
		std::cout << Chessboard;
		analyzed = false;
		legitMove = false;
		do {
			if (analyzed) {
					std::cout << "That's not a legit move, please try another\n";
				}
				analyzed = false;
				std::cout << "Black makes a move\n";
				std::cout << ">";
				std::cin >> command;
				if (isCorrectCommand(command)) {
					analyzed = true;
				}
				else {
					analyzed = false;
					std::cout << "That's not a correct command\n";
				}
				if (analyzed) {
					legitMove = isLegitMove(command, 2);
				}
			} while (!legitMove);
		ForceMoveAnalysis();
		std::cout << Chessboard;
		analyzed = false;
		legitMove = false;
		//isConclusionReached = true;
	}
}

bool BoardAnalyzer::isCorrectCommand(std::string cmd) {
	if (((cmd[0] >= 65 && cmd[0] <= 90) || (cmd[0] >= 97 && cmd[0] <= 122)) && ((cmd[2] >= 65 && cmd[2] <= 90) || (cmd[2] >= 97 && cmd[2] <= 122))) {
		if (cmd[1] >= 49 && cmd[1] <= 56 && cmd[3] >= 49 && cmd[3] <= 56) {
			return true;
		}
	}
	else {
		return false;
	}
}

bool BoardAnalyzer::isLegitMove(std::string cmd, int player) {
	int fromX;
	int fromY = (int)cmd[1] - 49;
	int toX;
	int toY = (int)cmd[3] - 49;
	if (cmd[0] >= 97) {
		fromX = int(cmd[0]) - 97;
	}
	else {
		fromX = int(cmd[0]) - 65;
	}
	if (cmd[2] >= 97) {
		toX = int(cmd[2]) - 97;
	}
	else {
		toX = int(cmd[2]) - 65;
	}
	fromY = 7 - fromY;
	toY = 7 - toY;
	if (GameBoard::boardptr->board[fromY][fromX] != 0) {
		if (GameBoard::boardptr->board[fromY][fromX]->GetPlayer() == player) {
			if (GameBoard::boardptr->board[fromY][fromX]->movementRange[toY][toX]) {
				GameBoard::boardptr->PutFigure(GameBoard::boardptr->board[fromY][fromX],toY,toX);
				return true;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void BoardAnalyzer::ForceMoveAnalysis() {
	for (auto &figure : GameBoard::boardptr->figures) {
		figure->AnalyzeMovement();
	}
}

void BoardAnalyzer::DebugMode() {
	while (true) {
		int x;
		int y;
		std::cout << "Podaj i oraz j\n";
		std::cin >> x >> y;
		while (GameBoard::boardptr->board[x][y] == 0) {
			std::cout << "Tak nie wolno!\n";
			std::cout << "Podaj nowe i oraz j\n";
			std::cin >> x >> y;
		}
		for (int i=0; i<=7; ++i) {
			for (int j=0; j<=7; ++j) {
				std::cout << "|" << GameBoard::boardptr->board[x][y]->movementRange[i][j] << "|";
				if (j==7) {
					std::cout << '\n';
				}
			}
		}	
	}
}