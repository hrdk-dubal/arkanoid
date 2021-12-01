#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "cocos2d.h"

enum class PaddleMovement
{
	move_left = -1,
	move_none = 0,
	move_right = 1
};

class Paddle
{
public:
	Paddle(const cocos2d::Vec2 &init_position, const float left_bound, 
		const float right_bound);

	void move(const PaddleMovement movement_direction);
	void stopPaddle();
	void calculateMovement(const float dt);
	cocos2d::Vec2 getPosition() const;

private:
	cocos2d::Vec2			m_position;
	const float				m_left_bound;
	const float				m_right_bound;
	float					m_horizontal_velocity;
	PaddleMovement			m_movement_direction;
};


#endif // !__PADDLE_H__