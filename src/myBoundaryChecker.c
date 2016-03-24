/*
 * boundaryCheck.c
 *
 *  Created on: Mar 20, 2016
 *      Author: KaiHsiang
 */

#include "myBoundaryChecker.h"

int myBoundaryChecker_CheckOuter(int ball_X, int ball_Y, int myBoundary_Start_X,
		int myBoundary_Start_Y, int myBoundary_End_X, int myBoundary_End_Y) //speed????? angle???
{
	int side_ball_X = ball_X + CIRCLE_RADIUS;
	int side_ball_Y = ball_Y + CIRCLE_RADIUS;

	if (side_ball_X <= myBoundary_Start_X) { // left boundary
		//side_ball_X = myBoundary_Start_X;
		return HIT_LEFTBOUNDARY; // return 1
	}
	if (side_ball_X >= myBoundary_End_X) {	//right boundary
		//side_ball_X = myBoundary_End_X;
		return HIT_RIGHTBOUNDARY;		// return 2
	}
	if (side_ball_Y <= myBoundary_Start_Y) { // top boundary
		//side_ball_Y = myBoundary_Start_Y;
		return HIT_TOPBOUNDARY; // return 3
	}
	if (side_ball_Y >= myBoundary_End_Y) { // bottom boundary
		//side_ball_Y = myBoundary_End_Y;
		return HIT_BOTTOMBOUNDARY;		// return 4
	}

	/*******************************************four corners checking****************************************/
	// left and top boundary
	if ((side_ball_X <= myBoundary_Start_X)
			&& (side_ball_Y <= myBoundary_Start_Y)) {
		//side_ball_X = myBoundary_Start_X;
		//side_ball_Y = myBoundary_Start_Y;
		return HIT_2_BOUNDARY_TOP_LEFT; // return 5
	}
	// right and top boundary
	if ((side_ball_X >= myBoundary_End_X)
			&& (side_ball_Y <= myBoundary_Start_Y)) {
		//side_ball_X = myBoundary_End_X;
		//side_ball_Y = myBoundary_Start_Y;
		return HIT_2_BOUNDARY_TOP_RIGHT; // return 6
	}
	// left and bottom boundary
	if ((side_ball_X <= myBoundary_Start_X)
			&& (side_ball_Y >= myBoundary_End_Y)) {
		//side_ball_X = myBoundary_Start_X;
		//side_ball_Y = myBoundary_End_Y;
		return HIT_2_BOUNDARY_BOTTOM_LEFT; // return 7
	}
	// right and bottom boundary
	if ((side_ball_X >= myBoundary_End_X)
			&& (side_ball_Y >= myBoundary_End_Y)) {
		//side_ball_X = myBoundary_End_X;
		//side_ball_Y = myBoundary_End_Y;
		return HIT_2_BOUNDARY_BOTTOM_RIGHT; // return 8
	}
	return 0;
}

int myBoundaryChecker_CheckInner(int ball_X, int ball_Y, int myBoundary_Start_X,
		int myBoundary_Start_Y, int myBoundary_End_X, int myBoundary_End_Y) //speed????? angle???
{
	int side_ball_X = ball_X + CIRCLE_RADIUS;
	int side_ball_Y = ball_Y + CIRCLE_RADIUS;

	if (side_ball_X >= myBoundary_Start_X) { // left boundary
		//side_ball_X = myBoundary_Start_X;
		return HIT_INNER_LEFTBOUNDARY; // return 11
	}
	else if (side_ball_X <= myBoundary_End_X) {	//right boundary
		//side_ball_X = myBoundary_End_X;
		return HIT_INNER_RIGHTBOUNDARY;		// return 12
	}
	else if (side_ball_Y >= myBoundary_Start_Y) { // top boundary
		//side_ball_Y = myBoundary_Start_Y;
		return HIT_INNER_TOPBOUNDARY; // return 13
	}
	else if (side_ball_Y <= myBoundary_End_Y) { // bottom boundary
		//side_ball_Y = myBoundary_End_Y;
		return HIT_INNER_BOTTOMBOUNDARY;		// return 14
	}

	/*******************************************four corners checking****************************************/
	// left and top boundary
	else if ((side_ball_X >= myBoundary_Start_X)
			&& (side_ball_Y >= myBoundary_Start_Y)) {
		//side_ball_X = myBoundary_Start_X;
		//side_ball_Y = myBoundary_Start_Y;
		return HIT_2_INNER_BOUNDARY_TOP_LEFT; // return 15
	}
	// right and top boundary
	else if ((side_ball_X <= myBoundary_End_X)
			&& (side_ball_Y >= myBoundary_Start_Y)) {
		//side_ball_X = myBoundary_End_X;
		//side_ball_Y = myBoundary_Start_Y;
		return HIT_2_INNER_BOUNDARY_TOP_RIGHT; // return 16
	}
	// left and bottom boundary
	else if ((side_ball_X >= myBoundary_Start_X)
			&& (side_ball_Y <= myBoundary_End_Y)) {
		//side_ball_X = myBoundary_Start_X;
		//side_ball_Y = myBoundary_End_Y;
		return HIT_2_INNER_BOUNDARY_BOTTOM_LEFT; // return 17
	}
	// right and bottom boundary
	else if ((side_ball_X <= myBoundary_End_X)
			&& (side_ball_Y <= myBoundary_End_Y)) {
		//side_ball_X = myBoundary_End_X;
		//side_ball_Y = myBoundary_End_Y;
		return HIT_2_INNER_BOUNDARY_BOTTOM_RIGHT; // return 18
	}
	else{
		return 0;
	}
}
