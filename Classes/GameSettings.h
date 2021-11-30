#ifndef __GAME_SETTINGS_H__
#define __GAME_SETTINGS_H__
#define NUM_ROWS 4
#define NUM_COLS 5

enum class brickType
{
	brick_gray,
	brick_red,
	brick_green
};

class GameSettings
{
private:
	static const int	m_numCols;
	static const int	m_numRows;
	static brickType	m_brickLayout[NUM_ROWS][NUM_COLS];
};

#endif //__GAME_SETTINGS_H__