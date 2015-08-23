#pragma once
#include "Render.h"

using namespace mnkgame;

// does all the drawings and messagehandling for a MFC project
class MFCHandler : public Render
{
public:
	void setParameters(int sizeSquare, CPoint boardPos);
	// returns board square from (mouse-) coordinate 
	bool getBoardSquare(CPoint point, Coordinate& square);
	// handling window messages
	void onMouseMove(UINT nFlags, CPoint point);
	bool onLButtonDown(UINT nFlags, CPoint point) noexcept(false);
	void draw(CDC* pDC);

private:
	// overridables
	void drawBoard(int rows, int cols);
	void drawX(Coordinate square);
	void drawO(Coordinate square);
	// dc to draw. works only temporary from draw() function after windows paint call 
	CDC* m_drawTempDC = nullptr;
	int m_sizeSquare = 35;
	CPoint m_boardPos{ 50,30 };
};




