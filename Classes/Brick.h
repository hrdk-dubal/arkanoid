#ifndef __BRICK_H__
#define __BRICK_H__

#include "cocos2d.h"
#include "GameEntity.h"

enum class BrickType
{
	brick_gray,
	brick_red,
	brick_green
};

class Brick : public GameEntity
{
public:
	Brick(const BrickType brick_type, const cocos2d::Vec2 &position, const cocos2d::Size &size);

	BrickType getBrickType() const;

	unsigned short registerHit(); //return reward points if brick gets destroyed due to current hit

	bool isDestroyed() const;
	unsigned short getRemainingHits() const;

private:
	BrickType				m_brick_type;
	const cocos2d::Vec2		m_position;
	const cocos2d::Size		m_size;
	unsigned short			m_remaining_hits;
	unsigned short			m_reward_points;
	bool					m_is_destroyed;
};

#endif // !__BRICK_H__