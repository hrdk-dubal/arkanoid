#ifndef __GAMEPLAY_LAYER_H__
#define __GAMEPLAY_LAYER_H__

#include "cocos2d.h"
#include "Engine.h"
#include "GameView.h"

class GamePlayLayer : public cocos2d::Layer
{
public:
	GamePlayLayer();
	~GamePlayLayer();

	CREATE_FUNC(GamePlayLayer);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	virtual void update(float dt);

private:
	Engine*				m_engine;
	GameView*			m_game_view;
	bool				m_is_touch_pressed;
	cocos2d::Sprite*	m_paddle_sprite;

	cocos2d::Rect calculateGamePlayArea() const;
	bool initBoundarySprites(const cocos2d::Rect &inner_gameplay_area);
	bool initPaddle(const cocos2d::Rect& inner_gameplay_area);
	void movePaddleBasedOnInput();
};

#endif //__GAMEPLAY_LAYER_H__