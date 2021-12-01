#include "Ball.h"

USING_NS_CC;

Ball::Ball(const Vec2 &init_position, const Size &size, const Rect &game_area):
		GameEntity(init_position, size),
		m_game_area(game_area),
		m_velocity(750.0f, 450.0f)
{}

void Ball::calculateMovement(const float dt)
{
	const Vec2 dp = m_velocity * dt;
	const Vec2 new_position = getPosition() + dp;
	const Size half_ball_size = m_size * 0.5f;
	const float left_bound = m_game_area.getMinX();
	const float right_bound = m_game_area.getMaxX();
	const float top_bound = m_game_area.getMaxY();

	if (new_position.x < (left_bound + half_ball_size.width) || 
		new_position.x > right_bound - half_ball_size.width)
	{
		bounceFromVerticalSurface();
		return;
	}

	if (new_position.y > (top_bound - half_ball_size.height))
	{
		bounceFromHorizontalSurface();
		return;
	}

	setPosition(new_position);
}

void Ball::cancelLastMovement()
{
	setPosition(getPreviousPosition());
}

void Ball::bounceFromVerticalSurface()
{
	m_velocity.x = -m_velocity.x;
}

void Ball::bounceFromHorizontalSurface()
{
	m_velocity.y = -m_velocity.y;
}