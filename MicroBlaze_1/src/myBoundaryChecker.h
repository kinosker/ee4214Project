/*
 * boundaryCheck.h
 *
 *  Created on: Mar 20, 2016
 *      Author: KaiHsiang
 */

#ifndef BOUNDARYCHECK_H_
#define BOUNDARYCHECK_H_



/*****************************************************************************
 *																			 *
 *																			 *
 *					---- Start of constant definition ----					 *
 *																			 *
 *																			 *
 ******************************************************************************/

#define HIT_REFLECT_SIDE			9
#define HIT_REFLECT_TOP				10
#define HIT_REFLECT_BTM				12


 // 3 possibility to hit 180
#define HIT_REFLECT_180_1			11
#define HIT_REFLECT_180_2			12
#define HIT_REFLECT_180_3			13




#define HIT_OUTER_CORNER 			11    // Hit 2 boundaries(top and left)
#define HIT_OUTER_BOX_SIDE			9    // Hit Left Right side boundary
#define HIT_OUTER_BOX_TOP			10    // Hit Top side boundary
#define HIT_OUTER_BOX_BTM			99    // Hit Bottom side boundary

//inner block
#define HIT_INNER_BOX_TOP			10    // Hit Left side boundary
#define HIT_INNER_BOX_BTM			12    // Hit Left side boundary
#define HIT_INNER_BOX_SIDE 			9    // Hit Left side boundary
#define HIT_INNER_CORNER			11    // Hit 2 boundaries(bottom and left)

#define HIT_BAR_N					11	 

#define HIT_SPEED_DEC				12
#define HIT_SPEED_ACC				13

#define HIT_ANGLE_DEC				14
#define HIT_ANGLE_ACC				15

/*****************************************************************************
 **																			 *
 *																			 *
 *					---- Start of Functions Prototype ----					 *
 *																			 *
 *																			 *
 *****************************************************************************/

/*****************************************************************************
 **
 * Check whether the ball has hit or gone over the outer boundary of the outer rectangle
 *
 * @param ball_X is the current x-coordinate of the ball
 * @param ball_Y is the current y-coordinate of the ball
 * @param myBoundary_Start_X is the x-coordinate of the start point of the boundary
 * @param myBoundary_Start_Y is the y-coordinate of the start point of the boundary
 * @param myBoundary_End_X is the x-coordinate of the end point of the boundary
 * @param myBoundary_End_Y is the y-coordinate of the end point of the boundary
 *
 * @return
 *   - values representing the side of boundary that the ball has hit
 *
 *
 ******************************************************************************/

int myBoundaryChecker_CheckOuter(int ball_X, int ball_Y);

/*****************************************************************************
 **
 * Check whether the ball has hit the inner small rectangle
 *
 * @param ball_X is the current x-coordinate of the ball
 * @param ball_Y is the current y-coordinate of the ball
 * @param myBoundary_Start_X is the x-coordinate of the start point of the boundary
 * @param myBoundary_Start_Y is the y-coordinate of the start point of the boundary
 * @param myBoundary_End_X is the x-coordinate of the end point of the boundary
 * @param myBoundary_End_Y is the y-coordinate of the end point of the boundary
 *
 * @return
 *   - values representing the side of boundary that the ball has hit
 *
 *
 ******************************************************************************/

int myBoundaryChecker_CheckInner(int ball_X, int ball_Y, int myBoundary_Start_X,
		int myBoundary_Start_Y, int myBoundary_End_X, int myBoundary_End_Y);



int myBoundaryChecker_CheckBar(int ball_X, int ball_Y, int myBoundary_Start_X,
		int myBoundary_Start_Y, int myBoundary_End_X, int myBoundary_End_Y);
#endif /* BOUNDARYCHECK_H_ */
