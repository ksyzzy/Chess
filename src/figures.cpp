#include "figures.h"
#include "board.h"
#include <string>

Figure::Figure() {}

Figure::~Figure() {}

int Figure::GetPlayer() {
	return player;
}

char Figure::GetType() {
	return type;
}

Pawn::Pawn(int player) {
	isFirstMove = true;
	this->player = player;
	type = 'P';
	GameBoard::boardptr->AddFigure(this);
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			movementRange[i][j] = false;
		}
	}
}

Pawn::~Pawn() {
	GameBoard::boardptr->RemoveFigure(this);
	if (player==1) {
		std::cout << "White Pawn has been destroyed\n";
	}
	else {
		std::cout << "Black Pawn has been destroyed\n";
	}
}

void Pawn::AnalyzeMovement() {
	int posX = GameBoard::boardptr->GetPosX(this);
	int posY = GameBoard::boardptr->GetPosY(this, posX);
	bool analyzed;
	switch(player) {
		case(1):
			for (int i=0; i<8; ++i) {
				for (int j=0; j<8; ++j) {
					analyzed = false;
					if (i == (posX-2) && j == posY && (!GameBoard::boardptr->IsOccupied((i+1),j)) && isFirstMove &&  (!GameBoard::boardptr->IsOccupied(i,j)) && (!analyzed)) {
						movementRange[i][j] = true;
						analyzed = true;
					}
					if (i == (posX-1) && j == posY && (!GameBoard::boardptr->IsOccupied(i,j)) && (!analyzed)) {
						movementRange[i][j] = true;
						analyzed = true;
					}
					if (i == (posX-1) && j == (posY-1) && GameBoard::boardptr->IsOccupied(i,j) && GameBoard::boardptr->CheckForEnemy(player, i, j) && (!analyzed)) {
						movementRange[i][j] = true;
						analyzed = true;
					}
					if (i == (posX-1) && j == (posY+1) && GameBoard::boardptr->IsOccupied(i,j) && GameBoard::boardptr->CheckForEnemy(player, i, j) && (!analyzed)) {
						movementRange[i][j] = true;
						analyzed = true;
					}
					if (!analyzed) {
						movementRange[i][j] = false;
					}
				}
			}
		break;
		case(2):
			for (int i=0; i<8; ++i) {
				for (int j=0; j<8; ++j) {
					analyzed = false;
					if (i == (posX+2) && j == posY && (!GameBoard::boardptr->IsOccupied((i-1),j)) && isFirstMove && (!GameBoard::boardptr->IsOccupied(i,j)) && (!analyzed)) {
						movementRange[i][j] = true;
						analyzed = true;
					}
					if (i == (posX+1) && j == posY && (!GameBoard::boardptr->IsOccupied(i,j)) && (!analyzed)) {
						movementRange[i][j] = true;
						analyzed = true;
					}
					if (i == (posX+1) && j == (posY-1) && GameBoard::boardptr->IsOccupied(i,j) && GameBoard::boardptr->CheckForEnemy(player, i, j) && (!analyzed)) {
						movementRange[i][j] = true;
						analyzed = true;
					}
					if (i == (posX+1) && j == (posY+1) && GameBoard::boardptr->IsOccupied(i,j) && GameBoard::boardptr->CheckForEnemy(player, i, j) && (!analyzed)) {
						movementRange[i][j] = true;
						analyzed = true;
					}
					if (!analyzed) {
						movementRange[i][j] = false;
					}
				}
			}
		break;
	}
}

Tower::Tower(int player) {
	this->player = player;
	type = 'T';
	GameBoard::boardptr->AddFigure(this);
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			movementRange[i][j] = false;
		}
	}
}

Tower::~Tower() {
	GameBoard::boardptr->RemoveFigure(this);
	if (player==1) {
		std::cout << "White Tower has been destroyed\n";
	}
	else {
		std::cout << "Black Tower has been destroyed\n";
	}
}

void Tower::AnalyzeMovement() {
	int posX = GameBoard::boardptr->GetPosX(this);
	int posY = GameBoard::boardptr->GetPosY(this, posX);
	int ObstructedYL = GameBoard::boardptr->CheckLineY(posX, posY, 0);
	int ObstructedYR = GameBoard::boardptr->CheckLineY(posX, posY, 1);
	int ObstructedXU = GameBoard::boardptr->CheckLineX(posX, posY, 1);
	int ObstructedXD = GameBoard::boardptr->CheckLineX(posX, posY, 0);
	bool analyzed;
	for (int i=0; i<=7; ++i) {
		for (int j=0; j<=7; ++j) {
			movementRange[i][j] = false;
		}
	}
	int i = posX;
	int j = posY;
	while (i >= 0) {
		analyzed = false;
		if (ObstructedXU == (-1) && i != posX) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		if (ObstructedXU < posX && i < ObstructedXU && i != posX && (!analyzed)) {
			movementRange[i][j] = false;
			analyzed = true;
		}
		if (ObstructedXU < posX && i > ObstructedXU && i < posX && (!analyzed)) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		--i;
	}
	i = posX;
	j = posY;
	while (i <= 7) {
		analyzed = false;
		if (ObstructedXD == (-1) && i != posX) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		if (ObstructedXD > posX && i > ObstructedXD && i != posX && (!analyzed)) {
			movementRange[i][j] = false;
			analyzed = true;
		}
		if (ObstructedXD > posX && i < ObstructedXD && i > posX && (!analyzed)) {
			movementRange[i][j] = true;
			analyzed = false;
		}
		++i;
	}
	i = posX;
	j = posY;
	while (j >= 0) {
		analyzed = false;
		if (ObstructedYL == (-1) && j != posY) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		if (ObstructedYL < posY && j < ObstructedYL && j != posY && (!analyzed)) {
			movementRange[i][j] = false;
			analyzed = true;
		}
		if (ObstructedYL < posY && j > ObstructedYL && j < posY && (!analyzed)) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		--j;
	}
	i = posX;
	j = posY;
	while (j <= 7) {
		analyzed = false;
		if (ObstructedYR == (-1) && j != posY) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		if (ObstructedYR > posY && j > ObstructedYR && j != posY && (!analyzed)) {
			movementRange[i][j] = false;
			analyzed = true;
		}
		if (ObstructedYR > posY && j < ObstructedYR && j > posY && (!analyzed)) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		++j;
	}
	i = posX;
	j = posY;
	if (ObstructedYL != (-1)) {
		if (GameBoard::boardptr->board[posX][ObstructedYL]->GetPlayer() != this->player) {
			movementRange[posX][ObstructedYL] = true;
		}
	}
	if (ObstructedYR != (-1)) {
		if (GameBoard::boardptr->board[posX][ObstructedYR]->GetPlayer() != this->player) {
			movementRange[posX][ObstructedYR] = true;
		}
	}
	if (ObstructedXU != (-1)) {
		if (GameBoard::boardptr->board[ObstructedXU][posY]->GetPlayer() != this->player) {
			movementRange[ObstructedXU][posY] = true;
		}
	}
	if (ObstructedXD != (-1)) {
		if (GameBoard::boardptr->board[ObstructedXD][posY]->GetPlayer() != this->player) {
			movementRange[ObstructedXD][posY] = true;
		}
	}
}

Bishop::Bishop(int player) {
	this->player = player;
	type = 'B';
	GameBoard::boardptr->AddFigure(this);
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			movementRange[i][j] = false;
		}
	}
}

Bishop::~Bishop() {
	GameBoard::boardptr->RemoveFigure(this);
	if (player==1) {
		std::cout << "White Bishop has been destroyed\n";
	}
	else {
		std::cout << "Black Bishop has been destroyed\n";
	}
	
}

void Bishop::AnalyzeMovement() {
	int obstructedDULX, obstructedDULY, obstructedDURX, obstructedDURY, obstructedDDLX, obstructedDDLY, obstructedDDRX, obstructedDDRY;
	int posX = GameBoard::boardptr->GetPosX(this);
	int posY = GameBoard::boardptr->GetPosY(this, posX);
	bool analyzed;
	bool isObstructed[4];
	std::string obstructed = GameBoard::boardptr->CheckDiagonal(posX, posY);
	if (obstructed[0] != 'X') {
		isObstructed[0] = true;
		obstructedDULX = int(obstructed[0]) - 48;
		obstructedDULY = int(obstructed[1]) - 48;
	}
	else {
		isObstructed[0] = false;
	}
	if (obstructed[2] != 'X') {
		isObstructed[1] = true;
		obstructedDURX = int(obstructed[2]) - 48;
		obstructedDURY = int(obstructed[3]) - 48;
	}
	else {
		isObstructed[1] = false;
	}
	if (obstructed[4] != 'X') {
		isObstructed[2] = true;
		obstructedDDLX = int(obstructed[4]) - 48;
		obstructedDDLY = int(obstructed[5]) - 48;
	}
	else {
		isObstructed[2] = false;
	}
	if (obstructed[6] != 'X') {
		isObstructed[3] = true;
		obstructedDDRX = int(obstructed[6]) - 48;
		obstructedDDRY = int(obstructed[7]) - 48;
	}
	else {
		isObstructed[3] = false;
	}
	for (int i = 0; i <= 7; ++i) {
		for (int j = 0; j <= 7; ++j) {
			movementRange[i][j] = false;
		}
	} 
	int i = posX;
	int j = posY;
	while (i >= 0 && j >= 0) {
		analyzed = false;
		if (i < posX && j < posY && (posX-i) == (posY-j)) { //upper-left diagonal
			if (!isObstructed[0]) {
				movementRange[i][j] = true;
				analyzed = true;
			}
			if (!analyzed) {
				if (i < obstructedDULX && j < obstructedDULY) {
					movementRange[i][j] = false;
					analyzed = true;
				}
			}
			if (!analyzed) {
				if (i > obstructedDULX && j > obstructedDULY) {
					movementRange[i][j] = true;
					analyzed = true;
				}
			}
		}
		--i;
		--j;
	}
	i = posX;
	j = posY;
	while (i >= 0 && j <= 7) {
		analyzed = false;
		if (i < posX && j > posY && (posX-i) == (j-posY)) { //upper-right diagonal
			if (!isObstructed[1]) {
				movementRange[i][j] = true;
				analyzed = true;
			}
			if (!analyzed) {
				if (i < obstructedDURX && j > obstructedDURY) {
					movementRange[i][j] = false;
					analyzed = true;
				}
			}
			if (!analyzed) {
				if (i > obstructedDURX && j < obstructedDURY) {
					movementRange[i][j] = true;
					analyzed = true;
				}
			}
		}
		--i;
		++j;
	}
	i = posX;
	j = posY;
	while (i <= 7 && j >= 0) {
		analyzed = false;
		if (!analyzed && i > posX && j < posY && (i-posX) == (posY-j)) { // lower-left diagonal
			if (!isObstructed[2]) {
				movementRange[i][j] = true;
				analyzed = true;
			}
			if (!analyzed) {
				if (i > obstructedDDLX && j < obstructedDDLY) {
					movementRange[i][j] = false;
					analyzed = true;
				}
			}
			if (!analyzed) {
				if (i < obstructedDDLX && j > obstructedDDLY) {
					movementRange[i][j] = true;
					analyzed = true;
				}
			}
		}
		++i;
		--j;
	}
	i = posX;
	j = posY;
	while (i <= 7 && j <= 7) {
		analyzed = false;
		if (i > posX && j > posY && (i-posX) == (j-posY)) { //lower-right diagonal
			if (!isObstructed[3]) {
				movementRange[i][j] = true;
				analyzed = true;
			}
			if (!analyzed) {
				if (i > obstructedDDRX && j > obstructedDDRY) {
					movementRange[i][j] = false;
					analyzed = true;
				}
			}
			if (!analyzed) {
				if (i < obstructedDDRX && j < obstructedDDRY) {
					movementRange[i][j] = true;
					analyzed = true;
				}
			}
		}
		++i;
		++j;
	}
	if (isObstructed[0]) {
		if (GameBoard::boardptr->board[obstructedDULX][obstructedDULY]->GetPlayer() == player) {
			movementRange[obstructedDULX][obstructedDULY] = false;
		}
		else if (GameBoard::boardptr->board[obstructedDULX][obstructedDULY]->GetPlayer() != player) {
			movementRange[obstructedDULX][obstructedDULY] = true;
		}
	}
	if (isObstructed[1]) {
		if (GameBoard::boardptr->board[obstructedDURX][obstructedDURY]->GetPlayer() == player) {
			movementRange[obstructedDURX][obstructedDURY] = false;
		}
		else if (GameBoard::boardptr->board[obstructedDURX][obstructedDURY]->GetPlayer() != player) {
			movementRange[obstructedDURX][obstructedDURY] = true;
		}
	}
	if (isObstructed[2]) {
		if (GameBoard::boardptr->board[obstructedDDLX][obstructedDDLY]->GetPlayer() == player) {
			movementRange[obstructedDDLX][obstructedDDLY] = false;
		}
		else if (GameBoard::boardptr->board[obstructedDDLX][obstructedDDLY]->GetPlayer() != player) {
			movementRange[obstructedDDLX][obstructedDDLY] = true;
		}
	}
	if (isObstructed[3]) {
		if (GameBoard::boardptr->board[obstructedDDRX][obstructedDDRY]->GetPlayer() == player) {
			movementRange[obstructedDDRX][obstructedDDRY] = false;
		}
		else if (GameBoard::boardptr->board[obstructedDDRX][obstructedDDRY]->GetPlayer() != player) {
			movementRange[obstructedDDRX][obstructedDDRY] = true;
		}
	}
}

Knight::Knight(int player) {
	this->player = player;
	type = 'N';
	GameBoard::boardptr->AddFigure(this);
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			movementRange[i][j] = false;
		}
	}
}

Knight::~Knight() {
	GameBoard::boardptr->RemoveFigure(this);
	if (player==1) {
		std::cout << "White Knight has been destroyed\n";
	}
	else {
		std::cout << "Black Knight has been destroyed\n";
	}
}

void Knight::AnalyzeMovement() {
	int posX = GameBoard::boardptr->GetPosX(this);
	int posY = GameBoard::boardptr->GetPosY(this, posX);
	for (int i = 0; i <= 7; ++i) {
		for (int j = 0; j <= 7; ++j) {
			movementRange[i][j] = false;
		}
	}
	int i = posX+2;
	int j = posY-1;
	if (i <= 7 && j >= 0 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	j = posY+1;
	if (i <= 7 && j <= 7 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	i = posX-2;
	if (i >= 0 && j <= 7 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;		
	}
	j = posY-1;
	if (i >=0 && j >= 0 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;		
	}
	i = posX-1;
	j = posY-2;
	if (i >= 0 && j >= 0 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	i = posX+1;
	if (i <= 7 && j >= 0 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	j = posY+2;
	if (i <= 7 && j <= 7 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	i = posX-1;
	if (i >= 0 && j <= 7 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
}

Queen::Queen(int player) {
	this->player = player;
	type = 'Q';
	GameBoard::boardptr->AddFigure(this);
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			movementRange[i][j] = false;
		}
	}
}

Queen::~Queen() {
	GameBoard::boardptr->RemoveFigure(this);
	if (player==1) {
		std::cout << "White Queen has been destroyed\n";
	}
	else {
		std::cout << "Black Queen has been destroyed\n";
	}
}

void Queen::AnalyzeMovement() {
	int obstructedDULX, obstructedDULY, obstructedDURX, obstructedDURY, obstructedDDLX, obstructedDDLY, obstructedDDRX, obstructedDDRY;
	int posX = GameBoard::boardptr->GetPosX(this);
	int posY = GameBoard::boardptr->GetPosY(this, posX);
	int ObstructedYL = GameBoard::boardptr->CheckLineY(posX, posY, 0);
	int ObstructedYR = GameBoard::boardptr->CheckLineY(posX, posY, 1);
	int ObstructedXU = GameBoard::boardptr->CheckLineX(posX, posY, 1);
	int ObstructedXD = GameBoard::boardptr->CheckLineX(posX, posY, 0);
	bool analyzed;
	bool isObstructed[4];
	std::string obstructed = GameBoard::boardptr->CheckDiagonal(posX, posY);
	for (int i = 0; i <= 7; ++i) {
		for (int j = 0; j <= 7; ++j) {
			movementRange[i][j] = false;
		}
	}
	int i = posX;
	int j = posY;
	while (i >= 0) {
		analyzed = false;
		if (ObstructedXU == (-1) && i != posX) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		if (ObstructedXU < posX && i < ObstructedXU && i != posX && (!analyzed)) {
			movementRange[i][j] = false;
			analyzed = true;
		}
		if (ObstructedXU < posX && i > ObstructedXU && i < posX && (!analyzed)) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		--i;
	}
	i = posX;
	j = posY;
	while (i <= 7) {
		analyzed = false;
		if (ObstructedXD == (-1) && i != posX) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		if (ObstructedXD > posX && i > ObstructedXD && i != posX && (!analyzed)) {
			movementRange[i][j] = false;
			analyzed = true;
		}
		if (ObstructedXD > posX && i < ObstructedXD && i > posX && (!analyzed)) {
			movementRange[i][j] = true;
			analyzed = false;
		}
		++i;
	}
	i = posX;
	j = posY;
	while (j >= 0) {
		analyzed = false;
		if (ObstructedYL == (-1) && j != posY) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		if (ObstructedYL < posY && j < ObstructedYL && j != posY && (!analyzed)) {
			movementRange[i][j] = false;
			analyzed = true;
		}
		if (ObstructedYL < posY && j > ObstructedYL && j < posY && (!analyzed)) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		--j;
	}
	i = posX;
	j = posY;
	while (j <= 7) {
		analyzed = false;
		if (ObstructedYR == (-1) && j != posY) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		if (ObstructedYR > posY && j > ObstructedYR && j != posY && (!analyzed)) {
			movementRange[i][j] = false;
			analyzed = true;
		}
		if (ObstructedYR > posY && j < ObstructedYR && j > posY && (!analyzed)) {
			movementRange[i][j] = true;
			analyzed = true;
		}
		++j;
	}
	i = posX;
	j = posY;
	if (ObstructedYL != (-1)) {
		if (GameBoard::boardptr->board[posX][ObstructedYL]->GetPlayer() != this->player) {
			movementRange[posX][ObstructedYL] = true;
		}
	}
	if (ObstructedYR != (-1)) {
		if (GameBoard::boardptr->board[posX][ObstructedYR]->GetPlayer() != this->player) {
			movementRange[posX][ObstructedYR] = true;
		}
	}
	if (ObstructedXU != (-1)) {
		if (GameBoard::boardptr->board[ObstructedXU][posY]->GetPlayer() != this->player) {
			movementRange[ObstructedXU][posY] = true;
		}
	}
	if (ObstructedXD != (-1)) {
		if (GameBoard::boardptr->board[ObstructedXD][posY]->GetPlayer() != this->player) {
			movementRange[ObstructedXD][posY] = true;
		}
	}
	if (obstructed[0] != 'X') {
		isObstructed[0] = true;
		obstructedDULX = int(obstructed[0]) - 48;
		obstructedDULY = int(obstructed[1]) - 48;
	}
	else {
		isObstructed[0] = false;
	}
	if (obstructed[2] != 'X') {
		isObstructed[1] = true;
		obstructedDURX = int(obstructed[2]) - 48;
		obstructedDURY = int(obstructed[3]) - 48;
	}
	else {
		isObstructed[1] = false;
	}
	if (obstructed[4] != 'X') {
		isObstructed[2] = true;
		obstructedDDLX = int(obstructed[4]) - 48;
		obstructedDDLY = int(obstructed[5]) - 48;
	}
	else {
		isObstructed[2] = false;
	}
	if (obstructed[6] != 'X') {
		isObstructed[3] = true;
		obstructedDDRX = int(obstructed[6]) - 48;
		obstructedDDRY = int(obstructed[7]) - 48;
	}
	else {
		isObstructed[3] = false;
	}
	i = posX;
	j = posY;
	while (i >= 0 && j >= 0) {
		analyzed = false;
		if (i < posX && j < posY && (posX-i) == (posY-j)) { //upper-left diagonal
			if (!isObstructed[0]) {
				movementRange[i][j] = true;
				analyzed = true;
			}
			if (!analyzed) {
				if (i < obstructedDULX && j < obstructedDULY) {
					movementRange[i][j] = false;
					analyzed = true;
				}
			}
			if (!analyzed) {
				if (i > obstructedDULX && j > obstructedDULY) {
					movementRange[i][j] = true;
					analyzed = true;
				}
			}
		}
		--i;
		--j;
	}
	i = posX;
	j = posY;
	while (i >= 0 && j <= 7) {
		analyzed = false;
		if (i < posX && j > posY && (posX-i) == (j-posY)) { //upper-right diagonal
			if (!isObstructed[1]) {
				movementRange[i][j] = true;
				analyzed = true;
			}
			if (!analyzed) {
				if (i < obstructedDURX && j > obstructedDURY) {
					movementRange[i][j] = false;
					analyzed = true;
				}
			}
			if (!analyzed) {
				if (i > obstructedDURX && j < obstructedDURY) {
					movementRange[i][j] = true;
					analyzed = true;
				}
			}
		}
		--i;
		++j;
	}
	i = posX;
	j = posY;
	while (i <= 7 && j >= 0) {
		analyzed = false;
		if (!analyzed && i > posX && j < posY && (i-posX) == (posY-j)) { // lower-left diagonal
			if (!isObstructed[2]) {
				movementRange[i][j] = true;
				analyzed = true;
			}
			if (!analyzed) {
				if (i > obstructedDDLX && j < obstructedDDLY) {
					movementRange[i][j] = false;
					analyzed = true;
				}
			}
			if (!analyzed) {
				if (i < obstructedDDLX && j > obstructedDDLY) {
					movementRange[i][j] = true;
					analyzed = true;
				}
			}
		}
		++i;
		--j;
	}
	i = posX;
	j = posY;
	while (i <= 7 && j <= 7) {
		analyzed = false;
		if (i > posX && j > posY && (i-posX) == (j-posY)) { //lower-right diagonal
			if (!isObstructed[3]) {
				movementRange[i][j] = true;
				analyzed = true;
			}
			if (!analyzed) {
				if (i > obstructedDDRX && j > obstructedDDRY) {
					movementRange[i][j] = false;
					analyzed = true;
				}
			}
			if (!analyzed) {
				if (i < obstructedDDRX && j < obstructedDDRY) {
					movementRange[i][j] = true;
					analyzed = true;
				}
			}
		}
		++i;
		++j;
	}
	if (isObstructed[0]) {
		if (GameBoard::boardptr->board[obstructedDULX][obstructedDULY]->GetPlayer() == player) {
			movementRange[obstructedDULX][obstructedDULY] = false;
		}
		else if (GameBoard::boardptr->board[obstructedDULX][obstructedDULY]->GetPlayer() != player) {
			movementRange[obstructedDULX][obstructedDULY] = true;
		}
	}
	if (isObstructed[1]) {
		if (GameBoard::boardptr->board[obstructedDURX][obstructedDURY]->GetPlayer() == player) {
			movementRange[obstructedDURX][obstructedDURY] = false;
		}
		else if (GameBoard::boardptr->board[obstructedDURX][obstructedDURY]->GetPlayer() != player) {
			movementRange[obstructedDURX][obstructedDURY] = true;
		}
	}
	if (isObstructed[2]) {
		if (GameBoard::boardptr->board[obstructedDDLX][obstructedDDLY]->GetPlayer() == player) {
			movementRange[obstructedDDLX][obstructedDDLY] = false;
		}
		else if (GameBoard::boardptr->board[obstructedDDLX][obstructedDDLY]->GetPlayer() != player) {
			movementRange[obstructedDDLX][obstructedDDLY] = true;
		}
	}
	if (isObstructed[3]) {
		if (GameBoard::boardptr->board[obstructedDDRX][obstructedDDRY]->GetPlayer() == player) {
			movementRange[obstructedDDRX][obstructedDDRY] = false;
		}
		else if (GameBoard::boardptr->board[obstructedDDRX][obstructedDDRY]->GetPlayer() != player) {
			movementRange[obstructedDDRX][obstructedDDRY] = true;
		}
	}
}

King::King(int player) {
	isFirstMove = true;
	this->player = player;
	type = 'K';
	GameBoard::boardptr->AddFigure(this);
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			movementRange[i][j] = false;
		}
	}
}

King::~King() {
	GameBoard::boardptr->RemoveFigure(this);
}

void King::AnalyzeMovement() {
	int posX = GameBoard::boardptr->GetPosX(this);
	int posY = GameBoard::boardptr->GetPosY(this, posX);
	for (int i = 0; i <= 7; ++i) {
		for (int j = 0; j <= 7; ++j) {
			movementRange[i][j] = false;
		}
	}
	int i = posX-1;
	int j = posY-1;
	if (i >= 0 && j >= 0 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	j = posY;
	if (i >= 0 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	j = posY+1;
	if (i >= 0 && j <= 7 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	i = posX;
	if (j <= 7 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	j = posY-1;
	if (j >= 0 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	i = posX+1;
	if (i <= 7 && j >= 0 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
			movementRange[i][j] = true;
	}
	j = posY;
	if (i <= 7 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
	j = posY+1;
	if (i <= 7 && j <= 7 && !GameBoard::boardptr->CheckForAlly(player, i, j)) {
		movementRange[i][j] = true;
	}
}