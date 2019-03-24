#ifndef FIGURES
#define FIGURES

class Figure {
    protected:
        int player;
        bool movementRange[8][8];
		char type;
        virtual void AnalyzeMovement() = 0;

    public:
		Figure();
		virtual ~Figure();
		int GetPlayer();
		char GetType();
	friend class BoardAnalyzer;
};

class Pawn: public Figure {
    private:
        bool isFirstMove;
		virtual void AnalyzeMovement();
    public:
        Pawn(int);
        virtual ~Pawn();
	friend class BoardAnalyzer;
};

class Knight: public Figure {
	private:
		virtual void AnalyzeMovement();
	public:
		Knight(int);
		virtual ~Knight();
	friend class BoardAnalyzer;
};

class Bishop: public Figure {
	private:
		virtual void AnalyzeMovement();
	public:
		Bishop(int);
		virtual ~Bishop();
	friend class BoardAnalyzer;
};

class Queen: public Figure {
	private:
		virtual void AnalyzeMovement();
	public:
		Queen(int);
		virtual ~Queen();
	friend class BoardAnalyzer;
};

class King: public Figure {
	private:
		bool isFirstMove;
		virtual void AnalyzeMovement();
	public:
		King(int);
		virtual ~King();
	friend class BoardAnalyzer;
};
class Tower: public Figure {
	private:
		bool isFirstMove;
		virtual void AnalyzeMovement();
	public:
		Tower(int);
		virtual ~Tower();
	friend class BoardAnalyzer;
};

#endif
