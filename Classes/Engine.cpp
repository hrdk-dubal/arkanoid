#include "Engine.h"

USING_NS_CC;

Engine::Engine(const Rect &gameplay_area, const Vec2 &paddle_init_position) :
	m_gameplay_area(gameplay_area),
	m_paddle(paddle_init_position, gameplay_area.getMinX(), gameplay_area.getMaxX())
{}

void Engine::acceleratePaddle()
{
	m_paddle.accelerate();
}

void Engine::deceleratePaddle()
{
	m_paddle.decelerate();
}

void Engine::update(const float dt)
{
	m_paddle.calculateMovement(dt);
}

Vec2 Engine::getPaddlePosition() const
{
	return m_paddle.getPosition();
}