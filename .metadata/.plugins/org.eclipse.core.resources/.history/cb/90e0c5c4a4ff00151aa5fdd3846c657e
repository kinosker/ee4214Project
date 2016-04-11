
#include "myBallSpeed.h"

static int ballSpeed = BALL_INITIAL_SPEED;

int myBallControl_getBallSpeed()
{
	return ballSpeed;
}

void myBallControl_updateBallSpeed(int speedGain)
{
	xil_printf("Speed Gained is %d\n", speedGain);
	if(ballSpeed > BALL_MINIMUM_SPEED && ballSpeed < BALL_MAXIMUM_SPEED)
	{
		ballSpeed += speedGain;
	}

	if(ballSpeed < BALL_MINIMUM_SPEED)
	{
		ballSpeed = BALL_MINIMUM_SPEED;
	}

	if(ballSpeed > BALL_MAXIMUM_SPEED)
	{
		ballSpeed = BALL_MAXIMUM_SPEED;
	}

	xil_printf("New Speed is %d\n", ballSpeed);

}

void myBallControl_updateAutoSpeed(int score)
{
	static int prev_score = 0;

	if ((score != prev_score) && (score % 10 == 0))
	{
		myBallControl_updateBallSpeed(BALL_AUTO_SPEED_INCREMENT);
	}

	 prev_score = score; // update prev score
}
