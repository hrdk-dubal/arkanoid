#include "Engine.h"

USING_NS_CC;

Engine::Engine(const Rect &gameplay_area, const Vec2 &paddle_init_position) :
	m_gameplay_area(gameplay_area),
	m_paddle(paddle_init_position, gameplay_area.getMinX(), gameplay_area.getMaxX())
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