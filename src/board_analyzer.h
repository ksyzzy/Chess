#ifndef BOARD_ANALYZER
#define BOARD_ANALYZER
#include <string>

class BoardAnalyzer {
	private:
	void BeginOperation();
	void BeginSession();
	void AnalyzeBoard();
	void ForceMoveAnalysis();
	void DebugMode();
	bool isLegitMove(std::string, int);
	bool isCorrectCommand(std::string);
	bool isGameInSession;
	bool isConclusionReached;
	bool analyzed;
	std::string command;
	
	public:
	BoardAnalyzer();
	virtual ~BoardAnalyzer();
};

#endif