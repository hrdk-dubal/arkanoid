#include "Paddle.h"

USING_NS_CC;

Paddle::Paddle(const Vec2 &initPosition, Sprite* sprite, const float left_bound, 
	const float right_bound) :
		m_position(initPosition),
		m_sprite(sprite),
		m_left_bound(left_bound),
		m_right_bound(right_bound),
		m_horizontal_acceleration(0.0f),
		m_horizontal_velocity(0.0f),
		m_horizontal_friction(0.5f)
{}

void Paddle::calculateMovement(const float dt)
{
	const float dv = dt * m_horizontal_acceleration;
	m_horizontal_velocity += dv;

	const float absolute_velocity = fabsf(m_horizontal_velocity);
	const int friction_direction = (m_horizontal_velocity != 0.0f) ?
		int(-1.0f * (m_horizontal_velocity / absolute_velocity)) :
		0;

	const float dv_due_to_friction = dt * m_horizontal_friction;
	m_horizontal_velocity += friction_direction * dv_due_to_friction;

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

	m_sprite->setPositionX(m_position.x);
}