#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "cocos2d.h"
#include "Engine.h"

class GameView
{
public:
	GameView(Engine* engine, cocos2d::Sprite* paddle_sprite);
	~GameView();

	void updateView();

private:
	const Engine* m_engine;
	cocos2d::Sprite* m_paddle_sprite;

};

#endif // !__GAME_VIEW_H__