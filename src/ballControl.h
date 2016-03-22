/*
 * ballControl.h
 *
 *  Created on: Mar 22, 2016
 *      Author: KaiHsiang
 */

#ifndef BALLCONTROL_H_
#define BALLCONTROL_H_

#include "myBoundaryChecker.h"
#include "TFT_Draw.h"

#define INITIAL_SPEED 			10	//250pixels per sec -> 25fps = 10pixels
#define BAR_AC_DECELERATION 	4	//100pixels per sec -> 25fps = 4pixels (+4 when hit S+ part of bar, -4 when hit S- part of bar)
#define SCORE_ACCELERATION		1	//25pixels per sec -> 25fps = 1pixels (+1 when the score is increase by 10)


void myBallControl_SpeedChange(XTft *InstancePtr, int ball_X, int ball_Y,int score, int speed);


#endif /* BALLCONTROL_H_ */
