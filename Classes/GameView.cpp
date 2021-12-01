#include "GameView.h"

USING_NS_CC;
using namespace std;

GameView::GameView(Engine* engine, Sprite* paddle_sprite, Sprite* ball_sprite) :
	m_engine(engine),
	m_paddle_sprite(paddle_sprite),
	m_ball_sprite(ball_sprite)
{}

GameView::~GameView()
{
	//do nothing
}

void GameView::updateView()
{
	Vec2 paddle_position(m_engine->getPaddlePosition());
	m_paddle_sprite->setPosition(paddle_position);

	Vec2 ball_position(m_engine->getBallPosition());
	m_ball_sprite->setPosition(ball_position);
}

void GameView::addBrickSprite(cocos2d::Sprite* brick_sprite)
{
	m_all_brick_sprites.push_back(brick_sprite);
}