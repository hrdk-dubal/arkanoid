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
	cocos2d::Sprite*	m_ball_sprite;

	cocos2d::Rect calculateGamePlayArea() const;
	void initBoundarySprites(const cocos2d::Rect &inner_gameplay_area);
	void initPaddle(const cocos2d::Rect &inner_gameplay_area);
	void initBall(const cocos2d::Rect &inner_gameplay_area, 
		const cocos2d::Vec2 &paddle_position, const cocos2d::Size &paddle_size);
	void movePaddleBasedOnInput();
	void createBrickLayout(const cocos2d::Rect& inner_gameplay_area);
	void createBrick(const BrickType brick_type, const cocos2d::Vec2& position);
};

#endif //__GAMEPLAY_LAYER_H__