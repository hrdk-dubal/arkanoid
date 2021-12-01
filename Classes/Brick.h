#ifndef __BRICK_H__
#define __BRICK_H__

#include "cocos2d.h"

enum class BrickType
{
	brick_gray,
	brick_red,
	brick_green
};

class Brick
{
public:
	Brick(const BrickType brick_type, const cocos2d::Vec2 &position, const cocos2d::Size &size);

	BrickType getBrickType();
	cocos2d::Vec2 getPosition();
	cocos2d::Size getSize();

	unsigned short registerHit(); //return reward points if brick gets destroyed due to current hit

private:
	BrickType				m_brick_type;
	const cocos2d::Vec2		m_position;
	const cocos2d::Size		m_size;
	unsigned short			m_remaining_hits;
	unsigned short			m_reward_points;
	bool					m_is_destroyed;
};

#endif // !__BRICK_H__