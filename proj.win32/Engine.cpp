#include "Engine.h"

Engine::Engine(const cocos2d::Vec2 &paddle_position, cocos2d::Sprite* paddle_sprite,
	const float left_bound, const float right_bound) :
	m_paddle(paddle_position, paddle_sprite, left_bound, right_bound)
{}