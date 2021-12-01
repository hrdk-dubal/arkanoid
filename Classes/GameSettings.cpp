#include "GameSettings.h"

USING_NS_CC;

const int GameSettings::m_numRows = NUM_ROWS;

const int GameSettings::m_numCols = NUM_COLS;

BrickType GameSettings::m_brickLayout[NUM_ROWS][NUM_COLS] = 
{
	{ BrickType::brick_gray, BrickType::brick_gray, BrickType::brick_green, BrickType::brick_gray,BrickType::brick_gray },
	{ BrickType::brick_red, BrickType::brick_red, BrickType::brick_green, BrickType::brick_red,BrickType::brick_red },
	{ BrickType::brick_green, BrickType::brick_gray, BrickType::brick_green, BrickType::brick_gray,BrickType::brick_green },
	{ BrickType::brick_gray, BrickType::brick_red, BrickType::brick_red, BrickType::brick_red,BrickType::brick_gray }
};

const Size GameSettings::m_game_size(GAME_AREA_W, GAME_AREA_H);

const float GameSettings::m_paddle_height = PADDLE_HEIGHT;

const float GameSettings::m_brick_gap = BRICK_GAP;

const float GameSettings::m_brick_layout_top = BRICK_LAYOUT_TOP_MARGIN;

const float GameSettings::m_score_margin = SCORE_MARGIN;