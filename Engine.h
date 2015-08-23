#pragma once
#include "Board.h"

namespace mnkgame
{

class Render;

// mnk game engine
class Engine
{
public:
	// winRowLenght: how many (one sides) pieces in a row is a win
	void setParameters(Render* renderer, int rows, int cols, int winRowLenght) noexcept(false);
	void newGame();
	const Board& getBoard() const { return m_board; }
	Board& setBoard() { return m_board; }
	bool makeNextMove(const Coordinate& square) noexcept(false);
	// checks if there is a win; if there is then saves the info about it to m_gameOverInfo
	bool checkWin();
	GameState getGameState() const { return m_gameState; }
	PosInfo getGameOverInfo() { return m_gameOverInfo; }
	const std::vector<Coordinate>& getMoveHistory() const { return m_moveHistory; }

private:
	GameState m_gameState = GameState::READY_TO_START;
	// after the game is over this contains information about the end
	PosInfo m_gameOverInfo;
	Board m_board;
	Player m_nextTurn = PLAYER_TO_START; // who's turn is next (X always starts the game)
	int m_winRowLenght = 3;	// how many needed in a row to win
	std::vector<Coordinate> m_moveHistory;
};

}

