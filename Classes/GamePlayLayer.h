#ifndef __GAMEPLAY_LAYER_H__
#define __GAMEPLAY_LAYER_H__

#include "cocos2d.h"
#include "Paddle.h"

class GamePlayLayer : public cocos2d::Layer
{
public:
	GamePlayLayer();
	CREATE_FUNC(GamePlayLayer);
	virtual bool init();

private:
	
};

#endif //__GAMEPLAY_LAYER_H__