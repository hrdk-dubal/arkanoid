#include "Paddle.h"

USING_NS_CC;

Paddle::Paddle(const cocos2d::Vec2& init_position, const float left_bound, const float right_bound) :
		m_position(init_position),
		m_left_bound(left_bound),
		m_right_bound(right_bound),
		m_horizontal_velocity(400.0f),
		m_movement_direction(PaddleMovement::move_none)
{}

void Paddle::move(const PaddleMovement movement_direction)
{
	m_movement_direction = movement_direction;
}

void Paddle::calculateMovement(const float dt)
{
	if (m_movement_direction == PaddleMovement::move_none)
	{
		return;
	}

	const float effective_velocity = m_horizontal_velocity * int(m_movement_direction);
	const float dx = effective_velocity * dt;
	CCLOG("dx: %f", dx);
	CCLOG("previous position: %f", m_position.x);
	m_position.x += dx;
	CCLOG("new position: %f", m_position.x);

	if (m_position.x < m_left_bound)
	{
			m_position.x = m_left_bound;
			stopPaddle();
	}

	if (m_position.x > m_right_bound)
	{
		m_position.x = m_right_bound;
		stopPaddle();
	}
}

void Paddle::stopPaddle()
{
	m_movement_direction = PaddleMovement::move_none;
}

Vec2 Paddle::getPosition() const
{
	return m_position;
}