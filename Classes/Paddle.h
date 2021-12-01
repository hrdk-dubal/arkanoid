#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "cocos2d.h"

class Paddle
{
public:
	Paddle(const cocos2d::Vec2 &init_position, const float left_bound, 
		const float right_bound);

	void accelerate();
	void decelerate();
	void calculateMovement(const float dt);
	cocos2d::Vec2 getPosition() const;

private:
	cocos2d::Vec2			m_position;
	const float				m_left_bound;
	const float				m_right_bound;
	const float				m_acceleration_step_value;
	const float				m_max_acceleration;
	const float				m_max_velocity;
	float					m_horizontal_acceleration;
	float					m_horizontal_velocity;
	float					m_horizontal_friction;

	int findDirection(const float value) const;
	void changeAcceleration(const float da);
};


#endif // !__PADDLE_H__