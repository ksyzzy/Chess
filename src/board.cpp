#include "board.h"
#include "figures.h"
#include <iostream>
#include <algorithm>
#include <string>

GameBoard* GameBoard::boardptr = 0;
GameBoard::GameBoard() {
	GameBoard::boardptr = this;
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {	
			board[i][j] = 0;
		}
	}
}

GameBoard::~GameBoard() {
	figures.clear();
}

std::string GameBoard::DrawBoard() {
	std::string temp = "";
	int k = 8;
    for (int i=0; i<8; ++i) {
		temp += std::to_string(k);
        for (int j=0; j<8; ++j) {
			if (board[i][j] != 0) {
				temp+= '|' + std::string(1,board[i][j]->GetType()) + std::to_string(board[i][j]->GetPlayer()) + '|';
			}
			else {
				
				temp += '|' + std::string("__") + '|';
			}
			if (j==7) {
				temp += '\n';
				--k;
			}
        }
    }
	temp += "  A   B   C   D   E   F   G   H\n";
	return temp;
}

std::ostream& operator<< (std::ostream & output, GameBoard & gameboard)
{
   output << GameBoard::boardptr->DrawBoard();
   return output;
}

bool GameBoard::CheckForAlly(int player, int i, int j) {
	if (board[i][j] == 0) {
		return false;
	}
	else if (board[i][j]->GetPlayer() == player) {
		return true;
	}
}

bool GameBoard::CheckForEnemy(int player, int i, int j) {
	if (board[i][j] == 0) {
		return false;
	}
	else if (board[i][j]->GetPlayer() != player) {
		return true;
	}
}

bool GameBoard::IsOccupied(int i, int j) {
	if (board[i][j] == 0) {
		return false;
	}
	else {
		return true;
	}
}

void GameBoard::AddFigure(Figure* figure) {
	if (figure->GetType() != 0) {
		figures.push_back(figure);
	}
}

void GameBoard::RemoveFigure(Figure* figure) {
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j){
			if (board[i][j] == figure){
				board[i][j] = 0;
			}
		}
	}
	figures.erase(std::remove(figures.begin(), figures.end(), figure), figures.end());
}

void GameBoard::ArrangeFigures() {
	int pawns_P1 = 0;
	int pawns_P2 = 0;
	for (int i=0; i<figures.size(); ++i) {
		if (figures[i]->GetPlayer() == 1) {
			switch(figures[i]->GetType()) {
				case('K'):
					board[7][4] = figures[i];
				break;
				case('Q'):
					board[7][3] = figures[i];
				break;
				case('T'):
					if (board[7][0] == 0) {
						board[7][0] = figures[i];
					}
					else {
						board[7][7] = figures[i];
					}
				break;
				case('N'):
					if (board[7][1] == 0) {
						board[7][1] = figures[i];
					}
					else {
						board[7][6] = figures[i];
					}
				break;
				case('B'):
					if (board[7][2] == 0) {
						board[7][2] = figures[i];
					}
					else {
						board[7][5] = figures[i];
					}
				break;
				case('P'):
					board[6][pawns_P1] = figures[i];
					++pawns_P1;
				break;
			}
		}
		else {
			if (figures[i]->GetPlayer() == 2) {
				switch(figures[i]->GetType()) {
				case('K'):
					board[0][4] = figures[i];
				break;
				case('Q'):
					board[0][3] = figures[i];
				break;
				case('T'):
					if (board[0][0] == 0) {
						board[0][0] = figures[i];
					}
					else {
						board[0][7] = figures[i];
					}
				break;
				case('N'):
					if (board[0][1] == 0) {
						board[0][1] = figures[i];
					}
					else {
						board[0][6] = figures[i];
					}
				break;
				case('B'):
					if (board[0][2] == 0) {
						board[0][2] = figures[i];
					}
					else {
						board[0][5] = figures[i];
					}
				break;
				case('P'):
					board[1][pawns_P2] = figures[i];
					++pawns_P2;
				break;
				}
			}
			
		}
	}
}

void GameBoard::PutFigure(Figure* figure, int x, int y) {
	int posX = GetPosX(figure);
	int posY = GetPosY(figure, posX);
	board[posX][posY] = 0;
	if (board[x][y] == 0) {
		board[x][y] = figure;
	}
	else {
		delete(board[x][y]);
		board[x][y] = figure;
	}
}

int GameBoard::GetPosX(Figure* figure) {
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			if (board[i][j] == figure) {
				return i;
			}
		}
	}
}

int GameBoard::GetPosY(Figure* figure, int x) {
	for (int j=0; j<8; ++j) {
		if (board[x][j] == figure) {
			return j;
		}
	}
}

int GameBoard::CheckLineY(int x, int y, int direction) {
	int i = y;
	switch(direction) {
		case(0):
			while (i>=0) {
				if (board[x][i] != 0 && i != y) {
					return i;
				}
				--i;
			}
			return -1;
		break;
		case(1):
			while (i<=7) {
				if (board[x][i] != 0 && i != y) {
					return i;
				}
				++i;
			}
			return -1;
		break;
	}
}

int GameBoard::CheckLineX(int x, int y, int direction) {
	int i = x;
	switch(direction) {
		case(0):
			while (i<=7) {
				if (board[i][y] != 0 && i != x) {
					return i;
				}
				++i;
			}
			return -1;
		break;
		case(1):
			while (i>=0) {
				if (board[i][y] != 0 && i != x) {
					return i;
				}
				--i;
			}
			return -1;
		break;
	}
}

std::string GameBoard::CheckDiagonal(int x, int y) {
	int i = x;
	int j = y;
	bool found = false;
	std::string result;
	while (i>=0 && j>=0 && !found) {
		if (board[i][j] != 0 && i != x && j != y) {
			result += std::to_string(i) + std::to_string(j);
			found = true;
		}
		--i;
		--j;
	}
	if (!found) {
		result += "XX";
	}
	i = x;
	j = y;
	found = false;
	while (i>=0 && j<=7 && !found) {
		if (board[i][j] != 0 && i != x && j != y) {
			result += std::to_string(i) + std::to_string(j);
			found = true;
		}
		--i;
		++j;
	}
	if (!found) {
		result += "XX";
	}
	i = x;
	j = y;
	found = false;
	while (i<=7 && j>=0 && !found) {
		if (board[i][j] != 0 && i != x && j != y) {
			result += std::to_string(i) + std::to_string(j);
			found = true;
		}
		++i;
		--j;
	}
	if (!found) {
		result += "XX";
	}
	i = x;
	j = y;
	found = false;
	while (i<=7 && j<=7 && !found) {
		if (board[i][j] != 0 && i != x && j != y) {
			result += std::to_string(i) + std::to_string(j);
			found = true;
		}
		++i;
		++j;
	}
	if (!found) {
		result += "XX";
	}
	return result;
}
