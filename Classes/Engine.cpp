#include "Engine.h"

USING_NS_CC;
using namespace std;

Engine::Engine(const Rect &gameplay_area, 
	const Vec2 &paddle_init_position, const cocos2d::Size& paddle_size,
	const Vec2 &ball_init_position, const Size &ball_size) :
		m_gameplay_area(gameplay_area),
		m_paddle(paddle_init_position, paddle_size, gameplay_area.getMinX(), gameplay_area.getMaxX()),
		m_ball(ball_init_position, ball_size, gameplay_area),
		m_score(0),
		m_game_state(GameState::game_menu)
{}

Engine::~Engine()
{}

void Engine::movePaddle(const PaddleMovement movement_direction)
{
	if (m_game_state != GameState::game_ongoing)
	{
		return;
	}
	m_paddle.move(movement_direction);
}

void Engine::stopPaddle()
{
	if (m_game_state != GameState::game_ongoing)
	{
		return;
	}
	m_paddle.stopPaddle();
}

void Engine::startGame()
{
	m_game_state = GameState::game_ongoing;
}

void Engine::update(const float dt)
{
	if (m_game_state != GameState::game_ongoing)
	{
		return;
	}

	m_paddle.calculateMovement(dt);
	m_ball.calculateMovement(dt);
	const bool is_game_over = checkGameOver();
	if (is_game_over)
	{
		m_game_state = GameState::game_over;
		return;
	}

	ballCollisionCheck(&m_paddle);

	for (unsigned short brick_index = 0; brick_index < m_all_bricks.size(); brick_index++)
	{
		Brick& brick = m_all_bricks[brick_index];
		if (brick.isDestroyed())
		{
			continue;
		}

		bool hit_with_brick = ballCollisionCheck(&brick);
		if (hit_with_brick)
		{
			const unsigned short reward_points = brick.registerHit();
			m_score += reward_points;
		}
	}
}

GameState Engine::getCurrentState() const
{
	return m_game_state;
}

bool Engine::isBrickDestroyed(unsigned short brick_index) const
{
	const Brick& brick = m_all_bricks[brick_index];
	return brick.isDestroyed();
}

BrickType Engine::getBrickType(unsigned short brick_index) const
{
	const Brick& brick = m_all_bricks[brick_index];
	return brick.getBrickType();
}

unsigned short Engine::getRemainingHitsOfBrick(unsigned short brick_index) const
{
	const Brick& brick = m_all_bricks[brick_index];
	return brick.getRemainingHits();
}
Vec2 Engine::getPaddlePosition() const
{
	return m_paddle.getPosition();
}

Vec2 Engine::getBallPosition() const
{
	return m_ball.getPosition();
}

unsigned int Engine::getScore() const
{
	return m_score;
}

bool Engine::checkGameOver() const
{
	const Rect ball_bounding_box(m_ball.getBoundingBox());
	const Rect paddle_bounding_box(m_paddle.getBoundingBox());
	if (ball_bounding_box.getMaxY() <= paddle_bounding_box.getMinY())
	{
		return true;
	}

	return false;
}

void Engine::createBrick(const BrickType brick_type, const cocos2d::Vec2& position, 
	const cocos2d::Size& size)
{
	Brick new_brick(brick_type, position, size);
	m_all_bricks.push_back(new_brick);
}

bool Engine::ballCollisionCheck(GameEntity* gameEntity)
{
	const Rect ball_bounding_box(m_ball.getBoundingBox());
	const Rect ball_prev_bounding_box(m_ball.getPreviousBoundingBox());
	const Rect entity_bounding_box(gameEntity->getBoundingBox());

	if (ball_bounding_box.intersectsRect(entity_bounding_box))
	{
		if (ball_prev_bounding_box.getMaxX() < entity_bounding_box.getMinX() &&
			ball_bounding_box.getMaxX() >= entity_bounding_box.getMinX())
		{
			//ball touched paddle from the left edge of the entity
			m_ball.bounceFromVerticalSurface();
			m_ball.cancelLastMovement();
		}

		if (ball_prev_bounding_box.getMinX() > entity_bounding_box.getMaxX() &&
			ball_bounding_box.getMinX() >= entity_bounding_box.getMaxX())
		{
			//ball touched paddle from the right edge of the entity
			m_ball.bounceFromVerticalSurface();
			m_ball.cancelLastMovement();
		}

		if (ball_prev_bounding_box.getMinY() > entity_bounding_box.getMaxY() &&
				ball_bounding_box.getMinY() <= entity_bounding_box.getMaxY())
		{
			//ball touched paddle from the top edge of the entity
			m_ball.bounceFromHorizontalSurface();
			m_ball.cancelLastMovement();
		}

		if (ball_prev_bounding_box.getMaxY() < entity_bounding_box.getMinY() &&
			ball_bounding_box.getMaxY() >= entity_bounding_box.getMinY())
		{
			//ball touched paddle from the bottom edge of the entity
			m_ball.bounceFromHorizontalSurface();
			m_ball.cancelLastMovement();
		}
		return true;
	}
	return false;
}