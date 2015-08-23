#pragma once
#include "definitions.h"
#include "Engine.h"

namespace mnkgame
{

class Render
{
public:
	virtual void drawBoard(int rows, int cols) = 0;
	virtual void drawX(Coordinate square) = 0;
	virtual void drawO(Coordinate square) = 0;

	Engine* getEngine() const { return m_engine; }
	// call Render::draw from defived classes to do all drawing 
	void draw();
protected:
	// prohibits deletion of a derived class object through the pointer of this class;
	// only derived class objects can be deleted not with pointers to base/this class.
	~Render() = default;
private:
	void drawPosition();
	friend void Engine::setParameters(Render* renderer, int rows, int cols, int winRowLenght);
	Engine* m_engine = nullptr;
};

}

