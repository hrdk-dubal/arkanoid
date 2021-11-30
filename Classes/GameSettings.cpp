#include "GameSettings.h"

const int GameSettings::m_numRows = NUM_ROWS;

const int GameSettings::m_numCols = NUM_COLS;

brickType GameSettings::m_brickLayout[NUM_ROWS][NUM_COLS] = 
{
	{ brickType::brick_gray, brickType::brick_gray, brickType::brick_green, brickType::brick_gray,brickType::brick_red },
	{ brickType::brick_gray, brickType::brick_gray, brickType::brick_green, brickType::brick_gray,brickType::brick_red },
	{ brickType::brick_gray, brickType::brick_gray, brickType::brick_green, brickType::brick_gray,brickType::brick_red },
	{ brickType::brick_gray, brickType::brick_gray, brickType::brick_green, brickType::brick_gray,brickType::brick_red }
};

const float GameSettings::m_paddle_height = PADDLE_HEIGHT;