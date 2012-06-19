// GLUTSingleton.cpp
//   Demonstrates Singleton Pattern for putting C++ wrapper around GLUT.
//   Initiates our investigation of TicTacToe Game implementation.

#include <cstdlib>	/* For exit(int ); */
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;
#include "glut.h" /* Use this for local directory install of GLUT */
/* #include <GL/glut.h> Use this on a full system install of GLUT */

#define SHOW_DIAGNOSTICS

// This enum type is used to describe the status of the nine squares
// in a tic-tac-toe game grid.
enum TicTacSquare {EMPTY, PLAYER, COMPUTER};
float PI = 3.141592654;
class TicTacToeGame
{
public:
	// Initialize private data as well as set up GLUT window.
	TicTacToeGame() {
		windowWidth=450;
		windowHeight=450;
		initialULx=100;
		initialULy=100;
		clearTheSquares();
		glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
		glutInitWindowSize( windowWidth, windowHeight );
		glutInitWindowPosition( initialULx, initialULy );
		glutCreateWindow( "Tic-Tac-Toe" );
		glClearColor(1.0, 1.0, 1.0, 0.0); /* Clear with white */
		glColor3f(0.0, 0.0, 0.0); /* Current draw color is black */
	}
	// Call clearTheSquares when resetting a game.
	static void clearTheSquares() {
		catGame=false;
		computerGame=false;
		playerGame=false;
		gameOver=false;
		for(int i=0; i<9; i++)
			TheSquares[i]=EMPTY;
	}
	// Complete all of the OpenGL calls to draw the current game state.
	static void display() {
		glClear( GL_COLOR_BUFFER_BIT );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt(0,0,1,0,0,0,0,1,0);
		float angle;
		// Set the radius of the circle to fit within the square
		float rad = (windowWidth <= windowHeight) ? (.30*windowWidth)/2 : (.30*windowHeight)/2;
		/* Draw the squares */
		for(int i=0; i<9; i++) {
			glColor3f(1.0, 1.0, 1.0); // Change drawing color to white
			// Draw a rectangle using the preset size percentages
			glRectf( TheSquarePercents[i][0]*windowWidth, TheSquarePercents[i][1]*windowHeight,
					 TheSquarePercents[i][2]*windowWidth, TheSquarePercents[i][3]*windowHeight );
			if (TheSquares[i]==COMPUTER) {
				glColor3f(0.0, 0.0, 1.0);		// Blue if COMPUTER.
				// Draw an O
				// glBegin(...) and glEnd() must surround drawing code
				// GL_LINE_LOOP creates lines between vertexes
				glBegin(GL_LINE_LOOP);			// Begin drawing phase
				float xCenter = (TheSquarePercents[i][0]+.16)*windowWidth;	// x-coordinate for center of circle
				float yCenter = (TheSquarePercents[i][1]+.16)*windowHeight;	// y-coordinate for center of circle
					for (int j=0; j<100; j++) {
						angle = j*2*PI/100;
						// Create a circle using 100 vertices connected with lines
						glVertex2f(xCenter + (cos(angle) * rad), yCenter + (sin(angle) * rad));
					}
				glEnd();						// End drawing phase
			} else if (TheSquares[i]==PLAYER) {
				glColor3f(1.0, 0.0, 0.0);		// Red if PLAYER.
				// Draw an X
				glBegin(GL_LINE_LOOP);			// Begin drawing phase
					// Create vertex point at bottom left of square
					glVertex2f(TheSquarePercents[i][0]*windowWidth,
							   TheSquarePercents[i][1]*windowHeight);
					// Create vertex point at top right of square
					glVertex2f(TheSquarePercents[i][2]*windowWidth,
							   TheSquarePercents[i][3]*windowHeight);
				glEnd();						// End drawing phase
				glBegin(GL_LINE_LOOP);			// Begin new drawing phase
					// Create vertex point at top left of square
					glVertex2f(TheSquarePercents[i][0]*windowWidth,
							   (TheSquarePercents[i][1]+.32)*windowHeight);
					// Create vertex point at bottom right of square
					glVertex2f(TheSquarePercents[i][2]*windowWidth,
							   (TheSquarePercents[i][3]-.32)*windowHeight);
				glEnd();						// End new drawing phase
			}
		}
		/* Draw the Tic-Tac-Toe grid as a set of four overlapping thin rectangles */
		if (catGame) {
			glColor3f(.75, 0.0, 1.0); // If cat's game, grid color is purple
		} else if (computerGame) {
			glColor3f(1.0, 0.0, 0.0); // If computer won game, grid color is red
		} else if (playerGame) {
			glColor3f(0.0, 0.0, 1.0); // If player won game, grid color is blue
		} else {
			glColor3f(0.0, 0.0, 0.0); // If game is still in play, grid color is black
		}
		glRectf( 0.0, 0.32*windowHeight, 1.0*windowWidth, 0.34*windowHeight );
		glRectf( 0.0, 0.65*windowHeight, 1.0*windowWidth, 0.67*windowHeight );
		glRectf( 0.32*windowWidth, 0.0, 0.34*windowWidth, 1.0*windowHeight );
		glRectf( 0.65*windowWidth, 0.0, 0.67*windowWidth, 1.0*windowHeight );
		glMatrixMode( GL_PROJECTION );
		/* If the game is over, draw a line through the winning squares */
		if (playerGame || computerGame) {
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
				if (winningSquare%3==0 && winningSquareTwo==(winningSquare+2)) {		// If there is a horizontal win
					glVertex2f(0, (TheSquarePercents[winningSquare][1]+.16)*windowHeight);
					glVertex2f(windowWidth, (TheSquarePercents[winningSquare][1]+.16)*windowHeight);
				} else if (winningSquare < 3 && winningSquareTwo==(winningSquare+6)) {	// If there is a vertical win
					glVertex2f((TheSquarePercents[winningSquare][0]+.16)*windowWidth, 0);
					glVertex2f((TheSquarePercents[winningSquare][0]+.16)*windowWidth, windowHeight);
				} else if (winningSquare == 0) {										// If there is a diagonal win
					glVertex2f(0,0);
					glVertex2f(windowWidth, windowHeight);
				} else if (winningSquare == 2) {
					glVertex2f(0, windowHeight);
					glVertex2f(windowWidth, 0);
				}
			glEnd();
		}
		glFlush();	// Make sure the pictures are drawn and not simply stored in a buffer
	}
	// If the user reshapes the window with the mouse, reset OpenGL view.
	static void reshape(int w, int h) {
		windowWidth=w;
		windowHeight=h;
		glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluOrtho2D( 0, w, 0, h );
		glMatrixMode( GL_MODELVIEW );
	}
	// Capture keyboard input to reset/clear game and to quit.
	static void keyboard(unsigned char key, int x, int y) {
		#ifdef SHOW_DIAGNOSTICS
		cout << "keyboard(" << key << "," << x << "," << y << ")" << endl;
		#endif
		if( key=='Q' || key=='q' )
			exit(1);
		if( key=='C' || key=='c' || key=='R' || key=='r' )
			clearTheSquares();
		glutPostRedisplay();
	}
	// Convert GLUT mouse clicks to OpenGL 2D position, determine if square should be modified.
	static void mouse(int button, int state, int x, int y) {
		checkForWinner();
		if (!gameOver && button==0 && state==0) { // Don't respond if gameOver, or not left button press.
			GLfloat xpos=1.0*x/windowWidth; // These three lines convert mouse(x,y) to square index value.
			GLfloat ypos=1.0*(windowHeight-y)/windowHeight; 
			int squareIndex = 3*static_cast<int>(ypos/0.33)+static_cast<int>(xpos/0.33); // Trick.
			if (TheSquares[squareIndex]==EMPTY) {
				TheSquares[squareIndex]=PLAYER;
				makeComputerPlay();	// Tell the computer to makes its move
			}
			#ifdef SHOW_DIAGNOSTICS
			cout << "square(" << squareIndex << ")" << endl;
			#endif
			glutPostRedisplay();
		} // If statement
	}
	// Here's where you need to start your work, can use lots of extra class methods to help.
	static void checkForWinner()
	{
		int squareCount = 0;
		for (int i=0; i<8; i++) {		// Cycle through all rows of the SolutionSets array
			// The game is over if all the squares in a sequence are highlighted
			// Computer Wins
			if (TheSquares[SolutionSets[i][0]] == COMPUTER && 
				TheSquares[SolutionSets[i][1]] == COMPUTER &&
				TheSquares[SolutionSets[i][2]] == COMPUTER) {
					computerGame = true;
					gameOver = true;
			  // Player Wins
			} if (TheSquares[SolutionSets[i][0]] == PLAYER && 
				  TheSquares[SolutionSets[i][1]] == PLAYER &&
				  TheSquares[SolutionSets[i][2]] == PLAYER) {
					  playerGame = true;
					  gameOver = true;
			  // Cat's Game
			} if (TheSquares[SolutionSets[i][0]] != EMPTY && 
				TheSquares[SolutionSets[i][1]] != EMPTY &&
				TheSquares[SolutionSets[i][2]] != EMPTY) {
					squareCount += 1;	// Count the number of occupied squares
			} if (squareCount == 8 && !computerGame && !playerGame) {
					  catGame = true;
					  gameOver = true;
			} if (gameOver) {
				winningSquare=SolutionSets[i][0];
				winningSquareTwo=SolutionSets[i][2];
				break;
			}
		}
	}
	// Tells the computer how to play
	static void makeComputerPlay()
	{
		int playerCount = 0;
		int computerCount = 0;
		int emptyCount = 0;
		int win[2] = {-1, -1};
		int block[2] = {-1, -1};
		int moveToWin[2] = {-1, -1};
		int jHolder = 0;
		bool played = false;
	    checkForWinner(); // Just a suggestion, do this before wasting time looking for a play.
	    if( !gameOver ) {
			for (int i=0; i<8; i++) {		// For every row in SolutionSets
				for (int j=0; j<3; j++) {	// For every column in SolutionSets
					if (TheSquares[SolutionSets[i][j]] == PLAYER) {
						playerCount ++;		// If a square is occupied by the player, increment the count
					} else if (TheSquares[SolutionSets[i][j]] == COMPUTER) {
						computerCount ++;	// If a square is occupied by the computer, increment the count
					} else {
						emptyCount ++;		// If a square is empty, increment the count
						jHolder = j;		// Keep track of where the empty block is
					}
				} // For loop
				if (computerCount == 2 && emptyCount == 1) {		// If the computer can win
					// Keep track of where the computer must play to win
					win[0] = i;
					win[1] = jHolder;
					// Exit the for loop and win the game
					break;
				} else if (playerCount == 2 && emptyCount == 1) {	// If the computer can block
					// Keep track of where the computer must play to block
					block[0] = i;
					block[1] = jHolder;
				} else if (computerCount == 1 && emptyCount == 2) {	// If the computer can move to win
					// Keep track of where the computer must play
					moveToWin[0] = i;
					moveToWin[1] = jHolder;
				}
				// Reset the counters
				playerCount = 0;
				computerCount = 0;
				emptyCount = 0;
			} // For loop
			if (win[0] > -1) {								// If the computer can win and if the computer has not played
				TheSquares[SolutionSets[win[0]][win[1]]] = COMPUTER;
				played = true;
			} else if (block[0] > -1 && !played) {			// If the computer can block and if the computer has not played
				TheSquares[SolutionSets[block[0]][block[1]]] = COMPUTER;
				played = true;
															// If the player is planning a corner fork, play on a side
			}
			if (TheSquares[0] == PLAYER && TheSquares[8] == PLAYER ||
				TheSquares[2] == PLAYER && TheSquares[6] == PLAYER) {
						   if (TheSquares[1] == EMPTY && !played) {
							   TheSquares[1] = COMPUTER;
							   played = true;
						   }
			}												// If a player is planning a different corner fork, play on the bottom, left corner
			/********************************************************
			// Uncomment this line for a computer that never loses.
			if (TheSquares[1] == PLAYER && TheSquares[3] == PLAYER) {
				if (TheSquares[0] == EMPTY && !played) {
					TheSquares[0] = COMPUTER;
					played = true;
				}
			}
			********************************************************/
															// If the player is planning an "L" fork, play on the bottom, left corner
			if ((TheSquares[1] == PLAYER && TheSquares[6] == PLAYER) ||
				   TheSquares[2] == PLAYER && TheSquares[3] == PLAYER) {
				if (TheSquares[0] == EMPTY && !played) {
					TheSquares[0] = COMPUTER;
					played = true;
				}
															// If the player is planning an "L" fork, play on the bottom, right corner
			} else if ((TheSquares[1] == PLAYER && TheSquares[8] == PLAYER) ||
					   (TheSquares[0] == PLAYER && TheSquares[5] == PLAYER)) {
				if (TheSquares[2] == EMPTY && !played) {
					TheSquares[2] = COMPUTER;
					played = true;
				}
			}
			if (moveToWin[0] > -1 && !played) {				// If the computer can move to make two in a row
				TheSquares[SolutionSets[moveToWin[0]][moveToWin[1]]] = COMPUTER;
				played = true;
			} 
			if (TheSquares[4] == EMPTY && !played) {		// If play has not been made, play in center
				TheSquares[4] = COMPUTER;
				played = true;
			}
			for (int i=0; i < 9; i+=2) {					// If play has not been made, play in empty corner
				if (!played && TheSquares[i] == EMPTY) {
					TheSquares[i] = COMPUTER;
					played = true;
					break;
				}
			}
			for (int i=1; i < 8; i+=2) {					// If play has not been made, play to empty side
				if (!played && TheSquares[i] == EMPTY) {
					TheSquares[i] = COMPUTER;
					played = true;
					break;
				}
			}
		}	// End if statement
	    checkForWinner(); // Make sure status is changed if needed before PLAYER goes next.
	}
	// A singleton class model allows for one and only one object instance.
	static TicTacToeGame* getInstanceOf() {
		if( !instanceFlag ) {
			singleTon = new TicTacToeGame();
			instanceFlag = true;
		}
		return singleTon;
	}
	~TicTacToeGame() {
		instanceFlag = false;
	}
private:
	// All of the data members of the singleton are static, only one instance.
	static bool		instanceFlag;
	static TicTacToeGame* 	singleTon;
	static int		windowWidth;
	static int		windowHeight;
	static int		initialULx;
	static int		initialULy;
	static TicTacSquare 	TheSquares[9];
	static GLfloat 		TheSquarePercents[9][4];
	static int		SolutionSets[8][3];
	static bool			gameOver;
	static bool 		computerGame;
	static bool			playerGame;
	static bool			catGame;
	static int			winningSquare;
	static int			winningSquareTwo;
};

/***** The Singleton member data are declared here *****/
bool TicTacToeGame::instanceFlag=false;
TicTacToeGame* TicTacToeGame::singleTon=NULL;
int TicTacToeGame::windowWidth;
int TicTacToeGame::windowHeight;
int TicTacToeGame::initialULx;
int TicTacToeGame::initialULy;
TicTacSquare TicTacToeGame::TheSquares[9];
// This multi-D array describes the RectF percentages of 
// width and height to reach the LL and UR corners of
// each game square in the tic-tac-toe grid.
GLfloat TicTacToeGame::TheSquarePercents[9][4]=
  {	{   0,   0,0.32,0.32},
	{0.34,   0,0.65,0.32},
	{0.67,   0,   1,0.32},
	{   0,0.34,0.32,0.65},
	{0.34,0.34,0.65,0.65},
	{0.67,0.34,   1,0.65},
	{   0,0.67,0.32,   1},
	{0.34,0.67,0.65,   1},
	{0.67,0.67,   1,   1} };
// You'll want to use these sets for searching out the current status
// of gameOver or not.  For example, if squares {0,1,2} all contain
// PLAYER, gameOver should be set true, no more plays required.
int TicTacToeGame::SolutionSets[8][3]=
  {	{0,1,2}, {3,4,5}, {6,7,8}, // Rows of winning
	{0,3,6}, {1,4,7}, {2,5,8}, // Columns of winning
	{2,4,6}, {0,4,8} }; // Diagonals of winning
bool TicTacToeGame::gameOver=false;
bool TicTacToeGame::catGame=false;
bool TicTacToeGame::computerGame=false;
bool TicTacToeGame::playerGame=false;
int TicTacToeGame::winningSquare=-1;
int TicTacToeGame::winningSquareTwo=-1;
/*******************************************************************/

/*******************************************************************/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	TicTacToeGame*   TheGame = TicTacToeGame::getInstanceOf();
	glutDisplayFunc( TheGame->display );
 	glutReshapeFunc( TheGame->reshape );
	glutKeyboardFunc(TheGame->keyboard);
	glutMouseFunc(   TheGame->mouse   );
	glutMainLoop();

	return 0;
/*******************************************************************/
}