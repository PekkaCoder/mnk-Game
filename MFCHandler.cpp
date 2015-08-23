#include "stdafx.h"
#include "Engine.h"
#include "MFCHandler.h"

void MFCHandler::onMouseMove(UINT nFlags, CPoint point)
{

}

bool MFCHandler::onLButtonDown(UINT nFlags, CPoint point)
{
	Coordinate square;
	if (getBoardSquare(point, square))
	{
		getEngine()->makeNextMove(square);
		return true;
	}

	return false;
}

void MFCHandler::setParameters(int sizeSquare, CPoint boardPos)
{
	m_sizeSquare = sizeSquare;
	m_boardPos = boardPos;
}

bool MFCHandler::getBoardSquare(CPoint point, Coordinate& square)
{
	if (point.x - m_boardPos.x < 0 || point.y - m_boardPos.y < 0)
		return false;
	square = Coordinate{ (point.y - m_boardPos.y) / m_sizeSquare , ((point.x - m_boardPos.x) / m_sizeSquare) };
	return getEngine()->getBoard().isValid(square);
}

void MFCHandler::drawX(Coordinate square)
{
	assert(m_drawTempDC != nullptr);
	if (m_drawTempDC == nullptr)
		return;
	const int OFFSET = m_sizeSquare / 5; // offset from the square borders to draw X
	CPen thickPen(PS_SOLID, 3, RGB(255, 0, 255));
	CPen* oldPen = static_cast<CPen*>(m_drawTempDC->SelectObject(&thickPen));
	// downhill
	m_drawTempDC->MoveTo(m_boardPos.x + square.y * m_sizeSquare + OFFSET, m_boardPos.y + square.x * m_sizeSquare + OFFSET);
	m_drawTempDC->LineTo(m_boardPos.x + square.y * m_sizeSquare + m_sizeSquare - OFFSET,
		m_boardPos.y + square.x * m_sizeSquare + m_sizeSquare - OFFSET);
	// uphill
	m_drawTempDC->MoveTo(m_boardPos.x + square.y * m_sizeSquare + OFFSET, m_boardPos.y + square.x * m_sizeSquare + m_sizeSquare - OFFSET);
	m_drawTempDC->LineTo(m_boardPos.x + square.y * m_sizeSquare + m_sizeSquare - OFFSET,
		m_boardPos.y + square.x * m_sizeSquare + OFFSET);

	m_drawTempDC->SelectObject(oldPen);
}

void MFCHandler::drawO(Coordinate square)
{
	assert(m_drawTempDC != nullptr);
	if (m_drawTempDC == nullptr)
		return;
	const int OFFSET = m_sizeSquare / 5; // offset from the square borders to draw O
	CPen thickPen(PS_SOLID, 3, RGB(0, 255, 255));
	CPen* oldPen = static_cast<CPen*>(m_drawTempDC->SelectObject(&thickPen));

	m_drawTempDC->Ellipse(m_boardPos.x + square.y * m_sizeSquare + OFFSET, m_boardPos.y + square.x * m_sizeSquare + OFFSET,
		m_boardPos.x + square.y * m_sizeSquare + m_sizeSquare - OFFSET, m_boardPos.y + square.x * m_sizeSquare + m_sizeSquare - OFFSET);

	m_drawTempDC->SelectObject(oldPen);
}

void MFCHandler::drawBoard(int rows, int cols)
{
	assert(m_drawTempDC != nullptr);
	if (m_drawTempDC == nullptr)
		return;
	CPen thickPen(PS_SOLID, 3, RGB(0, 0, 255));
	CPen* oldPen = static_cast<CPen*>(m_drawTempDC->SelectObject(&thickPen));
	// rows
	for (int i = 0; i <= rows; ++i)
	{
		m_drawTempDC->MoveTo(m_boardPos.x, m_boardPos.y + i * m_sizeSquare);
		m_drawTempDC->LineTo(m_boardPos.x + cols * m_sizeSquare, m_boardPos.y + i * m_sizeSquare);
	}
	// columns
	for (int j = 0; j <= cols; ++j)
	{
		m_drawTempDC->MoveTo(m_boardPos.x + j * m_sizeSquare, m_boardPos.y);
		m_drawTempDC->LineTo(m_boardPos.x + j * m_sizeSquare, m_boardPos.y + rows * m_sizeSquare);
	}
	CString str;
	// coordinates - note: coordinates are shown going right, up. So (1,1) is at the bottom left.
	// Because the code uses right down system (see Definitions.h) we do a conversion here.
	for (int j = 0; j < cols; ++j)
	{
		str.Format(_T("%i"), j + 1);
		m_drawTempDC->TextOut(m_boardPos.x + m_sizeSquare * j + static_cast<int>(0.35*m_sizeSquare), m_boardPos.y + m_sizeSquare * rows + 5, str);
	}
	for (int j = 0; j < rows; ++j)
	{
		str.Format(_T("%i"), j + 1);
		m_drawTempDC->TextOut(m_boardPos.x - 25, m_boardPos.y + m_sizeSquare * rows - j * m_sizeSquare - static_cast<int>(0.7*m_sizeSquare), str);
	}
	// move history
	int x, y;
	int count = 0;
	for (const auto& a : getEngine()->getMoveHistory())
	{
		x = a.y + 1;
		y = getEngine()->getBoard().getRows() - a.x;
		str.Format(_T("%i, %i"), x, y);
		m_drawTempDC->TextOut(m_boardPos.x + cols * m_sizeSquare + 20, m_boardPos.y + 15 * count++, str);
	}
	// check game over
	if (getEngine()->getGameState() == GameState::GAME_OVER)
	{
		PosInfo winInfo = getEngine()->getGameOverInfo();
		if (winInfo.winner == Player::O)
			str.Format(_T("Game Over! O won"), x, y);
		else if (winInfo.winner == Player::X)
			str.Format(_T("Game Over! X won"), x, y);
		else
			str.Format(_T("Game Over! Draw"), x, y);
		m_drawTempDC->TextOut(m_boardPos.x + cols * m_sizeSquare + 20, m_boardPos.y + 15 * count++, str);
	}

	m_drawTempDC->SelectObject(oldPen);
}

void MFCHandler::draw(CDC* pDC)
{
	m_drawTempDC = pDC;

	Render::draw();
	// m_drawTempDC only works temporary in draw-function so set it to null
	// so that it cannot be used from other routes
	m_drawTempDC = nullptr;
}

