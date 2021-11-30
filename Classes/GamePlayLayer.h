#ifndef __GAMEPLAY_LAYER_H__
#define __GAMEPLAY_LAYER_H__

#include "cocos2d.h"
#include "Engine.h"

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

private:
	Engine* m_engine;
	cocos2d::Sprite* m_paddle_sprite;
	
	bool setBoundaries();
	bool initPaddle();
	cocos2d::Rect m_inner_gameplay_area;
};

#endif //__GAMEPLAY_LAYER_H__