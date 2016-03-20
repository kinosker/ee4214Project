/*
 * boundaryCheck.h
 *
 *  Created on: Mar 20, 2016
 *      Author: KaiHsiang
 */

#ifndef BOUNDARYCHECK_H_
#define BOUNDARYCHECK_H_

#include "TFT_Draw.h"

#define HIT_LEFTBOUNDARY  				1    // Hit Left side boundary
#define HIT_RIGHTBOUNDARY  				2    // Hit Right side boundary
#define HIT_TOPBOUNDARY 				3    // Hit TOP side boundary
#define HIT_BOTTOMBOUNDARY  			4    // Hit Bottom side boundary
#define HIT_2_BOUNDARY_TOP_LEFT 		5    // Hit 2 boundaries(top and left)
#define HIT_2_BOUNDARY_TOP_RIGHT 		6    // Hit 2 boundaries(top and right)
#define HIT_2_BOUNDARY_BOTTOM_LEFT 		7    // Hit 2 boundaries(bottom and left)
#define HIT_2_BOUNDARY_BOTTOM_RIGHT 	8    // Hit 2 boundaries(bottom and left)


int myBoundaryChecker_Check(int ball_X, int ball_Y, int myBoundary_Start_X,
		int myBoundary_Start_Y, int myBoundary_End_X, int myBoundary_End_Y);//speed?? and angle??


#endif /* BOUNDARYCHECK_H_ */
