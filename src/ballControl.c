/*
 * ballControl.c
 *
 *  Created on: Mar 17, 2016
 *      Author: KaiHsiang
 */

#include "ballControl.h"
#include "myBoundaryChecker.h"

int myBallControl_SpeedChange(XTft *InstancePtr, int ball_X, int ball_Y,int score, int speed) {
	//int side_ball_X = ball_X + CIRCLE_RADIUS;
	int side_ball_Y = ball_Y + CIRCLE_RADIUS;
	int curr_Score = score;
	int prev_Score = 0;

	if(speed <= MINIMUM_SPEED)
	{
		speed = MINIMUM_SPEED;
	}
	else if(speed >= MAXIMUM_SPEED)
	{
		speed = MAXIMUM_SPEED;
	}
	else
	{
		//When ball hit S+/S- of the bar the ball speed will increase/decrease by 10pixel
		if (side_ball_Y >= BAR_START_X_S_MINUS + BAR_LENGTH_S) {
			speed -= BAR_AC_DECELERATION;
		} else if (side_ball_Y >= BAR_START_X_S_PLUS + BAR_LENGTH_S) {
			speed += BAR_AC_DECELERATION;
		}

		if((curr_Score - prev_Score) >= 10)
		{
			speed += SCORE_ACCELERATION;
			prev_Score = curr_Score;
		}
	}
	return speed;
}

int myBallControl_AngleChange(XTft *InstancePtr, int ball_X, int ball_Y, int angle) {
	//int side_ball_X = ball_X + CIRCLE_RADIUS;
	int side_ball_Y = ball_Y + CIRCLE_RADIUS;

	if(angle <= MINIMUM_ANGLE_ON_BAR)
	{
		angle = MINIMUM_ANGLE_ON_BAR;
	}
	else if(angle >= MAXIMUM_ANGLE_ON_BAR)
	{
		angle = MAXIMUM_ANGLE_ON_BAR;
	}
	else
	{
		if(side_ball_Y <= BAR_START_X_A_MINUS)
		{
			side_ball_Y = BAR_START_X_A_MINUS;
			angle -= BAR_INCREASE_DECREASE;
		}
		else if(side_ball_Y <= BAR_START_X_A_PLUS)
		{
			side_ball_Y = BAR_START_X_A_PLUS;
			angle += BAR_INCREASE_DECREASE;
		}
	}
	return angle;
}
