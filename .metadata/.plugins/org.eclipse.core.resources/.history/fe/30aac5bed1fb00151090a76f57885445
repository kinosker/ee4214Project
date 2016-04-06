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

#define REGION_A	10
#define REGION_S	10
#define REGION_N	40

#define BALL_INITIAL_SPEED 250	// Initial speed : 250 pixel per sec
#define BALL_INITIAL_DIR 90		// Initial Direction : 90 Degree 



int myBallControl_updateBallSpeed(int ballSpeed, int speedGain)
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

// move the ball to a new location based on speed and currentLocation
ball_msg myBallControl_moveBall(float ballSpeed, ball_msg currentLocation)
{
	ball_msg tempBall = currentLocation;

	if(tempBall.dir > 180)
	{
		tempBall.dir = (tempBall.dir-180) * -1;
	}

	double radian = M_PI* tempBall.dir /180;

	//xil_printf("Currball.x = %d\r\nCurrball.y = %d\r\n", currentLocation.x, currentLocation.y);
	tempBall.x = tempBall.x + round(ballSpeed * cos(radian));
	tempBall.y = tempBall.y - round(ballSpeed * sin(radian));

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
	temp.dir = temp.dir * -1;
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

	x_gained = abs(tempBall.x);
	y_gained = abs(tempBall.y);

//    xil_printf("Get Step Location : %d , %d and speed %d\n", tempBall.x, tempBall.y, (int)ballSpeed_frame);

	// max steps = which 1 smaller.. + 2 circle radius to completely evade the brick.s

	if((BRICK_SIZE_HEIGHT < BRICK_SIZE_LENGTH || x_gained == 0) && y_gained != 0)
	{
		return (ceil(  (float)(y_gained) / (BRICK_SIZE_HEIGHT+CIRCLE_RADIUS+CIRCLE_RADIUS)));
	}
	else
	{
		return (ceil( (float)(x_gained) / (BRICK_SIZE_LENGTH+CIRCLE_RADIUS+CIRCLE_RADIUS)));
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

	x_gained = abs(tempBall.x);
	y_gained = abs(tempBall.y);


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


int myBallControl_SpeedChange(int ball_X, int ball_Y,
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
int myBallControl_ReboundAngle(int sideHit, ball_msg currentLocation)
{
	if(sideHit == HIT_INNER_BOX )
	{
		print("Hit inner box\n");
		return ((currentLocation.dir + 90) % 360);
	}
	else if (sideHit == HIT_INNER_CORNER)
	{
		print("Hit corner box\n");
		return ((currentLocation.dir + 180) % 360);
	}
	else // never hit
	{
		return currentLocation.dir;
	}
}

int myBallControl_AngleChange(int ball_X, int ball_Y,
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



