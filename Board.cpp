#include "Board.h"

namespace mnkgame
{

void Board::setBoardSize(int rows, int cols, bool emptyBoard)
{
	if (rows == m_rows && cols == m_cols)
	{
		// size is already correct, just (possibly) empty the board
		if (emptyBoard)
			empty();
		return;
	}
	m_rows = rows;
	m_cols = cols;

	m_position.resize(m_rows);
	m_position.shrink_to_fit();
	for (auto& row : m_position)
	{
		row.resize(m_cols);
		row.shrink_to_fit();
		if (emptyBoard)
			for (auto& col : row)
				col = Player::EMPTY;
	}
}

void Board::empty()
{
	for (auto& row : m_position)
	{
		for (auto& col : row)
			col = Player::EMPTY;
	}
}

bool Board::isValid(const Coordinate& square) const
{
	return square.x >= 0 && square.y >= 0 && square.x < m_rows && square.y < m_cols;
}

void Board::setSquareValue(const Coordinate& square, Player player)
{
	assert(isValid(square));
	if (isValid(square))
		m_position[square.x][square.y] = player;
}

}


