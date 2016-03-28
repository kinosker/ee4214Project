#ifndef TFT_DRAW_H_
#define TFT_DRAW_H_

#include "xtft.h"
#include "xparameters.h"
#include <stdio.h>
#include "xmk.h"
#include "stdlib.h"
#include "sys/init.h"
#include "semaphore.h"
#include <pthread.h>
#include <sys/timer.h> //for using sleep. need to set config_time to true
#include <sys/intr.h> //xilkernel api for interrupts
#include "String.h"
#include "ballControl.h"
// Note : We need to change TFT function to thread-safe => sw mutex.
// 		: <xtft_hw.h> defines XTFT_ASCIICHAR_OFFSET,  XTFT_CHAR_HEIGHT, XTFT_DISPLAY_HEIGHT, XTFT_DISPLAY_WIDTH
//		: Make use of disable and enable display to draw initially / reset !

/*****************************************************************************
 *																			 *
 *																			 *
 *					---- Start of constant definition ----					 *
 *																			 *
 *																			 *
 ******************************************************************************/
#define XST_SUCCESS                     0L
#define XST_FAILURE                     1L

/************************** TFT Defines *****************************/

#define TFT_DEVICE_ID    XPAR_TFT_0_DEVICE_ID
#define DDR_HIGH_ADDR    XPAR_PS7_DDR_0_S_AXI_HIGHADDR
#define TFT_FRAME_ADDR        0x10000000

#ifndef DDR_HIGH_ADDR
#warning "CHECK FOR THE VALID DDR ADDRESS IN XPARAMETERS.H"
#endif

#define COLOR_BLUE   			0x000000FF		/**<  Color - Blue */
#define COLOR_LIGHT_BLUE 		0x00CCCCFF		/**<  Color - Light Blue */
#define COLOR_BLACK   			0x0             /**<  Color - Black */
#define COLOR_WHITE 			0x00FFFFFF		/**<  Color - White */
#define COLOR_RED  				0xFF0000		/**<  Color - RED */
#define COLOR_GREEN  			0x006400        /**<  Color - GREEN */
#define COLOR_GREY  			0x9C9C9C		/**<  Color - GREY */
#define COLOR_YELLOW  			0xFFFF00		/**<  Color - YELLOW */

#define DISPLAY_COLUMNS  		640
#define DISPLAY_ROWS     		480

#define TOTAL_BRICKS			80
#define COL_BRICKS 				10
#define ROW_BRICKS 				8
#define BRICK_SIZE_LENGTH 		40
#define BRICK_SIZE_HEIGHT 		15
#define BRICK_GAP 		5

//Outer Green Rectangle (Boundary Rect)
#define OUTER_COL_START_X		60
#define OUTER_COL_START_Y		60
#define OUTER_COL_END_X			515
#define OUTER_COL_END_Y			420

//bricks column - inner smaller squares (x80)
#define COL_OFFSET				45 						// Col offset from each other
#define COL_X_START				65 						// Default start x value for the smaller square
#define COL_1_X			COL_X_START + COL_OFFSET * 0 	// Default col 1 X value to start.
#define COL_2_X			COL_X_START + COL_OFFSET * 1 	// Default col 2 X value to start.
#define COL_3_X			COL_X_START + COL_OFFSET * 2	// Default col 3 X value to start.
#define COL_4_X			COL_X_START + COL_OFFSET * 3 	// Default col 4 X value to start.
#define COL_5_X			COL_X_START + COL_OFFSET * 4 	// Default col 5 X value to start.
#define COL_6_X			COL_X_START + COL_OFFSET * 5 	// Default col 6 X value to start.
#define COL_7_X			COL_X_START + COL_OFFSET * 6 	// Default col 7 X value to start.
#define COL_8_X			COL_X_START + COL_OFFSET * 7 	// Default col 8 X value to start.
#define COL_9_X			COL_X_START + COL_OFFSET * 8 	// Default col 9 X value to start.
#define COL_10_X		COL_X_START + COL_OFFSET * 9 	// Default col 10 X value to start.
#define ROW_OFFSET				20 						// Row offset from each other
#define ROW_Y_START				65 						// Default start Y value to draw smaller square
#define ROW_Y_END		ROW_Y_START + ROW_OFFSET *  ROW_BRICKS - 1	// Default Endin Y value to draw smaller square
#define ROW_1_Y					65 						// default Y value to start.

//bar
#define BAR_START_X				247
#define BAR_START_Y				405
#define BAR_START_X_A_MINUS		247
#define BAR_START_X_S_MINUS		257
#define BAR_START_X_N			267
#define BAR_START_X_A_PLUS		307
#define BAR_START_X_S_PLUS		317
//#define BAR_END_X				327
//#define BAR_END_Y				410
#define BAR_LENGTH				80
#define BAR_LENGTH_A			10
#define BAR_LENGTH_S			10
#define BAR_LENGTH_N			40
#define BAR_HEIGHT				5

//Ball Radius
#define CIRCLE_RADIUS			7
#define CIRCLE_X 				287
#define CIRCLE_Y 				397
#define CIRCLE_ANGLE			0

//Box Containing Word SCORE
#define SCORE_WORD_BOX_START_X	550
#define SCORE_WORD_BOX_START_Y	40
#define SCORE_WORD_BOX_END_X	600
#define SCORE_WORD_BOX_END_Y	63

//Outer Box SCORE
#define SCORE_OUTER_BOX_START_X		525
#define SCORE_OUTER_BOX_START_Y		70
#define SCORE_OUTER_BOX_END_X		620
#define SCORE_OUTER_BOX_END_Y		120

//Inner Boxes of SCORE
#define SCORE_BOX1_START_X		530
#define SCORE_BOX1_END_X		555
#define SCORE_BOX2_START_X		560
#define SCORE_BOX2_END_X		585
#define SCORE_BOX3_START_X		590
#define SCORE_BOX4_END_X		615
#define SCORE_BOX_START_Y		75
#define SCORE_BOX_END_Y			115

//Time Box
#define TIME_START_X			520
#define TIME_START_Y			250
#define TIME_END_X	    		635
#define TIME_END_Y		   		270

//Speed of Ball Box
#define BALL_SPEED_START_X		520
#define BALL_SPEED_START_Y		348
#define BALL_SPEED_END_X		635
#define BALL_SPEED_END_Y		368

//Amount of Brick Left Box
#define BRICK_LEFT_START_X		520
#define BRICK_LEFT_START_Y		388
#define BRICK_LEFT_END_X		635
#define BRICK_LEFT_END_Y		408

// Amount of columns to be coloured
#define COL_YELLOW				2
#define COL_BACKGROUND		COL_BRICKS - COL_YELLOW

/*****************************************************************************
 **																			 *
 *																			 *
 *					---- Start of Functions Prototype ----					 *
 *																			 *
 *																			 *
 *****************************************************************************/

/*****************************************************************************
 **
 * Initialise the TFT display
 *
 * @param  XTft_SetPixel is the TFT device ID
 * @param InstancePtr is the Xtft pointer
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_init(u32 TftDeviceId, XTft *InstancePtr);

/*****************************************************************************/
/**
 * Thread-safe set pixel (instead of using setpixel, use this!)
 *
 * @param  Tft is a pointer to the XTft instance.
 * @param  colVal is the x cordinate to draw the circle
 * @param  rowVal is the y cordinate to draw the circle
 * @param  colour determines the colour of the circle
 * @param  mutex_sw_tft software mutex that enable thread safe setting of pixel
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
static int tft_setPixelSafe(XTft *InstancePtr, u32 colVal, u32 rowVal,
		u32 colour, pthread_mutex_t mutex_sw_tft);

/*****************************************************************************
 **
 * Draw initial GUI
 *	- Overall Background
 *	- Scores background
 *	- CurrentBall Speed
 *	- Number of Bricks Left
 *	- MSG queue to all threads? (still to be decided)
 *
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *****************************************************************************/
int tft_intialDraw(XTft *InstancePtr);

/*****************************************************************************
 **
 * Brain of tft update
 *	- Fire threads to update based on timer / mailbox? (still to be determined)
 *	- Update params based on msg queue?
 *
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *****************************************************************************/
int tft_updateDisplay(XTft *InstancePtr);

/*****************************************************************************
 **
 * Update column for the bricks to be drawn
 *	- Calculate difference of currentBricks and future bricks
 *		- Add / Remove based on it from BOTTOM to TOP!!!
 *		- For loop to add/remove => use colour to draw !! (May change colour due to requirement)
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  col_x is the position of X axis to start drawing.
 * @param  currentBricks is the number of bricks on the screen now.
 * @param  futureBricks is the number of bricks that is to be updated.
 * @param  currentColour is the colour of the bricks on the screen now.
 * @param  futureColour is the colour of the bricks that is to be updated.
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *****************************************************************************/
int tft_updateColumn(XTft *InstancePtr, const int col_x, int currentBricks,
		int futureBricks, unsigned int currentColour, unsigned int futureColour);

/*****************************************************************************
 **
 * Update score based on tft_writeInteger()
 *	- Depending if you wan to save resources... can old score compare new score to save print
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  score is the new score to be updated
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *****************************************************************************/
int tft_updateScore(XTft *InstancePtr, int score);

/*****************************************************************************
 **
 * Update speed based on tft_writeInteger()
 *	- Depending if you wan to save resources... can old score compare new score to save print
 *	- Handle different number of digit!
 *	- Print 000 -> 009  instead of 1 to 9?
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  speed is the new score to be updated
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *****************************************************************************/
int tft_updateSpeed(XTft *InstancePtr, int speed);

/****************************************************************************
 **
 * Update bricks left based on tft_writeInteger()
 *	- Handle single digit please!!!
 *	- Print 00 -> 09 instead of 1 to 9
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  bricksLeft is the new score to be updated
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *****************************************************************************/
int tft_updateBricksLeft(XTft *InstancePtr, int bricksLeft);

/****************************************************************************
 **
 * Update time when the game has started by tft_writeString() and tft_writeInteger()
 *	- handle 2 digits in minutes and seconds
 *
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  gameTime is the amount of time has passed from the start of the game
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *****************************************************************************/
int tft_updateTime(XTft *InstancePtr, int gameTime);

/*****************************************************************************
 **
 * Precondition : Max of 5 digits value
 * Write integer value the TFT.
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  x is the X axis cordinate to start writing the Integer
 * @param  x is the Y axis cordinate to start writing the Integer
 * @param  value is the integer you wished to print (Max 5 digits)
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *****************************************************************************/
int tft_writeInteger(XTft *InstancePtr, int x, int y, const int value,
		u32 foreGround, u32 backGround);

/*****************************************************************************
 **
 * Write a string of characters to the TFT.
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  x is the X axis cordinate to start writing the character
 * @param  x is the Y axis cordinate to start writing the character
 * @param  CharValue is a pointer to the character array to be written
 *   to the TFT screen.
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 * @note   None.
 *
 ******************************************************************************/
int tft_writeString(XTft *InstancePtr, int x, int y, const char *CharValue,
		u32 foreGround, u32 backGround);

/*****************************************************************************
 **
 * Add circle based on tft_drawCircle() to add it on the screen
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  x0 is the x cordinate to draw the circle
 * @param  y0 is the y cordinate to draw the circle
 * @param  radius determines how big is the circle
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_addCircle(XTft *InstancePtr, int x0, int y0, int radius);

/*****************************************************************************
 **
 * Remove circle based on tft_drawCircle() to remove it on the screen
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  x0 is the x cordinate to draw the circle
 * @param  y0 is the y cordinate to draw the circle
 * @param  radius determines how big is the circle
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_removeCircle(XTft *InstancePtr, int x0, int y0, int radius);

/*******************************************************************************
 * Draw a solid circle on the Tft display based on midpoint circle algorithm.
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  x0 is the x cordinate to draw the circle
 * @param  y0 is the y cordinate to draw the circle
 * @param  radius determines how big is the circle
 * @param  colour determines the colour of the circle
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_drawCircle(XTft *InstancePtr, int x0, int y0, int radius,
		unsigned int colour);

/*****************************************************************************
 **
 * Draws a brick based on tft_drawLine() to add it on the screen
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  ColStartPos is the Start point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowStartPos is the Start point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  ColEndPos is the End point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowEndPos is the End point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_addBrick(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos);

/*****************************************************************************
 **
 * Remove a brick based on tft_drawLine() to remove it on the screen
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  ColStartPos is the Start point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowStartPos is the Start point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  ColEndPos is the End point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowEndPos is the End point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_removeBrick(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos);

/*****************************************************************************
 **
 * Fill a brick on the screen
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  ColStartPos is the Start point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowStartPos is the Start point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  ColEndPos is the End point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowEndPos is the End point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  colour is the Color value to be filled for the brick.
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_fillBrick(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos, unsigned int colour);

/*****************************************************************************
 **
 * Add a bar based on tft_drawLine() to add it on the screen
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  ColStartPos is the Start point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowStartPos is the Start point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  ColEndPos is the End point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowEndPos is the End point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  colour is the Color Value to be put at pixel.
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_addBar(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos, unsigned int colour);

/*****************************************************************************
 **
 * Move the circle
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/

int tft_moveCircle(XTft *InstancePtr, int x0, int y0, int future_x0, int future_y0, int speed);

/*****************************************************************************
 **
 * Move the bar to the left
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_moveBarLeft(XTft *InstancePtr, unsigned int holdTime);

/*****************************************************************************
 **
 * Move the bar to the right
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_moveBarLeft(XTft *InstancePtr, unsigned int holdTime);

/*****************************************************************************
 **
 * Draws a line between two points with a specified color.
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  ColStartPos is the Start point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowStartPos is the Start point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  ColEndPos is the End point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowEndPos is the End point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  colour is the Color Value to be put at pixel.
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int tft_drawLine(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos, unsigned int colour);

/*****************************************************************************
 **
 * Draw a rectangle base of TftDrawLine
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  ColStartPos is the Start point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowStartPos is the Start point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  ColEndPos is the End point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowEndPos is the End point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  colour is the Color Value to be put at pixel.
 *
 *
 ******************************************************************************/
void tft_drawRect(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos, u32 colour);

/*****************************************************************************
 **
 * Fill a rectangle
 *
 * @param  InstancePtr is a pointer to the XTft instance.
 * @param  ColStartPos is the Start point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowStartPos is the Start point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  ColEndPos is the End point of Column.
 *   The valid value is 0 to (XTFT_DISPLAY_WIDTH - 1).
 * @param  RowEndPos is the End point of Row.
 *   The valid value is 0 to (XTFT_DISPLAY_HEIGHT - 1).
 * @param  colour is the Color Value to be filled.
 *
 *
 ******************************************************************************/
void tft_fillRect(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos, u32 colour);

/*****************************************************************************
 **																			 *
 *																			 *
 *					---- Start of Helper Function Prototype ----			 *
 *																			 *
 *																			 *
 *****************************************************************************/

/*****************************************************************************
 **
 * Converts integer to ascii
 *
 * @param  n is the integer to be converted
 * @param  s is the char buffer to store the conversion
 *
 *
 ******************************************************************************/
void itoa(int n, char s[]);

/*****************************************************************************
 **
 * Reverse the char array
 *
 * @param  s is the char array to be reversed
 *
 *
 ******************************************************************************/
void reverse(char s[]);

#endif /* TFT_DRAW_H_ */
