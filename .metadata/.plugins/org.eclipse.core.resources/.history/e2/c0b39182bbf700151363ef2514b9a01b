/*
 * ballControl.h
 *
 *  Created on: Mar 22, 2016
 *      Author: KaiHsiang
 */

#ifndef BALLCONTROL_H_
#define BALLCONTROL_H_

#include "myBoundaryChecker.h"
#include "TFT_Draw.h"

/*****************************************************************************
 *																			 *
 *																			 *
 *					---- Start of constant definition ----					 *
 *																			 *
 *																			 *
 ******************************************************************************/
#define FRAME_PER_SEC			25
#define MINIMUM_SPEED			50/FRAME_PER_SEC
#define MAXIMUM_SPEED			1000/FRAME_PER_SEC
#define INITIAL_SPEED 			250/FRAME_PER_SEC	//250pixels per sec -> 25fps = 10pixels
#define BAR_AC_DECELERATION 	100/FRAME_PER_SEC	//100pixels per sec -> 25fps = 4pixels (+4 when hit S+ part of bar, -4 when hit S- part of bar)
#define SCORE_ACCELERATION		25/FRAME_PER_SEC	//25pixels per sec -> 25fps = 1pixels (+1 when the score is increase by 10)

/*************************************************angle definition*****************************************/
#define MINIMUM_ANGLE_ON_BAR			15
#define MAXIMUM_ANGLE_ON_BAR			165
#define INITIAL_ANGLE					0
#define BAR_INCREASE_DECREASE			15// the increase/decrease angle when the ball hit A+/A- will be 15



// 10 pts -> Speed up by 25

typedef struct {

	int dir, speed, x, y;

} ball_msg;

/*****************************************************************************
 **																			 *
 *																			 *
 *					---- Start of Functions Prototype ----					 *
 *																			 *
 *																			 *
 *****************************************************************************/

/*****************************************************************************
 **
 * Control the change of speed according to the condiions
 *
 * @param InstancePtr is the Xtft pointer
 * @param ball_X is the X-coordinate of the ball currently
 * @param ball_Y is the Y-coordinate of the ball currently
 * @param score is the current score in game
 * @param speed is the current speed of the ball
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int myBallControl_SpeedChange(XTft *InstancePtr, int ball_X, int ball_Y,int score, int speed);

/*****************************************************************************
 **
 * Control the change of speed according to the condiions
 *
 * @param InstancePtr is the Xtft pointer
 * @param ball_X is the X-coordinate of the ball currently
 * @param ball_Y is the Y-coordinate of the ball currently
 * @param angle is the current angle in game
 *
 *
 * @return
 *   - XST_SUCCESS if successful.
 *   - XST_FAILURE if unsuccessful.
 *
 *
 ******************************************************************************/
int myBallControl_AngleChange(XTft *InstancePtr, int ball_X, int ball_Y, int angle);


int myBallControl_getNumberOfSteps(int ballSpeed_pixel);
int myBallControl_updateBallSpeed(int ballSpeed, int speedGain);
int myBallControl_getBallSpeedPerFrame(int ballSpeed);
int myBallControl_getNumberOfSteps(int ballSpeed_pixel);

ball_msg myBallControl_getBallLocation (int ballSpeed_pixel, ball_msg currentLocation);
ball_msg myBallControl_getBallLocation_step(int numberOfSteps, int ballSpeed_pixel, ball_msg currentLocation, ball_msg endLocation);

#endif /* BALLCONTROL_H_ */
