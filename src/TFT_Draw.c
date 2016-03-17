#include "TFT_Draw.h"

int barLeftPos = BAR_START_X, barRightPos = BAR_START_X + BAR_LENGTH;

int tft_init(u32 TftDeviceId, XTft *InstancePtr) {
	int Status;
	XTft_Config *TftConfigPtr;

	/*
	 * Get address of the XTft_Config structure for the given device id.
	 */
	TftConfigPtr = XTft_LookupConfig(TftDeviceId);
	if (TftConfigPtr == (XTft_Config *) NULL ) {
		return XST_FAILURE;
	}

	/*
	 * Initialize all the TftInstance members and fills the screen with
	 * default background color.
	 */
	Status = XTft_CfgInitialize(InstancePtr, TftConfigPtr,
			TftConfigPtr->BaseAddress);

	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Wait till Vsync(Video address latch) status bit is set before writing
	 * the frame address into the Address Register. This ensures that the
	 * current frame has been displayed and we can display a new frame of
	 * data. Checking the Vsync state ensures that there is no data flicker
	 * when displaying frames in real time though there is some delay due to
	 * polling.
	 */
	while (XTft_GetVsyncStatus(InstancePtr) != XTFT_IESR_VADDRLATCH_STATUS_MASK)
		;

	/*
	 * Change the Video Memory Base Address from default value to
	 * a valid Memory Address and clear the screen.
	 */
	XTft_SetFrameBaseAddr(InstancePtr, TFT_FRAME_ADDR);
	XTft_ClearScreen(InstancePtr);

	xil_printf("Finish initializing TFT\n\r");

	XTft_SetColor(InstancePtr, COLOR_WHITE, COLOR_WHITE);
	XTft_ClearScreen(InstancePtr);

	xil_printf("TFT test completed!\r\n");
	return XST_SUCCESS;
}

static int tft_setPixelSafe(XTft *InstancePtr, u32 colVal, u32 rowVal,
		u32 colour, pthread_mutex_t mutex_sw_tft);

int tft_intialDraw(XTft *InstancePtr) {
	int i, j, stor_X = COL_1_X;
	// Outer green box

	tft_fillRect(InstancePtr, OUTER_COL_START_X, OUTER_COL_START_Y,
			OUTER_COL_END_X, OUTER_COL_END_Y, COLOR_GREEN);
	tft_drawRect(InstancePtr, OUTER_COL_START_X, OUTER_COL_START_Y,
			OUTER_COL_END_X, OUTER_COL_END_Y, COLOR_BLACK);

	// Inner 80 Small boxes

//	for (i = 0; i < 10; i++) {
//		for (j = 0; j < 8; j++) {
//			tft_drawLine(InstancePtr, stor_X, ROW_1_Y + (20 * j), stor_X + 40,
//					ROW_1_Y + (20 * j), COLOR_BLACK);
//			tft_drawLine(InstancePtr, stor_X, ROW_1_Y + (20 * j), stor_X,
//					ROW_1_Y + (20 * j) + (15), COLOR_BLACK);
//			tft_drawLine(InstancePtr, stor_X, ROW_1_Y + (20 * j) + (15),
//					stor_X + 40, ROW_1_Y + (20 * j) + (15), COLOR_BLACK);
//			tft_drawLine(InstancePtr, stor_X + 40, ROW_1_Y + (20 * j),
//					stor_X + 40, ROW_1_Y + (20 * j) + (15), COLOR_BLACK);
//		}
//		stor_X = stor_X + 45;
//	}

	// Bar Box
	tft_drawRect(InstancePtr, BAR_START_X, BAR_START_Y, BAR_END_X, BAR_END_Y,
			COLOR_BLACK);

	// Score (WORD) Box
	tft_drawRect(InstancePtr, SCORE_WORD_BOX_START_X, SCORE_WORD_BOX_START_Y,
			SCORE_WORD_BOX_END_X, SCORE_WORD_BOX_END_Y, COLOR_BLACK);
	tft_fillRect(InstancePtr, SCORE_WORD_BOX_START_X, SCORE_WORD_BOX_START_Y,
			SCORE_WORD_BOX_END_X, SCORE_WORD_BOX_END_Y, COLOR_GREY);
	tft_writeString(InstancePtr, SCORE_WORD_BOX_START_X + 2,
			SCORE_WORD_BOX_START_Y + 7, "Scores", COLOR_BLACK, COLOR_GREY);

	// Score Outer Box
	tft_drawRect(InstancePtr, SCORE_OUTER_BOX_START_X, SCORE_OUTER_BOX_START_Y,
			SCORE_OUTER_BOX_END_X, SCORE_OUTER_BOX_END_Y, COLOR_BLACK);
	tft_fillRect(InstancePtr, SCORE_OUTER_BOX_START_X, SCORE_OUTER_BOX_START_Y,
			SCORE_OUTER_BOX_END_X, SCORE_OUTER_BOX_END_Y, COLOR_GREY);

	// 3 Score Inner Box
	tft_drawRect(InstancePtr, SCORE_BOX1_START_X, SCORE_BOX_START_Y,
			SCORE_BOX1_END_X, SCORE_BOX_END_Y, COLOR_BLACK);
	tft_drawRect(InstancePtr, SCORE_BOX2_START_X, SCORE_BOX_START_Y,
			SCORE_BOX2_END_X, SCORE_BOX_END_Y, COLOR_BLACK);
	tft_drawRect(InstancePtr, SCORE_BOX3_START_X, SCORE_BOX_START_Y,
			SCORE_BOX4_END_X, SCORE_BOX_END_Y, COLOR_BLACK);

	// Current time
	tft_fillRect(InstancePtr, TIME_START_X, TIME_START_Y,
			TIME_END_X, TIME_END_Y, COLOR_GREY);
	tft_drawRect(InstancePtr, TIME_START_X, TIME_START_Y,
			TIME_END_X, TIME_END_Y, COLOR_BLACK);
	tft_writeString(InstancePtr, TIME_START_X, TIME_START_Y - 20,
			"Time: ", COLOR_BLACK, COLOR_WHITE);

	// Current Ball Speed
	tft_fillRect(InstancePtr, BALL_SPEED_START_X, BALL_SPEED_START_Y,
			BALL_SPEED_END_X, BALL_SPEED_END_Y, COLOR_GREY);
	tft_drawRect(InstancePtr, BALL_SPEED_START_X, BALL_SPEED_START_Y,
			BALL_SPEED_END_X, BALL_SPEED_END_Y, COLOR_BLACK);
	tft_writeString(InstancePtr, BALL_SPEED_START_X, BALL_SPEED_START_Y - 20,
			"Ball Speed: ", COLOR_BLACK, COLOR_WHITE);

	// Bricks Left
	tft_fillRect(InstancePtr, BRICK_LEFT_START_X, BRICK_LEFT_START_Y,
			BRICK_LEFT_END_X, BRICK_LEFT_END_Y, COLOR_GREY);
	tft_drawRect(InstancePtr, BRICK_LEFT_START_X, BRICK_LEFT_START_Y,
			BRICK_LEFT_END_X, BRICK_LEFT_END_Y, COLOR_BLACK);
	tft_writeString(InstancePtr, BRICK_LEFT_START_X, BALL_SPEED_END_Y + 5,
			"Bricks left: ", COLOR_BLACK, COLOR_WHITE);

	tft_addCircle(InstancePtr, CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS);
}

int tft_updateDisplay(XTft *InstancePtr);

int tft_updateColumn(XTft *InstancePtr, const int col_x, int currentBricks,
		int futureBricks, unsigned int currentColour, unsigned int futureColour) {

	int row_num, row_y, updateBricks, updateAddBricks, updateRemoveBricks;



	updateBricks =  currentBricks ^ futureBricks; // get required bricks to update
	updateAddBricks = futureBricks & updateBricks;	// get what bricks to add.
	updateRemoveBricks = (~futureBricks) & updateBricks; // get what bricks to remove


	// case 1 : need remove bricks.

	row_num = 0; // reset row number

	while(updateRemoveBricks)
	{
		// removeBricks if there is bricks to remove
		if(updateRemoveBricks & 1)
		{
			// if current bricks is to be removed....
			row_y = ROW_Y_START + ROW_OFFSET * row_num; // position of y to draw rect.

			tft_removeBrick(InstancePtr, col_x, row_y,
					col_x + BRICK_SIZE_LENGTH, row_y + BRICK_SIZE_HEIGHT);
		}
		
		updateRemoveBricks = updateRemoveBricks >> 1; // move to next brick to check
		row_num++;
	}



	// case 2 : need add bricks.

	row_num = 0; // reset row number

	while(updateAddBricks)
	{
		// addBricks if there is bricks to add
		if(updateAddBricks & 1)
		{
			// if current bricks is to be added....
			row_y = ROW_Y_START + ROW_OFFSET * row_num; // position of y to draw rect.

			tft_addBrick(InstancePtr, col_x, row_y,
					col_x + BRICK_SIZE_LENGTH, row_y + BRICK_SIZE_HEIGHT);
		}
		
		updateAddBricks = updateAddBricks >> 1; // move to next brick to check
		row_num++;
	}

	// case 3 : need update colour (bricks are already added/remove... just fill them)
	
	row_num = 0; // reset row number

	while(futureBricks && (currentColour != futureColour))
	{
		// fill all bricks in futureBricks
		if(futureBricks & 1)
		{
			// if current bricks is to be filled....
			row_y = ROW_Y_START + ROW_OFFSET * row_num; // position of y to draw rect.

			tft_fillBrick(InstancePtr, col_x, row_y, col_x + BRICK_SIZE_LENGTH,
					row_y + BRICK_SIZE_HEIGHT, futureColour);


			tft_addBrick(InstancePtr, col_x, row_y,
					col_x + BRICK_SIZE_LENGTH, row_y + BRICK_SIZE_HEIGHT);
		}
		
		futureBricks = futureBricks >> 1; // move to next brick to check
		row_num++;
	}

}

int tft_updateScore(XTft *InstancePtr, int score) {
	int score_Digit_Hundredth, score_Digit_Tens, score_Digit_Ones;
	if (score != 0)
		score_Digit_Ones = score % 10;
	else
		score_Digit_Ones = 0;
	score = score / 10;
	if (score != 0)
		score_Digit_Tens = score % 10;
	else
		score_Digit_Tens = 0;
	score = score / 10;
	if (score != 0)
		score_Digit_Hundredth = score % 10;
	else
		score_Digit_Hundredth = 0;

	tft_writeInteger(InstancePtr, SCORE_BOX1_START_X + 9,
			SCORE_BOX_START_Y + 15, score_Digit_Hundredth, COLOR_BLACK,
			COLOR_GREY); //first number
	tft_writeInteger(InstancePtr, SCORE_BOX2_START_X + 9,
			SCORE_BOX_START_Y + 15, score_Digit_Tens, COLOR_BLACK, COLOR_GREY); //second number
	tft_writeInteger(InstancePtr, SCORE_BOX3_START_X + 9,
			SCORE_BOX_START_Y + 15, score_Digit_Ones, COLOR_BLACK, COLOR_GREY); //third number
}

int tft_updateSpeed(XTft *InstancePtr, int speed) {
	tft_writeInteger(InstancePtr, BALL_SPEED_START_X + 50,
			BALL_SPEED_START_Y + 5, speed, COLOR_BLACK, COLOR_GREY);
}

int tft_updateBricksLeft(XTft *InstancePtr, int bricksLeft) {
	int temp_brickLeft = bricksLeft, count = 0;
	while ((temp_brickLeft /= 10) != 0) {
		count++;
	}
	switch (count) {
	case 0:
		tft_writeInteger(InstancePtr, BRICK_LEFT_START_X + 53,
				BRICK_LEFT_START_Y + 5, bricksLeft, COLOR_BLACK, COLOR_GREY);
		break;
	case 1:
		tft_writeInteger(InstancePtr, BRICK_LEFT_START_X + 53,
				BRICK_LEFT_START_Y + 5, bricksLeft, COLOR_BLACK, COLOR_GREY);
		break;
	case 2:
		tft_writeInteger(InstancePtr, BRICK_LEFT_START_X + 50,
				BRICK_LEFT_START_Y + 5, bricksLeft, COLOR_BLACK, COLOR_GREY);
		break;
	}

}

int tft_writeInteger(XTft *InstancePtr, int x, int y, const int value,
		u32 foreGround, u32 backGround) {
	char buffer[6];
	itoa(value, buffer);
	return tft_writeString(InstancePtr, x, y, buffer, foreGround, backGround);
}

int tft_writeString(XTft *InstancePtr, int x, int y, const char *CharValue,
		u32 foreGround, u32 backGround) {
	/*
	 * Writes a character from the string to the screen
	 * until it reaches null or end of the string.
	 */
	XTft_SetPosChar(InstancePtr, x, y);
	XTft_SetColor(InstancePtr, foreGround, backGround);
	while (*CharValue != 0) {
		XTft_Write(InstancePtr, *CharValue);
		CharValue++;
	}

	return XST_SUCCESS;
}

int tft_addCircle(XTft *InstancePtr, int x0, int y0, int radius) {
	tft_drawCircle(InstancePtr, x0, y0, radius, COLOR_YELLOW);
}

int tft_removeCircle(XTft *InstancePtr, int x0, int y0, int radius) {
	tft_drawCircle(InstancePtr, x0, y0, radius, COLOR_GREEN);
}

int tft_drawCircle(XTft *InstancePtr, int x0, int y0, int radius,
		unsigned int colour) {
	int x = radius;
	int y = 0;
	int decisionOver2 = 1 - x; // Decision criterion divided by 2 evaluated at x=r, y=0

	// check if circle exceed boundary
	if (x0 + radius > DISPLAY_COLUMNS || y0 + radius > DISPLAY_ROWS
			|| x0 - radius < 0 || y0 - radius < 0) {
		// exceed boundary to draw circle..
		return XST_FAILURE;
	}

	while (y <= x) {
		//XTft_SetPixel(Tft, x + x0,  y + y0, FGCOLOR_GREEEN); // Octant 1 (outline)
		//XTft_SetPixel(Tft, -x + x0,  y + y0, FGCOLOR_GREEEN); // Octant 4 (outline)
		tft_drawLine(InstancePtr, -x + x0, y0 + y, x + x0, y0 + y, colour);

		//XTft_SetPixel(Tft, y + x0,  x + y0, FGCOLOR_GREEEN); // Octant 2 (outline)
		//XTft_SetPixel(Tft, -y + x0,  x + y0, FGCOLOR_GREEEN); // Octant 3 (outline)
		tft_drawLine(InstancePtr, -y + x0, x + y0, y + x0, x + y0, colour);

		//XTft_SetPixel(Tft, -x + x0, -y + y0, FGCOLOR_GREEEN); // Octant 5 (outline)
		//XTft_SetPixel(Tft, x + x0, -y + y0, FGCOLOR_GREEEN); // Octant 7 (outline)
		tft_drawLine(InstancePtr, -x + x0, -y + y0, x + x0, -y + y0, colour);

		//XTft_SetPixel(Tft, -y + x0, -x + y0, FGCOLOR_GREEEN); // Octant 6 (outline)
		//XTft_SetPixel(Tft, y + x0, -x + y0, FGCOLOR_GREEEN); // Octant 8 (outline)
		tft_drawLine(InstancePtr, -y + x0, -x + y0, y + x0, -x + y0, colour);

		y++;

		if (decisionOver2 <= 0) {
			decisionOver2 += 2 * y + 1; // Change in decision criterion for y -> y+1
		} else {
			x--;
			decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
		}
	}

	return XST_SUCCESS;
}

int tft_addBrick(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos) {

	tft_drawRect(InstancePtr, ColStartPos, RowStartPos, ColEndPos, RowEndPos,
			COLOR_BLACK);
}

int tft_removeBrick(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos) {

	tft_fillRect(InstancePtr, ColStartPos, RowStartPos, ColEndPos, RowEndPos,
			COLOR_GREEN);
}

int tft_fillBrick(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos, unsigned int color) {

	tft_fillRect(InstancePtr, ColStartPos, RowStartPos, ColEndPos, RowEndPos,
			color);
}

int tft_addBar(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos, unsigned int colour) {
	tft_drawRect(InstancePtr, ColStartPos, RowStartPos, ColEndPos, RowEndPos,
			COLOR_BLACK); // line color = black

	// tft_fillRect(InstancePtr, ColStartPos, RowStartPos, ColEndPos, RowEndPos,
	// 		colour); // line color = black

}

int tft_moveBarLeft(XTft *InstancePtr) {
	if (barLeftPos > 0) {
		barLeftPos = barLeftPos - 25;
		tft_drawRect(InstancePtr, BAR_START_X, BAR_START_Y, BAR_END_X,
				BAR_START_Y, COLOR_GREEN);
		tft_drawRect(InstancePtr, barLeftPos, BAR_START_Y, barRightPos,
				BAR_START_Y, COLOR_BLACK);
		//XTft_SetPixel(InstancePtr, barRightPos, BAR_START_Y, COLOR_WHITE); // clear 1 pixel
		///XTft_SetPixel(InstancePtr, barLeftPos, BAR_START_Y, COLOR_BLUE); // set 1 pixel
		barRightPos = barRightPos - 25;

	}
}

int tft_moveBarRight(XTft *InstancePtr) {
	if (barRightPos < DISPLAY_COLUMNS - 1) {
		barRightPos = barRightPos + 25;
		tft_drawRect(InstancePtr, BAR_START_X, BAR_START_Y, BAR_END_X,
				BAR_START_Y, COLOR_GREEN);
		tft_drawRect(InstancePtr, barRightPos, BAR_START_Y, barLeftPos,
				BAR_START_Y, COLOR_BLACK);
		//XTft_SetPixel(InstancePtr, barLeftPos, BAR_START_Y, COLOR_WHITE); // clear 1 pixel
		//XTft_SetPixel(InstancePtr, barRightPos, BAR_START_Y, COLOR_BLUE); // set 1 pixel
		barLeftPos = barLeftPos + 25;
	}
}

int tft_drawLine(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos, unsigned int colour) {
	u32 Slope;
	u32 YIntercept;
	u32 Xmin;
	u32 Ymin;
	u32 Xmax;
	u32 Ymax;
	u32 Index1;
	u32 Index2;
	u32 Mx;

	/*
	 * Check whether the given position of X,Y dimensions
	 * are below the limits of the screen.
	 */
	if (ColStartPos >= 0 && ColStartPos <= (XTFT_DISPLAY_WIDTH - 1)
			&& ColEndPos >= 0 && ColEndPos <= (XTFT_DISPLAY_WIDTH - 1)
			&& RowStartPos >= 0 && RowStartPos <= (XTFT_DISPLAY_HEIGHT - 1)
			&& RowEndPos >= 0 && RowEndPos <= (XTFT_DISPLAY_HEIGHT - 1)) {

		/*
		 * Check the exception case where slope can be infinite
		 * that is vertical line.
		 */
		if (ColEndPos - ColStartPos != 0) {
			/*
			 * Calculate slope.
			 */
			Slope = ((RowEndPos - RowStartPos) / (ColEndPos - ColStartPos)
					* 100000);

			/*
			 * Calculate y intercept.
			 */
			YIntercept = RowStartPos - ((Slope / 100000) * ColStartPos);
		} else {
			/*
			 * Divide by zero.
			 */
			Slope = 0;
			YIntercept = (-1);
		}

		/*
		 * Update the min and max position by conditional checking.
		 */
		if (ColEndPos < ColStartPos) {
			Xmin = ColEndPos;
			Xmax = ColStartPos;
		} else {
			Xmin = ColStartPos;
			Xmax = ColEndPos;
		}
		if (RowEndPos < RowStartPos) {
			Ymin = RowEndPos;
			Ymax = RowStartPos;
		} else {
			Ymin = RowStartPos;
			Ymax = RowEndPos;
		}

		/*
		 * Increment X and Y position values and calculate
		 * slope at the corresponding x position. Check the condition
		 * for general line equation and set the pixel. Otherwise check
		 * for the case of vertical line.
		 */
		for (Index1 = Xmin; Index1 <= Xmax; Index1++) {
			Mx = (Slope * Index1) / 100000;
			for (Index2 = Ymin; Index2 <= Ymax; Index2++) {
				if ((Index2 - Mx) == YIntercept) {

					/*
					 * Calculate visible line.
					 */
					XTft_SetPixel(InstancePtr, Index1, Index2, colour);
				} else {
					/*
					 * Divide by zero.
					 */
					if ((Slope == 0) && (YIntercept == -1)) {

						/*
						 * Vertical line.
						 */
						XTft_SetPixel(InstancePtr, Index1, Index2, colour);
					}
				}
			}
		}
		return XST_SUCCESS;
	} else {
		return XST_FAILURE;
	}
}

void tft_drawRect(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos, u32 colour) {
	tft_drawLine(InstancePtr, ColStartPos, RowStartPos, ColEndPos, RowStartPos,
			colour);
	tft_drawLine(InstancePtr, ColStartPos, RowStartPos, ColStartPos, RowEndPos,
			colour);
	tft_drawLine(InstancePtr, ColStartPos, RowEndPos, ColEndPos, RowEndPos,
			colour);
	tft_drawLine(InstancePtr, ColEndPos, RowStartPos, ColEndPos, RowEndPos,
			colour);
}

void tft_fillRect(XTft *InstancePtr, u32 ColStartPos, u32 RowStartPos,
		u32 ColEndPos, u32 RowEndPos, u32 colour) {
	XTft_FillScreen(InstancePtr, ColStartPos, RowStartPos, ColEndPos, RowEndPos,
			colour);
}

void itoa(int n, char s[]) {
	int i, sign;

	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	i = 0;
	do { /* generate digits in reverse order */
		s[i++] = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[]) {
	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

