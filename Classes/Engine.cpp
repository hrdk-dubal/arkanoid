#include "Engine.h"

USING_NS_CC;
using namespace std;

Engine::Engine(const Rect &gameplay_area, const Vec2 &paddle_init_position, 
	const cocos2d::Size& paddle_size) :
		m_gameplay_area(gameplay_area),
		m_paddle(paddle_init_position, paddle_size, gameplay_area.getMinX(), gameplay_area.getMaxX())
{}

Engine::~Engine()
{}

void Engine::movePaddle(const PaddleMovement movement_direction)
{
	m_paddle.move(movement_direction);
}

void Engine::stopPaddle()
{
	m_paddle.stopPaddle();
}

void Engine::update(const float dt)
{
	m_paddle.calculateMovement(dt);
}

Vec2 Engine::getPaddlePosition() const
{
	return m_paddle.getPosition();
}

void Engine::createBrick(const BrickType brick_type, const cocos2d::Vec2& position, 
	const cocos2d::Size& size)
{
	Brick new_brick(brick_type, position, size);
	m_all_bricks.push_back(new_brick);
}