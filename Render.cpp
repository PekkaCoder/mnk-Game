#include "Render.h"

namespace mnkgame
{

void Render::draw()
{
	if (m_engine == nullptr)
		return;
	drawBoard(m_engine->getBoard().getRows(), m_engine->getBoard().getCols());
	drawPosition();
}

void Render::drawPosition()
{
	if (m_engine == nullptr)
		return;
	int rows, cols;
	rows = m_engine->getBoard().getRows();
	cols = m_engine->getBoard().getCols();

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (m_engine->getBoard().getSquareValue({ i, j }) == Player::X)
				drawX({ i, j });
			else if (m_engine->getBoard().getSquareValue({ i, j }) == Player::O)
				drawO({ i, j });
		}
	}
}

}
