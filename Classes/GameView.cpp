#include "GameView.h"

USING_NS_CC;
using namespace std;

GameView::GameView(Engine* engine, Sprite* paddle_sprite, Sprite* ball_sprite,
					Label* game_start_message, Label* game_restart_message, Label* score_display) :
	m_engine(engine),
	m_paddle_sprite(paddle_sprite),
	m_ball_sprite(ball_sprite),
	m_game_start_message(game_start_message),
	m_game_restart_message(game_restart_message),
	m_score_display(score_display)
{}

GameView::~GameView()
{
	//do nothing
}

void GameView::updateView()
{
	const GameState current_game_state = m_engine->getCurrentState();
	switch (current_game_state)
	{
		case GameState::game_menu:
		{
			m_game_start_message->setVisible(true);
			m_game_restart_message->setVisible(false);
			break;
		}
		case GameState::game_ongoing:
		{
			Vec2 paddle_position(m_engine->getPaddlePosition());
			m_paddle_sprite->setPosition(paddle_position);

			Vec2 ball_position(m_engine->getBallPosition());
			m_ball_sprite->setPosition(ball_position);

			for (int brick_index = 0; brick_index < m_all_brick_sprites.size(); brick_index++)
			{
				const bool is_destroyed = m_engine->isBrickDestroyed(brick_index);
				if (is_destroyed)
				{
					m_all_brick_sprites[brick_index]->setVisible(false);
					continue;
				}

				const BrickType brick_type = m_engine->getBrickType(brick_index);
				const unsigned short remaining_hits = m_engine->getRemainingHitsOfBrick(brick_index);
				if (brick_type == BrickType::brick_green && remaining_hits == 1)
				{
					m_all_brick_sprites[brick_index]->initWithFile("green_brick_hit.png");
				}
			}

			std::string score_string = "Score: " + m_engine->getScore();
			m_score_display->setString(score_string);
			break;
		}
		case GameState::game_over:
		{
			m_game_start_message->setVisible(false);
			m_game_restart_message->setVisible(true);
			break;
		}
	}
}

void GameView::addBrickSprite(cocos2d::Sprite* brick_sprite)
{
	m_all_brick_sprites.push_back(brick_sprite);
}

/*
void GameView::hideStartMessage()
{
	m_game_start_message->setVisible(false);
}

void GameView::hideGameOverMessage()
{
	m_game_restart_message->setVisible(false);
}

void GameView::showStartMessage()
{
	m_game_start_message->setVisible(true);
}

void GameView::showGameOverMessage()
{
	m_game_restart_message->setVisible(true);
}
*/