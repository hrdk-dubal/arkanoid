#include "Paddle.h"

USING_NS_CC;

Paddle::Paddle(Sprite* sprite, const float left_bound, 
	const float right_bound) :
		m_position(sprite->getPosition()),
		m_sprite(sprite),
		m_left_bound(left_bound),
		m_right_bound(right_bound),
		m_acceleration_step_value(0.1f),
		m_max_acceleration(0.1f),
		m_max_velocity(400.0f),
		m_horizontal_acceleration(0.0f),
		m_horizontal_velocity(0.0f),
		m_horizontal_friction(0.05f)
{}

int Paddle::findDirection(const float value) const
{
	const float absolute_value = fabsf(value);
	const int direction = int(value / absolute_value);
	return direction;
}

void Paddle::changeAcceleration(const float da)
{
	m_horizontal_acceleration += da;
	if (m_horizontal_acceleration > m_max_acceleration)
	{
		m_horizontal_acceleration = m_max_acceleration;
	}
	if (m_horizontal_acceleration < -m_max_acceleration)
	{
		m_horizontal_acceleration = -m_max_acceleration;
	}
}

void Paddle::accelerate()
{
	const int direction = findDirection(m_horizontal_acceleration);
	const float da = (m_acceleration_step_value * direction);
	changeAcceleration(da);
}

void Paddle::decelerate()
{
	const int direction = (-1) * findDirection(m_horizontal_acceleration);
	const float da = (m_acceleration_step_value * direction);
	changeAcceleration(da);
}

void Paddle::calculateMovement(const float dt)
{
	const float dv = dt * m_horizontal_acceleration;
	const float dv_due_to_friction = dt * m_horizontal_friction;
	const float net_dv = dv - dv_due_to_friction;

	const int previous_direction = findDirection(m_horizontal_velocity);
	m_horizontal_velocity += net_dv;
	const int new_direction = findDirection(m_horizontal_velocity);
	
	if (new_direction != previous_direction)
	{
		m_horizontal_velocity = 0.0f;
	}
	else
	{
		if (m_horizontal_velocity > m_max_velocity)
		{
			m_horizontal_velocity = m_max_velocity;
		}

		const float dx = m_horizontal_velocity * dt;
		m_position.x += dx;

		if (m_position.x < m_left_bound)
		{
			m_position.x = m_left_bound;
			m_horizontal_velocity = 0.0f;
		}

		if (m_position.x > m_right_bound)
		{
			m_position.x = m_right_bound;
			m_horizontal_velocity = 0.0f;
		}
	}

	m_sprite->setPositionX(m_position.x);
}