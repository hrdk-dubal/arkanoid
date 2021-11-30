#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "Engine.h"
#include "cocos2d.h"
#include "Paddle.h"

class Engine
{
public:
	Engine(const cocos2d::Vec2 &paddle_position, cocos2d::Sprite* paddle_sprite,
		const float left_bound, const float right_bound);

private:
	Paddle m_paddle;
};

#endif // __ENGINE_H__
