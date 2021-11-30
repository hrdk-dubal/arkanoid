#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "cocos2d.h"

class Paddle
{
public:
	Paddle(const cocos2d::Vec2 &initPosition, cocos2d::Sprite* sprite, const float left_bound, 
		const float right_bound);

	void calculateMovement(const float dt);

private:
	cocos2d::Vec2			m_position;
	cocos2d::Sprite*		m_sprite;
	const float				m_left_bound;
	const float				m_right_bound;
	float					m_horizontal_acceleration;
	float					m_horizontal_velocity;
	float					m_horizontal_friction;
};


#endif // !__PADDLE_H__