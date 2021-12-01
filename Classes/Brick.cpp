#include "Brick.h"

USING_NS_CC;

Brick::Brick(const BrickType brick_type, const Vec2 &position, const Size &size) :
	GameEntity(position, size),
	m_brick_type(brick_type)
{
	switch (m_brick_type)
	{
	case BrickType::brick_gray:
		m_remaining_hits = SHRT_MAX;
		m_reward_points = 0;
		break;
	case BrickType::brick_green:
		m_remaining_hits = 2;
		m_reward_points = 15;
		break;
	case BrickType::brick_red:
		m_remaining_hits = 1;
		m_reward_points = 10;
		break;
	}
}

BrickType Brick::getBrickType() const
{
	return m_brick_type;
}

bool Brick::isDestroyed() const
{
	return m_is_destroyed;
}

unsigned short Brick::getRemainingHits() const
{
	return m_remaining_hits;
}

//return reward points if brick gets destroyed due to current hit
unsigned short Brick::registerHit()
{
	if (m_is_destroyed)
	{
		return 0;
	}

	if (m_brick_type == BrickType::brick_gray)
	{
		return m_reward_points;
	}

	m_remaining_hits--;
	if (m_remaining_hits == 0)
	{
		m_is_destroyed = true;
		return m_reward_points;
	}

	return 0;
}