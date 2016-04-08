/*
 * ballControl.c
 *
 *  Created on: Mar 17, 2016
 *      Author: KaiHsiang
 */

#include "ballControl.h"
#include "myBoundaryChecker.h"
#include "math.h"
#include "stdlib.h"
#include "xmk.h"
#include "myBallSpeed.h"

#define REGION_A	10
#define REGION_S	10
#define REGION_N	40

#define BALL_INITIAL_DIR 			90		// Initial Direction : 90 Degree





// move the ball to a new location based on speed and currentLocation
ball_msg myBallControl_moveBall(float ballSpeed, ball_msg currentLocation)
{
	ball_msg tempBall = currentLocation;
	int modifier;
	double radian;

	if(tempBall.dir > 180)
	{
		tempBall.dir = (tempBall.dir-180);
		modifier = -1;

	}
	else
	{
		modifier = 1;
	}

	radian = M_PI* tempBall.dir /180;

	//xil_printf("Currball.x = %d\r\nCurrball.y = %d\r\n", currentLocation.x, currentLocation.y);
	tempBall.x = tempBall.x + (ballSpeed *( modifier * cos(radian)));
	tempBall.y = tempBall.y - (ballSpeed * (modifier *  sin(radian)));

	//xil_printf("dir = %d\r\n", currentLocation.dir);
	//xil_printf("Tempball.x = %d\r\nTempball.y = %d\r\n", tempBall.x, tempBall.y);

	// 2. boundary check
	//... not needed "will bounce"
	tempBall.dir = currentLocation.dir;

	return tempBall; 
}

// this function find the location of the ball per frame...
// please update currentLocation every step..
ball_msg myBallControl_moveBall_frame(float ballSpeed_frame, ball_msg currentLocation)
{
	return myBallControl_moveBall(ballSpeed_frame, currentLocation);
}


// this function find the location of the ball per step...
// please update currentLocation every step..
ball_msg myBallControl_moveBall_step(float ballSpeed_step, ball_msg currentLocation)
{
	return myBallControl_moveBall(ballSpeed_step, currentLocation);
}


ball_msg myBallControl_moveBall_step_backward(float ballSpeed_step, ball_msg currentLocation)
{
	ball_msg temp = currentLocation;
	temp.dir = ((temp.dir +180) % 360);
	temp = myBallControl_moveBall(ballSpeed_step, temp);
	// reset back the direction...
	temp.dir = currentLocation.dir;
	return temp;
}




ball_msg myBallControl_moveBall_forward(float ballSpeed_forward, ball_msg currentLocation)
{

	return myBallControl_moveBall(ballSpeed_forward, currentLocation);
}

// return the ball speed in pixel per frame
float myBallControl_getFrameSpeed(int ballSpeed)
{
	return 	((float)ballSpeed) / FRAME_PER_SEC; // divide by FPS!!
}



// return the number of steps that the ball will move in this frame
int myBallControl_getSteps(float ballSpeed_frame, int dir)
{
	int x_gained, y_gained;
	ball_msg tempBall;

	tempBall.dir = dir;
	tempBall.x = 0; 
	tempBall.y = 0;

	tempBall = myBallControl_moveBall(ballSpeed_frame, tempBall);
	//xil_printf("tempX: %d, tempY: %d\n", (int)tempBall.x, (int)tempBall.y);
	x_gained = abs( ((int) (round(tempBall.x)) ) );
	y_gained = abs( ((int) (round(tempBall.y)) ) );
	//xil_printf("gainedX: %d, gainedY: %d\n", x_gained, y_gained);
	//    xil_printf("Get Step Location : %d , %d and speed %d\n", tempBall.x, tempBall.y, (int)ballSpeed_frame);

	// max steps = which 1 smaller.. + 2 circle radius to completely evade the brick.s

	if((BRICK_SIZE_HEIGHT < BRICK_SIZE_LENGTH || x_gained == 0) && y_gained != 0)
	{
		return (ceil(  ((float)(y_gained)) / (BRICK_SIZE_HEIGHT+CIRCLE_RADIUS+CIRCLE_RADIUS)));
	}
	else
	{
		return (ceil( ((float)(x_gained)) / (BRICK_SIZE_LENGTH+CIRCLE_RADIUS+CIRCLE_RADIUS)));
	}
}


// return the ball speed in pixel per step in a frame.
float myBallControl_getStepSpeed(float ballSpeed_frame, int steps)
{
	return  ((float)ballSpeed_frame) / steps; 

}



int myBallControl_getForwardSteps(float ballSpeed_step, int dir)
{
	int x_gained, y_gained;
	ball_msg tempBall;

	tempBall.dir = dir;
	tempBall.x = 0; 
	tempBall.y = 0;

	tempBall = myBallControl_moveBall(ballSpeed_step, tempBall);


	x_gained = abs( ((int) (round(tempBall.x)) ) );
	y_gained = abs( ((int) (round(tempBall.y)) ) );



	if(x_gained > y_gained)
	{
		return  x_gained;
	}
	else
	{
		return y_gained;
	}
}

// return the ball speed in pixel per forward steps in a frame
float myBallControl_getForwardStepsSpeed(float ballSpeed_step, int forward_steps)
{
	return  ballSpeed_step / forward_steps; 

}


// int myBallControl_SpeedChange(int ball_X, int ball_Y,
// 		int score, int speed) {
// 	//int side_ball_X = ball_X + CIRCLE_RADIUS;
// 	int side_ball_Y = ball_Y + CIRCLE_RADIUS;
// 	int curr_Score = score;
// 	int prev_Score = 0;

// 	if (speed <= MINIMUM_SPEED) {
// 		speed = MINIMUM_SPEED;
// 	} else if (speed >= MAXIMUM_SPEED) {
// 		speed = MAXIMUM_SPEED;
// 	} else {
// 		//When ball hit S+/S- of the bar the ball speed will increase/decrease by 10pixel
// 		if (side_ball_Y >= BAR_START_X_S_MINUS + BAR_LENGTH_S) {
// 			speed -= BAR_AC_DECELERATION;
// 		} else if (side_ball_Y >= BAR_START_X_S_PLUS + BAR_LENGTH_S) {
// 			speed += BAR_AC_DECELERATION;
// 		}

// 		if ((curr_Score - prev_Score) >= 10) {
// 			speed += SCORE_ACCELERATION;
// 			prev_Score = curr_Score;
// 		}
// 	}
// 	return speed;
// }


int myBallControl_ReboundAngle(int sideHit, ball_msg currentLocation)
{
	int tempAngle;

	if(sideHit == HIT_REFLECT_SIDE || sideHit == HIT_REFLECT_TOP || sideHit == HIT_REFLECT_BTM || sideHit == HIT_OUTER_BOX_BTM) //remove sideHit == HIT_OUTER_BOX_BOX after testing
	{
		//print("Hit inner box\n");
		//xil_printf("Inside rebound angle is %d\n", currentLocation.dir);
		if(currentLocation.dir % 90 == 0)
		{
			// if flying vertical or horizontally perfectly... should rebounce 180 deg instead of 90 deg
			//xil_printf("reflect 90 but 180 is %d\n\n\n", currentLocation.dir);
			return ((currentLocation.dir + 180) % 360);

		}
		else if(sideHit == HIT_REFLECT_SIDE)
		{
			//xil_printf("Angle reflect side hit is %d\n\n", sideHit);

			return ((180 - currentLocation.dir) % 360); //editted

			//return ((360 - currentLocation.dir) % 360); //initial
		}
		else
		{
			//xil_printf("reflect 90 is %d\n\n", currentLocation.dir);
			//return ((180 - currentLocation.dir) % 360); //inital
			return ((360 - currentLocation.dir) % 360); //editted
		}
	}
	else if (sideHit == HIT_REFLECT_180_1 || sideHit == HIT_REFLECT_180_2 || sideHit == HIT_REFLECT_180_3)
	{
		//print("Hit corner box\n");
		return ((currentLocation.dir + 180) % 360);
	}
	else if(sideHit == HIT_ANGLE_DEC)
	{
		xil_printf("Angle reflect DECREASE CONSTANT is %d\n\n", sideHit);
		tempAngle = (currentLocation.dir + 180) % 360 ; // reflect 1st
		tempAngle -= BAR_ANGLE_ADJUSTMENT;				// decrease angle..

		// low angle threshold check.
		if(tempAngle <= MINIMUM_ANGLE_ON_BAR)
		{
			return MINIMUM_ANGLE_ON_BAR;
		}
		else
		{
			return tempAngle;
		}
	}
	else if (sideHit == HIT_ANGLE_ACC)
	{
		xil_printf("Angle reflect increase CONSTANT is %d\n\n", sideHit);
		tempAngle = (currentLocation.dir + 180) % 360 ; // reflect 1st
		tempAngle += BAR_ANGLE_ADJUSTMENT;				// decrease angle..

		// low angle threshold check.
		if(tempAngle >= MAXIMUM_ANGLE_ON_BAR)
		{
			return MAXIMUM_ANGLE_ON_BAR;
		}
		else
		{
			return tempAngle;
		}
	}
	else // never hit
	{
		return currentLocation.dir;
	}
}



void myBallControl_SetReboundSpeed(int sideHit)
{
	if(sideHit == HIT_SPEED_DEC)
	{
		xil_printf("Speed decrease CONSTANT is %d\n\n", sideHit);
		myBallControl_updateBallSpeed(BAR_SPEED_ADJUSTMENT_DOWN);
	}
	else if (sideHit == HIT_SPEED_ACC)
	{
		xil_printf("Speed increase CONSTANT is %d\n\n", sideHit);
		myBallControl_updateBallSpeed(BAR_SPEED_ADJUSTMENT_UP);
	}

}


// int myBallControl_AngleChange(int ball_X, int ball_Y,
// 		int hit_Angle_Bar, int angle) {
// 	//int side_ball_X = ball_X + CIRCLE_RADIUS;
// 	//int side_ball_Y = ball_Y + CIRCLE_RADIUS;
// 	//int prev_X = 0, prev_Y = 0;
// 	//int normal_Y = 0, normal_X = 0, diff = 0;

// //	if (angle <= MINIMUM_ANGLE_ON_BAR) {
// //		angle = MINIMUM_ANGLE_ON_BAR;
// //	} else if (angle >= MAXIMUM_ANGLE_ON_BAR) {
// //		angle = MAXIMUM_ANGLE_ON_BAR;
// //	} else {
// 		//ball hit the bar
// 		if (hit_Angle_Bar == HIT_ANGLE_DEC) {
// 			//side_ball_Y = BAR_START_X_A_MINUS;
// 			angle -= BAR_INCREASE_DECREASE;
// 		} else if (hit_Angle_Bar == HIT_ANGLE_ACC) {
// 			//side_ball_Y = BAR_START_X_A_PLUS;
// 			angle += BAR_INCREASE_DECREASE;
// 		}
// //	}
// 	return angle;
// }



