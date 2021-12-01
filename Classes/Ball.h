#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"
#include "GameEntity.h"

class Ball : public GameEntity
{
public:
	Ball(const cocos2d::Vec2 &init_position, const cocos2d::Size &size, const cocos2d::Rect &game_area);
	void calculateMovement(const float dt);
	void bounceFromVerticalSurface();
	void bounceFromHorizontalSurface();
	void cancelLastMovement();

private:
	
	const cocos2d::Rect		m_game_area;
	cocos2d::Vec2			m_velocity;
};

#endif