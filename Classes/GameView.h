#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "cocos2d.h"
#include "Engine.h"

class GameView
{
public:
	GameView(Engine* engine, cocos2d::Sprite* paddle_sprite, cocos2d::Sprite* ball_sprite,
		cocos2d::Label* game_start_message, cocos2d::Label* game_restart_message, 
		cocos2d::Label* score_display);
	~GameView();

	void updateView();
	
	void addBrickSprite(cocos2d::Sprite* brick_sprite);

	/*void hideStartMessage();
	void hideGameOverMessage();
	void showStartMessage();
	void showGameOverMessage();
	*/
private:
	const Engine*					m_engine;
	cocos2d::Sprite*				m_paddle_sprite;
	cocos2d::Sprite*				m_ball_sprite;
	std::vector<cocos2d::Sprite*>	m_all_brick_sprites;
	cocos2d::Label*					m_game_start_message;
	cocos2d::Label*					m_game_restart_message;
	cocos2d::Label*					m_score_display;
};

#endif // !__GAME_VIEW_H__