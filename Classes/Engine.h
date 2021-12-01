#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "Engine.h"
#include "cocos2d.h"
#include "Paddle.h"

class Engine
{
public:
	Engine(const cocos2d::Rect &gameplay_area, const cocos2d::Vec2 &paddle_init_position);

	void acceleratePaddle();
	void deceleratePaddle();
	cocos2d::Vec2 getPaddlePosition() const;

	void update(const float dt);

private:
	cocos2d::Rect m_gameplay_area;
	Paddle m_paddle;
};

#endif // __ENGINE_H__
