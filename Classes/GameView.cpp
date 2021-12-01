#include "GameView.h"

USING_NS_CC;

GameView::GameView(Engine* engine, Sprite* paddle_sprite) : 
	m_engine(engine),
	m_paddle_sprite(paddle_sprite)
{}

GameView::~GameView()
{
	//do nothing
}

void GameView::updateView()
{
	Vec2 paddle_position(m_engine->getPaddlePosition());
	m_paddle_sprite->setPosition(paddle_position);
}