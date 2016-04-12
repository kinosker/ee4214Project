/*
 * myCommon.h
 *
 *  Created on: Mar 30, 2016
 *      Author: KaiHsiang
 */

#ifndef MYCOMMON_H_
#define MYCOMMON_H_


#define COLOR_BLUE   			0x000000FF		/**<  Color - Blue */
#define COLOR_LIGHT_BLUE 		0x00CCCCFF		/**<  Color - Light Blue */
#define COLOR_BLACK   			0x0             /**<  Color - Black */
#define COLOR_WHITE 			0x00FFFFFF		/**<  Color - White */
#define COLOR_RED  				0xFF0000		/**<  Color - RED */
#define COLOR_GREEN  			0x006400        /**<  Color - GREEN */
#define COLOR_GREY  			0x9C9C9C		/**<  Color - GREY */
#define COLOR_YELLOW  			0xFFFF00		/**<  Color - YELLOW */

#define FPS						25

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
#define ROW_Y_END		ROW_Y_START + ROW_OFFSET *  (ROW_BRICKS - 1)	// Default Endin Y value to draw smaller square
#define ROW_1_Y					65 						// default Y value to start.



#define ALL_COL_X   COL_1_X, \
                    COL_2_X, \
                    COL_3_X, \
                    COL_4_X, \
                    COL_5_X, \
                    COL_6_X, \
                    COL_7_X, \
                    COL_8_X, \
                    COL_9_X, \
                    COL_10_X
                    

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

//Game Status Box
#define GAME_START_X			520
#define GAME_START_Y			175
#define GAME_END_X				635
#define GAME_END_Y				195

// Amount of columns to be coloured
#define COL_YELLOW				2
#define COL_BACKGROUND		COL_BRICKS - COL_YELLOW

#define SEM_SUCCESS			0

#define MAX_TIMER_THREAD			1 // timer thread works alone...
#define MAX_BRICKS_THREAD			10
#define MAX_BALL_THREAD				1
#define MAX_CONTROLLER_THREAD		1
#define MAX_MISC_THREAD				1

#define FRAME_PER_SEC			25
#define INITIAL_SPEED 			250/FRAME_PER_SEC	//250pixels per sec -> 25fps = 10pixels



#define RESUME_STATUS				0
#define PAUSE_STATUS				1
#define RESTART_STATUS				2
#define WIN_STATUS					3
#define LOSE_STATUS					4


typedef struct
{

  int dir,speed;
  float x,y;
  
} ball_msg;

typedef struct
{

  int start_x, start_y, end_x, end_y;

} bar_msg;

typedef struct
{

  int score, ballSpeed, bricksLeft;

} misc_msg;


typedef struct
{
  char columnNumber;
  int bricksLeft;
  uint colour;

}brick_msg;

typedef struct
{
  int totalBricksLeft;      // total bricks left to be updated
  brick_msg allMsg[MAX_BRICKS_THREAD];

}allBricks_msg;


typedef struct
{
  char status;
  int score;                    // score to be updated
  ball_msg msg_ball;            // ball location to be update.
  allBricks_msg msg_Allbricks;  // bricks to be updated

}allProcessor_msg;




#endif /* MYCOMMON_H_ */
