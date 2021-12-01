#ifndef __GAME_ENTITY_H__
#define __GAME_ENTITY_H__

#include "cocos2d.h"

class GameEntity
{
public:
	GameEntity(const cocos2d::Vec2& init_position, const cocos2d::Size& size);
	cocos2d::Vec2 getPosition() const;
	cocos2d::Size getSize() const;
	cocos2d::Rect getBoundingBox() const;
	cocos2d::Vec2 getPreviousPosition() const;
	cocos2d::Rect getPreviousBoundingBox() const;

protected:
	cocos2d::Size			m_size;
	void setPosition(const cocos2d::Vec2& new_position);

private:
	cocos2d::Vec2			m_position;
	cocos2d::Vec2			m_prev_position;
};


#endif // !__GAME_ENTITY_H__