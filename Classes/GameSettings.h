#ifndef __GAME_SETTINGS_H__
#define __GAME_SETTINGS_H__

#include "cocos2d.h"

#define NUM_ROWS 4
#define NUM_COLS 5
#define PADDLE_HEIGHT 120.0f
#define GAME_AREA_W 2048.0f
#define GAME_AREA_H 1536.0f

enum class brickType
{
	brick_gray,
	brick_red,
	brick_green
};

class GameSettings
{
public:
	static const int				m_numCols;
	static const int				m_numRows;
	static brickType				m_brickLayout[NUM_ROWS][NUM_COLS];

	static const cocos2d::Size		m_game_size;
	static const float				m_paddle_height;
};

#endif //__GAME_SETTINGS_H__