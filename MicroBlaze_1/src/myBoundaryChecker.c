/*
 * boundaryCheck.c
 *
 *  Created on: Mar 20, 2016
 *      Author: KaiHsiang
 */

#include "myBoundaryChecker.h"
#include "myCommon.h"

int myBoundaryChecker_CheckOuter(int ball_X, int ball_Y) //speed????? angle???
{
	int side_ball_X = ball_X + CIRCLE_RADIUS;
	int side_ball_Y = ball_Y + CIRCLE_RADIUS;

	if (side_ball_X <= OUTER_COL_START_X) { // left boundary
		//side_ball_X = myBoundary_Start_X;
		return HIT_LEFTBOUNDARY; // return 1
	}
	if (side_ball_X >= OUTER_COL_END_X) {	//right boundary
		//side_ball_X = myBoundary_End_X;
		return HIT_RIGHTBOUNDARY;		// return 2
	}
	if (side_ball_Y <= OUTER_COL_START_Y) { // top boundary
		//side_ball_Y = myBoundary_Start_Y;
		return HIT_TOPBOUNDARY; // return 3
	}
	if (side_ball_Y >= OUTER_COL_END_Y) { // bottom boundary
		//side_ball_Y = myBoundary_End_Y;
		return HIT_BOTTOMBOUNDARY;		// return 4
	}

	/*******************************************four corners checking****************************************/
	// left and top boundary
	if ((side_ball_X <= OUTER_COL_START_X)
			&& (side_ball_Y <= OUTER_COL_START_Y)) {
		//side_ball_X = myBoundary_Start_X;
		//side_ball_Y = myBoundary_Start_Y;
		return HIT_2_BOUNDARY_TOP_LEFT; // return 5
	}
	// right and top boundary
	if ((side_ball_X >= OUTER_COL_END_X)
			&& (side_ball_Y <= OUTER_COL_START_Y)) {
		//side_ball_X = myBoundary_End_X;
		//side_ball_Y = myBoundary_Start_Y;
		return HIT_2_BOUNDARY_TOP_RIGHT; // return 6
	}
	// left and bottom boundary
	if ((side_ball_X <= OUTER_COL_START_X)
			&& (side_ball_Y >= OUTER_COL_END_Y)) {
		//side_ball_X = myBoundary_Start_X;
		//side_ball_Y = myBoundary_End_Y;
		return HIT_2_BOUNDARY_BOTTOM_LEFT; // return 7
	}
	// right and bottom boundary
	if ((side_ball_X >= OUTER_COL_END_X)
			&& (side_ball_Y >= OUTER_COL_END_Y)) {
		//side_ball_X = myBoundary_End_X;
		//side_ball_Y = myBoundary_End_Y;
		return HIT_2_BOUNDARY_BOTTOM_RIGHT; // return 8
	}
	return 0;
}

int leftTopBoundaryCheck(int side_ball_X, int myBoundary_Start_X,
		int side_ball_Y, int myBoundary_Start_Y) {
	return (side_ball_X >= myBoundary_Start_X)
			&& (side_ball_Y >= myBoundary_Start_Y)
			&& (side_ball_X <= myBoundary_Start_X + CIRCLE_RADIUS)
			&& (side_ball_Y <= myBoundary_Start_Y + CIRCLE_RADIUS);
}

int innerBoundaryCheck(int side_ball_X, int myBoundary_Start_X,
		int myBoundary_End_X, int side_ball_Y, int myBoundary_Start_Y,
		int myBoundary_End_Y) {
	return (side_ball_X >= myBoundary_Start_X)
			&& (side_ball_X <= myBoundary_End_X)
			&& (side_ball_Y >= myBoundary_Start_Y)
			&& (side_ball_Y <= myBoundary_End_Y);
}

int rightTopBoundaryCheck(int side_ball_X, int myBoundary_End_X,
		int side_ball_Y, int myBoundary_Start_Y) {
	return (side_ball_X <= myBoundary_End_X)
			&& (side_ball_Y >= myBoundary_Start_Y)
			&& (side_ball_X >= (myBoundary_End_X - CIRCLE_RADIUS))
			&& (side_ball_Y <= (myBoundary_Start_Y + CIRCLE_RADIUS));
}

int leftBottomBoundaryCheck(int side_ball_X, int myBoundary_Start_X,
		int side_ball_Y, int myBoundary_End_Y) {
	return (side_ball_X <= myBoundary_Start_X)
			&& (side_ball_Y <= myBoundary_End_Y)
			&& (side_ball_X >= myBoundary_Start_X + CIRCLE_RADIUS)
			&& (side_ball_Y >= myBoundary_End_Y - CIRCLE_RADIUS);
}

int rightBottomBoundaryCheck(int side_ball_X, int myBoundary_End_X,
		int side_ball_Y, int myBoundary_End_Y) {
	return (side_ball_X <= myBoundary_End_X)
			&& (side_ball_Y <= myBoundary_End_Y)
			&& (side_ball_X >= myBoundary_End_X - CIRCLE_RADIUS)
			&& (side_ball_Y >= myBoundary_End_Y - CIRCLE_RADIUS);
}

int myBoundaryChecker_CheckInner(int ball_X, int ball_Y, int myBoundary_Start_X,
		int myBoundary_Start_Y, int myBoundary_End_X, int myBoundary_End_Y) //speed????? angle???
{
	int side_ball_X_Right = ball_X + CIRCLE_RADIUS;
	int side_ball_Y_Bottom = ball_Y + CIRCLE_RADIUS;
	int side_ball_X_Left = ball_X - CIRCLE_RADIUS;
	int side_ball_Y_Top = ball_Y - CIRCLE_RADIUS;
	
	int side_ball_X = 0;
	int side_ball_Y = 0;

	int quad_x[] = {side_ball_X_Left, side_ball_X_Left, side_ball_X_Right, side_ball_X_Right};
	int quad_y[] = {side_ball_Y_Top, side_ball_Y_Bottom, side_ball_Y_Top, side_ball_Y_Bottom};
	int i =0;
//	xil_printf("bound_x_start : %d, bound_ystart : %d\n bound_x_end : %d, bound_yend : %d\n", myBoundary_Start_X, myBoundary_Start_Y, myBoundary_End_X, myBoundary_End_Y);

	for(i = 0; i < 4; i++)
	{
		side_ball_X = quad_x[i];
		side_ball_Y = quad_y[i];



	//	}

		/*******************************************four corners checking****************************************/
		// left and top boundary
		if (leftTopBoundaryCheck(side_ball_X, myBoundary_Start_X, side_ball_Y,
				myBoundary_Start_Y)) {

			//side_ball_X = myBoundary_Start_X;
			//side_ball_Y = myBoundary_Start_Y;
			return HIT_INNER_CORNER; // return 11
		}

		// right and top boundary
		else if (rightTopBoundaryCheck(side_ball_X, myBoundary_End_X, side_ball_Y,
				myBoundary_Start_Y)) {
			//side_ball_X = myBoundary_End_X;
			//side_ball_Y = myBoundary_Start_Y;

			//xil_printf("sideball : %d,%d , bound_x_start : %d, bound_ystart : %d\n bound_x_end : %d, bound_yend : %d\n", side_ball_X, side_ball_Y, myBoundary_Start_X, myBoundary_Start_Y, myBoundary_End_X, myBoundary_End_Y);

			return HIT_INNER_CORNER; // return 11
		}
		// left and bottom boundary
		else if (leftBottomBoundaryCheck(side_ball_X, myBoundary_Start_X,
				side_ball_Y, myBoundary_End_Y)) {
			//side_ball_X = myBoundary_Start_X;
			//side_ball_Y = myBoundary_End_Y;
			return HIT_INNER_CORNER; // return 11
		}
		// right and bottom boundary
		else if (rightBottomBoundaryCheck(side_ball_X, myBoundary_End_X,
				side_ball_Y, myBoundary_End_Y)) {
			//side_ball_X = myBoundary_End_X;
			//side_ball_Y = myBoundary_End_Y;
			return HIT_INNER_CORNER; // return 11
		}
		else if (innerBoundaryCheck(side_ball_X, myBoundary_Start_X, myBoundary_End_X,
						side_ball_Y, myBoundary_Start_Y, myBoundary_End_Y)) { // left boundary
					//side_ball_X = myBoundary_Start_X;
					return HIT_INNER_BOX; // return 10
				}
	}
	return 0;
}
