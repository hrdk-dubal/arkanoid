#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "cocos2d.h"
#include "GameEntity.h"

enum class PaddleMovement
{
	move_left = -1,
	move_none = 0,
	move_right = 1
};

class Paddle : public GameEntity
{
public:
	Paddle(const cocos2d::Vec2 &init_position, const cocos2d::Size &size, const float left_bound, 
		const float right_bound);

	void move(const PaddleMovement movement_direction);
	void stopPaddle();
	void calculateMovement(const float dt);

private:
	const float				m_left_bound;
	const float				m_right_bound;
	float					m_horizontal_velocity;
	PaddleMovement			m_movement_direction;
};


#endif // !__PADDLE_H__