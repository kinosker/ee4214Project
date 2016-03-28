/*
 * ballControl.c
 *
 *  Created on: Mar 17, 2016
 *      Author: KaiHsiang
 */

#include "ballControl.h"
#include "myBoundaryChecker.h"
#include "math.h"

#define REGION_A	10
#define REGION_S	10
#define REGION_N	40
#define INITIAL_SPEED 250	// 250 pixel per sec (10 pixel per frame) FPS is 25... change this ....

// 10 pts -> Speed up by 25


int myBallControl_getNumberOfSteps(int ballSpeed_pixel);
void myBallControl_updateBallSpeed(int speedGain);
int myBallControl_getBallSpeedPixel(int ballSpeed);
int myBallControl_getNumberOfSteps(int ballSpeed_pixel);

ball_msg myBallControl_getBallLocation (ballSpeed_pixel, ball_msg currentLocation);
ball_msg myBallControl_getBallLocation_step(int numberOfSteps, int ballSpeed_pixel, ball_msg currentLocation, ball_msg endLocation);


void myBallControl_updateBallSpeed(int speedGain)
{
	if(ballSpeed > MINIMUM_SPEED && ballSpeed < MAXIMUM_SPEED)
	{
		ballSpeed += speedGain;
	}

	if(ballSpeed < MINIMUM_SPEED)
	{
		ballSpeed = MINIMUM_SPEED;
	}

	if(ballSpeed > MAXIMUM_SPEED)
	{
		ballSpeed = MAXIMUM_SPEED;
	}

}

// get ball speed based on speed in pixel and current ball location
ball_msg myBallControl_getBallLocation (ballSpeed_pixel, ball_msg currentLocation)
{
	ball_msg tempBall;

	tempBall.x += ballSpeed_pixel * sin(ball.dir);
	tempBall.y += ballSpeed_pixel * cos(ball.dir);

	// 2. boundary check...
	//if(tempBall.x > boundary....)

	return tempBall; 
}


// this function find the location of the ball per step...
// please update currentLocation every step..
ball_msg myBallControl_getBallLocation_step(int numberOfSteps, int ballSpeed_pixel, ball_msg currentLocation, ball_msg endLocation)
{
	int ballSpeed_step_pixel;
	ball_msg tempBall;


	ballSpeed_step_pixel = ballSpeed_pixel / numberOfSteps; // divide by FPS!!
	tempBall = myBallControl_getBallLocation(ballSpeed_step_pixel, currentLocation);

	// 3. if more than endLocation...
	if(tempBall.x > endLocation.x)
	{
		tempBall.x = endLocation.x;
	}

	if(tempBall.y > endLocation.y)
	{
		tempball.y = endLocation.y;
	}

	return tempBall;

}

// return the ball speed in pixel per frame
int myBallControl_getBallSpeedPixel(int ballSpeed)
{
	return 	ballSpeed_pixel = ballSpeed / FPS; // divide by FPS!!
}

// return the number of steps that the ball will move in this frame
int myBallControl_getNumberOfSteps(int ballSpeed_pixel)
{
	if(BRICK_SIZE_HEIGHT < BRICK_SIZE_LENGTH)
	{
		return (ceil(ballSpeed_pixel / (BRICK_SIZE_HEIGHT-1)));
	}
	else
	{
		return (ceil(ballSpeed_pixel / (BRICK_SIZE_LENGTH-1)));
	}
}


int myBallControl_SpeedChange(XTft *InstancePtr, int ball_X, int ball_Y,
		int score, int speed) {
	//int side_ball_X = ball_X + CIRCLE_RADIUS;
	int side_ball_Y = ball_Y + CIRCLE_RADIUS;
	int curr_Score = score;
	int prev_Score = 0;

	if (speed <= MINIMUM_SPEED) {
		speed = MINIMUM_SPEED;
	} else if (speed >= MAXIMUM_SPEED) {
		speed = MAXIMUM_SPEED;
	} else {
		//When ball hit S+/S- of the bar the ball speed will increase/decrease by 10pixel
		if (side_ball_Y >= BAR_START_X_S_MINUS + BAR_LENGTH_S) {
			speed -= BAR_AC_DECELERATION;
		} else if (side_ball_Y >= BAR_START_X_S_PLUS + BAR_LENGTH_S) {
			speed += BAR_AC_DECELERATION;
		}

		if ((curr_Score - prev_Score) >= 10) {
			speed += SCORE_ACCELERATION;
			prev_Score = curr_Score;
		}
	}
	return speed;
}

int myBallControl_AngleChange(XTft *InstancePtr, int ball_X, int ball_Y,
		int angle) {
	//int side_ball_X = ball_X + CIRCLE_RADIUS;
	int side_ball_Y = ball_Y + CIRCLE_RADIUS;
	//int prev_X = 0, prev_Y = 0;
	//int normal_Y = 0, normal_X = 0, diff = 0;

	if (angle <= MINIMUM_ANGLE_ON_BAR) {
		angle = MINIMUM_ANGLE_ON_BAR;
	} else if (angle >= MAXIMUM_ANGLE_ON_BAR) {
		angle = MAXIMUM_ANGLE_ON_BAR;
	} else {
		//ball hit the bar
		if (side_ball_Y <= BAR_START_X_A_MINUS) {
			side_ball_Y = BAR_START_X_A_MINUS;
			angle -= BAR_INCREASE_DECREASE;
		} else if (side_ball_Y <= BAR_START_X_A_PLUS) {
			side_ball_Y = BAR_START_X_A_PLUS;
			angle += BAR_INCREASE_DECREASE;
		}
	}
	return angle;
}

