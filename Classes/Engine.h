#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "Engine.h"
#include "cocos2d.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"

class Engine
{
public:
	Engine(const cocos2d::Rect &gameplay_area, 
		const cocos2d::Vec2 &paddle_init_position, const cocos2d::Size &paddle_size, 
		const cocos2d::Vec2 &ball_init_position, const cocos2d::Size &ball_size);
	~Engine();

	void movePaddle(const PaddleMovement movement_direction);
	void stopPaddle();
	cocos2d::Vec2 getPaddlePosition() const;
	cocos2d::Vec2 getBallPosition() const;

	void update(const float dt);
	void createBrick(const BrickType brick_type, const cocos2d::Vec2& position, const cocos2d::Size& size);

private:
	cocos2d::Rect			m_gameplay_area;
	Paddle					m_paddle;
	Ball					m_ball;
	std::vector<Brick>		m_all_bricks;
};

#endif // __ENGINE_H__
