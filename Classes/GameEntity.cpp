#include "GameEntity.h"

USING_NS_CC;

GameEntity::GameEntity(const cocos2d::Vec2& init_position, const cocos2d::Size& size) :
	m_position(init_position),
	m_prev_position(init_position),
	m_size(size)
{}

void GameEntity::setPosition(const cocos2d::Vec2& new_position)
{
	m_prev_position = m_position;
	m_position = new_position;
}

Vec2 GameEntity::getPosition() const
{
	return m_position;
}

Size GameEntity::getSize() const
{
	return m_size;
}

cocos2d::Rect GameEntity::getBoundingBox() const
{
	const Size half_size = m_size * 0.5f;
	const float left = m_position.x - half_size.width;
	const float bottom = m_position.y - half_size.height;

	const Rect bounding_box(left, bottom, m_size.width, m_size.height);

	return bounding_box;
}

Vec2 GameEntity::getPreviousPosition() const
{
	return m_prev_position;
}

cocos2d::Rect GameEntity::getPreviousBoundingBox() const
{
	const Size half_size = m_size * 0.5f;
	const float left = m_prev_position.x - half_size.width;
	const float bottom = m_prev_position.y - half_size.height;

	const Rect bounding_box(left, bottom, m_size.width, m_size.height);

	return bounding_box;
}