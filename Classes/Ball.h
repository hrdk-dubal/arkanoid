#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"

class Ball
{
public:
	Ball(const cocos2d::Vec2 &init_position, const cocos2d::Size &size, const cocos2d::Rect &game_area);
	void calculateMovement(const float dt);
	void bounceFromVerticalSurface();
	void bounceFromHorizontalSurface();
	cocos2d::Vec2 getPosition() const;

private:
	cocos2d::Vec2			m_position;
	cocos2d::Size			m_size;
	const cocos2d::Rect		m_game_area;
	cocos2d::Vec2			m_velocity;
};

#endif