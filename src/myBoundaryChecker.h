/*
 * boundaryCheck.h
 *
 *  Created on: Mar 20, 2016
 *      Author: KaiHsiang
 */

#ifndef BOUNDARYCHECK_H_
#define BOUNDARYCHECK_H_

#include "TFT_Draw.h"

/*****************************************************************************
 *																			 *
 *																			 *
 *					---- Start of constant definition ----					 *
 *																			 *
 *																			 *
 ******************************************************************************/

#define HIT_LEFTBOUNDARY  				1    // Hit Left side boundary
#define HIT_RIGHTBOUNDARY  				2    // Hit Right side boundary
#define HIT_TOPBOUNDARY 				3    // Hit TOP side boundary
#define HIT_BOTTOMBOUNDARY  			4    // Hit Bottom side boundary
#define HIT_2_BOUNDARY_TOP_LEFT 		5    // Hit 2 boundaries(top and left)
#define HIT_2_BOUNDARY_TOP_RIGHT 		6    // Hit 2 boundaries(top and right)
#define HIT_2_BOUNDARY_BOTTOM_LEFT 		7    // Hit 2 boundaries(bottom and left)
#define HIT_2_BOUNDARY_BOTTOM_RIGHT 	8    // Hit 2 boundaries(bottom and left)

//inner block
#define HIT_INNER_LEFTBOUNDARY  				11    // Hit Left side boundary
#define HIT_INNER_RIGHTBOUNDARY  				12    // Hit Right side boundary
#define HIT_INNER_TOPBOUNDARY 					13    // Hit TOP side boundary
#define HIT_INNER_BOTTOMBOUNDARY  				14    // Hit Bottom side boundary
#define HIT_2_INNER_BOUNDARY_TOP_LEFT 			15    // Hit 2 boundaries(top and left)
#define HIT_2_INNER_BOUNDARY_TOP_RIGHT 			16    // Hit 2 boundaries(top and right)
#define HIT_2_INNER_BOUNDARY_BOTTOM_LEFT 		17    // Hit 2 boundaries(bottom and left)
#define HIT_2_INNER_BOUNDARY_BOTTOM_RIGHT 		18    // Hit 2 boundaries(bottom and left)

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

int myBoundaryChecker_CheckOuter(int ball_X, int ball_Y, int myBoundary_Start_X,
		int myBoundary_Start_Y, int myBoundary_End_X, int myBoundary_End_Y);

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
#endif /* BOUNDARYCHECK_H_ */
