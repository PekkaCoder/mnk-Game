# mnk-Game
An illustration how to create a easily portable two players playable mnk-Game using modern C++ with classes.

How to use mnk Game code
---------------------------

Board consists of squares. The size of the board is m_rows x m_cols (class Board).
Coordinate system:

<pre>
              columns 
        _____________________
        |(0,0)|(0,1)|(0,2) ...
rows    |(1,0)|(1,1)|(1,2) ...
        |(2,0)|(2,1)|(2,2) ...
        |...
        |
</pre>	

In code x refers to rows and y to columns. x and y are zero based, so
x=0 is the first row.

Definitions.h
	This file contains the global definitions or the variables and structs etc. used in the project.

Board.h
	Contains the board class. m_position contains the information about each square: EMPTY, X, O.

Engine.h
	Game engine to run the game. Call setParameters() at the beginning to set game parameters. Parameters
can be changed also later. To start a new game after a game is finished call newGame(). To change
board call setBoard() (although normally only setParameters is needed).

MFCHandler.h
	Handles MFC messages and drawing. When paint-message comes to window call draw(CDC* pDC) function. It will 
use a temporary variable m_drawDC to store the given CDC pointer to be used during the drawing. Do not use 
m_drawDC outside draw()-function; use it only during the draw-execution and as long as draw() function has not finished.
In draw(CDC* pDC) call the base class version by Render::draw() which will take care of all drawing calls.

Render.h
	A pure virtual base class for drawing. Inherit your drawing class from this. drawX and drawO are optional
and if the drawing does not draw X and O separately then override drawBoard and do all drawing there (by
calling board objects data). When a paint message comes from the windows call Render classes draw() function
which starts all drawing.

How to use the code:
1) Create engine and mfc handler objects (for example in the view class):
	Engine m_engine;
	MFCHandler m_mfcHandler;

2) Set the parameters for the objects:
		m_mfcHandler.setParameters(40, CPoint(60, 20));
		m_engine.setParameters(&m_mfcHandler, 3, 3, 3);
wrap them around with try-catch if an exception is thrown - they might throw a vector allocation exception.

3) Send mouseclick information:
	m_mfcHandler.onLButtonDown(nFlags, point);

4) draw the window
		Invalidate();
		UpdateWindow();
