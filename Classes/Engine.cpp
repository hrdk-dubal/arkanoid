#include "Engine.h"

USING_NS_CC;

Engine::Engine(Rect &gameplay_area, Sprite* paddle_sprite) :
	m_gameplay_area(gameplay_area),
	m_paddle(paddle_sprite, gameplay_area.getMinX(), gameplay_area.getMaxX())
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