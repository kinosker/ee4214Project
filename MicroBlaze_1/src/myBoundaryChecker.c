/*
 * boundaryCheck.c
 *
 *  Created on: Mar 20, 2016
 *      Author: KaiHsiang
 */

#include "myBoundaryChecker.h"
#include "myCommon.h"

int outerLeftBoundary(int side_ball_X) {
	return side_ball_X <= OUTER_COL_START_X + 2;
}

int outerRightBoundary(int side_ball_X) {
	return side_ball_X >= OUTER_COL_END_X - 2;
}

int outerTopBoundary(int side_ball_Y) {
	return side_ball_Y <= OUTER_COL_START_Y + 2;
}

int outerBottomBoundary(int side_ball_Y) {
	return side_ball_Y >= OUTER_COL_END_Y - 2;
}

int outerTopLeftCorner(int side_ball_X, int side_ball_Y) {
	return (side_ball_X <= OUTER_COL_START_X + 1)
			&& (side_ball_Y <= OUTER_COL_START_Y + 1);
}

int outerTopRightCorner(int side_ball_X, int side_ball_Y) {
	return (side_ball_X >= OUTER_COL_END_X - 1)
			&& (side_ball_Y <= OUTER_COL_START_Y + 1);
}

int outerBtmLeftCorner(int side_ball_X, int side_ball_Y) {
	return (side_ball_X <= OUTER_COL_START_X + 1)
			&& (side_ball_Y >= OUTER_COL_END_Y - 1);
}

int outerBtmRightCorner(int side_ball_X, int side_ball_Y) {
	return (side_ball_X >= OUTER_COL_END_X - 1)
			&& (side_ball_Y >= OUTER_COL_END_Y - 1);
}

int myBoundaryChecker_CheckOuter(int ball_X, int ball_Y) //speed????? angle???
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

	for(i = 0; i < 4; i++)
	{
		side_ball_X = quad_x[i];
		side_ball_Y = quad_y[i];
		if (outerLeftBoundary(side_ball_X)) { // left boundary
			//side_ball_X = myBoundary_Start_X;
			return HIT_OUTER_BOX_SIDE; // return 10
		}
		else if (outerRightBoundary(side_ball_X)) {	//right boundary
			//side_ball_X = myBoundary_End_X;
			return HIT_OUTER_BOX_SIDE;		// return 10
		}
		else if (outerTopBoundary(side_ball_Y)) { // top boundary
			//side_ball_Y = myBoundary_Start_Y;
			return HIT_OUTER_BOX_TOP; // return 10
		}
		else if (outerBottomBoundary(side_ball_Y)) { // bottom boundary
			//side_ball_Y = myBoundary_End_Y;
			return HIT_OUTER_BOX_BTM;		// return 10
		}

		/*******************************************four corners checking****************************************/
		// left and top boundary
		else if (outerTopLeftCorner(side_ball_X, side_ball_Y)) {
			//side_ball_X = myBoundary_Start_X;
			//side_ball_Y = myBoundary_Start_Y;
			return HIT_OUTER_CORNER; // return 11
		}
		// right and top boundary
		else if (outerTopRightCorner(side_ball_X, side_ball_Y)) {
			//side_ball_X = myBoundary_End_X;
			//side_ball_Y = myBoundary_Start_Y;
			return HIT_OUTER_CORNER; // return 11
		}
		// left and bottom boundary
		else if (outerBtmLeftCorner(side_ball_X, side_ball_Y)) {
			//side_ball_X = myBoundary_Start_X;
			//side_ball_Y = myBoundary_End_Y;
			return HIT_OUTER_CORNER; // return 7
		}
		// right and bottom boundary
		else if (outerBtmRightCorner(side_ball_X, side_ball_Y)) {
			//side_ball_X = myBoundary_End_X;
			//side_ball_Y = myBoundary_End_Y;
			return HIT_OUTER_CORNER; // return 8
		}
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

int innerBarCheck(int side_ball_X, int myBoundary_Start_X,
		int myBoundary_End_X, int side_ball_Y, int myBoundary_Start_Y,
		int myBoundary_End_Y) {
	return (side_ball_X >= (myBoundary_Start_X - 1))
			&& (side_ball_X <= (myBoundary_End_X + 1))
			&& (side_ball_Y >= (myBoundary_Start_Y - 1));
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

int innerLeftBoundary(int side_ball_X, int myBoundary_Start_X) {
	return side_ball_X <= myBoundary_Start_X;
}

int innerRightBoundary(int side_ball_X, int myBoundary_End_X) {
	return side_ball_X >= myBoundary_End_X;
}

int innerTopBoundary(int side_ball_Y, int myBoundary_Start_Y) {
	return side_ball_Y <= myBoundary_Start_Y;
}

int innerBottomBoundary(int side_ball_Y, int myBoundary_End_Y) {
	return side_ball_Y >= myBoundary_End_Y;
}

int myBoundaryChecker_getClosestX(int ball_X, int myBoundary_Start_X, int myBoundary_End_X)
{
	if (ball_X  < myBoundary_Start_X)
	{
	    return  myBoundary_Start_X;
	}
	else if (ball_X  > myBoundary_End_X)
	{
		return myBoundary_End_X;
	}
	else
	{
		return ball_X;
	}
}


int myBoundaryChecker_getClosestY(int ball_Y, int myBoundary_Start_Y, int myBoundary_End_Y)
{
	if (ball_Y  < myBoundary_Start_Y)
	{
	    return  myBoundary_Start_Y;
	}
	else if (ball_Y  > myBoundary_End_Y)
	{
		return myBoundary_End_Y;
	}
	else
	{
		return ball_Y;
	}
}

int myBoundaryChecker_getDistanceBtwThem(int dist_X, int dist_Y)
{

	// use pythagoras to find distance.

	float distanceBtwThem = sqrt (  ( ((float)dist_X * dist_X)  + (dist_Y * dist_Y) ) );

	
	return (int)distanceBtwThem; // rnd down distance.

}


// return the side that it HIT!, if 
int myBoundaryChecker_checkHitBrick(int ball_X, int ball_Y, int myBoundary_Start_X, int myBoundary_Start_Y, int myBoundary_End_X, int myBoundary_End_Y)
{

	int closest_X, closest_Y;
	int dist_X, dist_Y, distanceBtwThem; 


	// get closest point btw them. 
	closest_X = myBoundaryChecker_getClosestX(ball_X, myBoundary_Start_X, myBoundary_End_X);
	closest_Y = myBoundaryChecker_getClosestY(ball_Y, myBoundary_Start_Y, myBoundary_End_Y);

	dist_X =  abs(ball_X - closest_X);
	dist_Y =  abs(ball_Y - closest_Y);


	// get dist btw brick and ball
	distanceBtwThem = myBoundaryChecker_getDistanceBtwThem(dist_X, dist_Y);

	if (distanceBtwThem < CIRCLE_RADIUS)
	{
		// collided into brick...

		if(CIRCLE_RADIUS - distanceBtwThem <= CORNER_TOLERANCE)
		{
			// distance between brick and ball is very near... likely to be corner
			// NOTE : Why cannot be ball inside brick and near..?
			// NOTE : How do u confirm!?!? => Small steps algorithm... 

			return HIT_INNER_CORNER; // return 11
		}
		else
		{
			// determine : hit side or top/bottom

			if(dist_X < dist_Y)
			{
				// distance for x is closer...
				return HIT_INNER_BOX_SIDE;
			}
			else
			{
				// distance for y is closer... either btm or top .. no difference
				return HIT_INNER_BOX_BTM;
			}
		}
	}
	else
	{
		return 0;
	}

}


// return 1 if x axis is within the brick side boundary
// Return 0 if not...
int myBoundaryChecker_checkBrick_horizontal(int ball_X, int myBoundary_Start_X, int myBoundary_End_X)
{
	int side_ball_X_Right = ball_X + CIRCLE_RADIUS + 1;
	int side_ball_X_Left = ball_X + CIRCLE_RADIUS - 1;


	if((side_ball_X_Right >= myBoundary_Start_X) &&  (side_ball_X_Right <= myBoundary_End_X))
	{
		// right of ball x inside boundary
		return 1;
	}

	else if((side_ball_X_Left >= myBoundary_Start_X) &&  (side_ball_X_Left <= myBoundary_End_X))
	{
		// left of ball x inside boundary
		return 1;
	}

	else
	{

		return 0;
	}

}


int myBoundaryChecker_checkBrick_vertical(int ball_Y, int myBoundary_Start_Y, int myBoundary_End_Y)
{
	int side_ball_Y_Top = ball_Y + CIRCLE_RADIUS + 1;
	int side_ball_Y_Bottom = ball_Y + CIRCLE_RADIUS - 1;


	if((side_ball_Y_Top >= myBoundary_Start_Y) &&  (side_ball_Y_Top <= myBoundary_End_Y))
	{
		// top of ball y inside boundary
		return 1;
	}

	else if((side_ball_Y_Bottom >= myBoundary_Start_Y) &&  (side_ball_Y_Bottom <= myBoundary_End_Y))
	{
		// btm of ball y inside boundary
		return 1;
	}

	else
	{

		return 0;
	}

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
			if( innerLeftBoundary(side_ball_X, myBoundary_Start_X)) {
				return HIT_INNER_BOX_SIDE;
			}

			if( innerRightBoundary(side_ball_X, myBoundary_End_X)) {
				return HIT_INNER_BOX_SIDE;
			}

			if(innerTopBoundary(side_ball_Y, myBoundary_Start_Y)) {
				return HIT_INNER_BOX_TOP;
			}

			if(innerBottomBoundary(side_ball_Y, myBoundary_End_Y)) {
				return HIT_INNER_BOX_BTM;
			}

		}
	}
	return 0;
}



// return 1 if x axis is within the brick side boundary
// Return 0 if not...
int myBoundaryChecker_checkHitBar_horizontal(int ball_X, int myBoundary_Start_X, int myBoundary_End_X)
{
	int side_ball_X_Right = ball_X + CIRCLE_RADIUS + 1;
	int side_ball_X_Left = ball_X + CIRCLE_RADIUS - 1;


	if((side_ball_X_Right >= myBoundary_Start_X) &&  (side_ball_X_Right <= myBoundary_End_X))
	{
		// right of ball x inside boundary
		return 1;
	}

	else if((side_ball_X_Left >= myBoundary_Start_X) &&  (side_ball_X_Left <= myBoundary_End_X))
	{
		// left of ball x inside boundary
		return 1;
	}

	else
	{

		return 0;
	}

}



// NO END Y cause... impossible to be below.. => below = lose game..
int myBoundaryChecker_checkBar_vertical(int ball_Y, int myBoundary_Start_Y)
{
	// check btm is enough..

	int side_ball_Y_Bottom = ball_Y + CIRCLE_RADIUS - 1;


	 if((side_ball_Y_Bottom >= myBoundary_Start_Y))
	{
		// btm of ball y inside boundary
		return 1;
	}

	else
	{

		return 0;
	}

}




int myBoundaryChecker_checkHitBar(int ball_X, int ball_Y, int myBoundary_Start_X,
		int myBoundary_Start_Y, int myBoundary_End_X, int myBoundary_End_Y)
{

	int closest_X, closest_Y;
	int dist_X, dist_Y, distanceBtwThem; 

	if(myBoundaryChecker_checkHitBar_horizontal( ball_X, myBoundary_Start_X, myBoundary_End_X))
	{
		// if ball at the x boundary of bar.. continue to confirm...

		if(myBoundaryChecker_checkBar_vertical (ball_Y, myBoundary_Start_Y))
		{
			// ball is both at x and y boundary... using square box check..
			// use distance to check if it's really hitting bar..

			closest_X = myBoundaryChecker_getClosestX( ball_X,  myBoundary_Start_X,  myBoundary_End_X);
			closest_Y = myBoundary_Start_Y; // using start Y only...


			dist_X =  abs(ball_X - closest_X);
			dist_Y =  abs(ball_Y - closest_Y);

			// get dist btw brick and ball
			distanceBtwThem = myBoundaryChecker_getDistanceBtwThem(dist_X, dist_Y);

			if (distanceBtwThem < CIRCLE_RADIUS)
			{
				// collided into bar...

				if(ball_X <= (myBoundary_Start_X + REGION_A_NEG))
				{
					// A- REGION : from LHS to end of A- region
					return HIT_ANGLE_DEC; // return 14

				}
				else if(ball_X <= (myBoundary_Start_X + REGION_S_NEG))
				{
					// S- REGION : from end of A- to end of S- region
					return HIT_SPEED_DEC; // return 14

				}
				else if(ball_X <= (myBoundary_Start_X + REGION_N))
				{
					// N REGION : from end of S- to end of N region

					return HIT_BAR_N; // return 11


				}
				else if(ball_X <= (myBoundary_Start_X + REGION_S_POS))
				{
					// S+ REGION: from end of N to end of S+ region
					return HIT_SPEED_ACC; // return 13

				}
				else
				{
					// N+ REGION : from end of S+ region to RHS
					return HIT_SPEED_ACC; // return 13

				}
				
			}

		}

	}
	
	return 0; // fail to hit any..
	

}

int myBoundaryChecker_CheckBar(int ball_X, int ball_Y, int myBoundary_Start_X,
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



		
		 // Region N
		 if (innerBarCheck(side_ball_X, (myBoundary_Start_X + 20), (myBoundary_End_X - 20),
				side_ball_Y, myBoundary_Start_Y, myBoundary_End_Y)) { 
			return HIT_BAR_N; // return 11
		}
		// Region S - 
		else if (innerBarCheck(side_ball_X, (myBoundary_Start_X + 10), (myBoundary_Start_X + 20),
				side_ball_Y, myBoundary_Start_Y, myBoundary_End_Y)) { 
			xil_printf("S- : x : %d, y : %d\n\n\n\n", ball_X, side_ball_Y_Bottom);
			return HIT_SPEED_DEC; // return 12
		}
		// Region S+
		else if (innerBarCheck(side_ball_X, (myBoundary_End_X - 20), (myBoundary_End_X - 10),
				side_ball_Y, myBoundary_Start_Y, myBoundary_End_Y)) { 
			xil_printf("S+ : x : %d, y : %d\n\n\n\n", ball_X, side_ball_Y_Bottom);
			return HIT_SPEED_ACC; // return 13
		}
		// Region  A-
		else if (innerBarCheck(side_ball_X, myBoundary_Start_X, (myBoundary_Start_X + 10),
				side_ball_Y, myBoundary_Start_Y, myBoundary_End_Y)) {
			xil_printf("A-  : x : %d, y : %d\n\n\n\n", ball_X, side_ball_Y_Bottom);
			return HIT_ANGLE_DEC; // return 14
		}
		// Region A+
		else if (innerBarCheck(side_ball_X, (myBoundary_End_X - 10), myBoundary_End_X,
				side_ball_Y, myBoundary_Start_Y, myBoundary_End_Y)) {
			xil_printf("A+ : x : %d, y : %d\n\n\n\n", ball_X, side_ball_Y_Bottom);
			return HIT_ANGLE_ACC; // return 15
		}
	}
	return 0;
}
