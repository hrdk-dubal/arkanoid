#include "Paddle.h"

USING_NS_CC;

Paddle::Paddle(const Vec2& init_position, const Size& size, 
	const float left_bound, const float right_bound) :
		GameEntity(init_position, size),
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
	
	const Vec2 new_position = getPosition() + Vec2(dx, 0);
	setPosition(new_position);

	const Size half_paddle_size = m_size * 0.5f;

	if (getPosition().x < m_left_bound + half_paddle_size.width)
	{
		const Vec2 new_position(m_left_bound + half_paddle_size.width, getPosition().y);
		setPosition(new_position);
		stopPaddle();
	}

	if (getPosition().x > m_right_bound - half_paddle_size.width)
	{
		const Vec2 new_position(m_right_bound - half_paddle_size.width, getPosition().y);
		setPosition(new_position);
		stopPaddle();
	}
}

void Paddle::stopPaddle()
{
	m_movement_direction = PaddleMovement::move_none;
}