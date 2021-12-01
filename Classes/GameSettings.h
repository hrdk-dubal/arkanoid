#ifndef __GAME_SETTINGS_H__
#define __GAME_SETTINGS_H__

#include "cocos2d.h"
#include "Brick.h"

#define NUM_ROWS 4
#define NUM_COLS 5
#define PADDLE_HEIGHT 120.0f
#define GAME_AREA_W 2048.0f
#define GAME_AREA_H 1536.0f
#define BRICK_GAP 30.0f
#define BRICK_LAYOUT_TOP_MARGIN 50.0f
#define SCORE_MARGIN 50.0f

class GameSettings
{
public:
	static const int				m_numCols;
	static const int				m_numRows;
	static BrickType				m_brickLayout[NUM_ROWS][NUM_COLS];

	static const cocos2d::Size		m_game_size;
	static const float				m_paddle_height;

	static const float				m_brick_gap;
	static const float				m_brick_layout_top;

	static const float				m_score_margin;
};

#endif //__GAME_SETTINGS_H__