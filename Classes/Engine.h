#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "Engine.h"
#include "cocos2d.h"
#include "Paddle.h"

class Engine
{
public:
	Engine(cocos2d::Rect &gameplay_area, cocos2d::Sprite* paddle_sprite);

	void acceleratePaddle();
	void deceleratePaddle();

	void update(const float dt);

private:
	cocos2d::Rect m_gameplay_area;
	Paddle m_paddle;
};

#endif // __ENGINE_H__
