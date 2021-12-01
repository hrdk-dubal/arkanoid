#include "Paddle.h"

USING_NS_CC;

Paddle::Paddle(const Vec2& init_position, const Size& size, 
	const float left_bound, const float right_bound) :
		m_position(init_position),
		m_size(size),
		m_left_bound(left_bound),
		m_right_bound(right_bound),
		m_horizontal_velocity(800.0f),
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
	
	m_position.x += dx;
	const Size half_paddle_size = m_size * 0.5f;

	if (m_position.x < m_left_bound + half_paddle_size.width)
	{
		m_position.x = m_left_bound + half_paddle_size.width;
		stopPaddle();
	}

	if (m_position.x > m_right_bound - half_paddle_size.width)
	{
		m_position.x = m_right_bound - half_paddle_size.width;
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