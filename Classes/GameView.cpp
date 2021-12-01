#include "GameView.h"

USING_NS_CC;
using namespace std;

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

void GameView::addBrickSprite(cocos2d::Sprite* brick_sprite)
{
	m_all_brick_sprites.push_back(brick_sprite);
}