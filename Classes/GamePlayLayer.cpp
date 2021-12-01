#include "GamePlayLayer.h"
#include "GameSettings.h"

USING_NS_CC;

GamePlayLayer::GamePlayLayer() : 
    Layer(), 
    m_engine(nullptr),
    m_game_view(nullptr),
    m_paddle_sprite(nullptr),
    m_is_touch_pressed(false)
{}

GamePlayLayer::~GamePlayLayer()
{
    if (m_engine != nullptr)
    {
        delete m_engine;
        m_engine = nullptr;
    }

    if (m_game_view != nullptr)
    {
        delete m_game_view;
        m_game_view = nullptr;
    }
}

bool GamePlayLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    const Rect inner_gameplay_area(calculateGamePlayArea());

    initBoundarySprites(inner_gameplay_area);
    
    initPaddle(inner_gameplay_area);
    
    const Vec2 init_paddle_position(inner_gameplay_area.getMidX(), GameSettings::m_paddle_height);
    const Size paddle_size(m_paddle_sprite->getContentSize());
    
    initBall(inner_gameplay_area, init_paddle_position, paddle_size);

    const Vec2 init_ball_position(m_ball_sprite->getPosition());
    const Size ball_size(m_ball_sprite->getContentSize());

    m_engine = new Engine(inner_gameplay_area, 
                    init_paddle_position, paddle_size,
                    init_ball_position, ball_size);
    
    m_game_view = new GameView(m_engine, m_paddle_sprite, m_ball_sprite);

    createBrickLayout(inner_gameplay_area);

    return true;
}

Rect GamePlayLayer::calculateGamePlayArea() const
{
    const Rect visible_area(Director::getInstance()->getVisibleOrigin(),
        Director::getInstance()->getVisibleSize());

    const float left_margin = visible_area.getMidX() - (GameSettings::m_game_size.width * 0.5f);
    const float top_margin = visible_area.getMidY() - (GameSettings::m_game_size.height * 0.5f);

    const Rect outer_gameplay_area(left_margin, top_margin,
        GameSettings::m_game_size.width, GameSettings::m_game_size.height);

    auto temp_bound_sprite = Sprite::create("bounds.png");
    CCASSERT(temp_bound_sprite != nullptr, "Error loading bounds.png for boundary size calculation.");
    
    Size bound_sprite_size = temp_bound_sprite->getContentSize();
    const float half_boundary_width = bound_sprite_size.width * 0.5f;
    const float half_boundary_height = bound_sprite_size.height * 0.5f;

    const Rect inner_gameplay_area(
        outer_gameplay_area.getMinX() + half_boundary_width,
        outer_gameplay_area.getMinY() + half_boundary_height,
        outer_gameplay_area.size.width - bound_sprite_size.width,
        outer_gameplay_area.size.height - bound_sprite_size.height);

    return inner_gameplay_area;
}

void GamePlayLayer::initBoundarySprites(const Rect &inner_gameplay_area)
{
    Rect visible_area(Director::getInstance()->getVisibleOrigin(),
                        Director::getInstance()->getVisibleSize());
        
    auto bottom_bound_sprite = Sprite::create("bounds.png");
    CCASSERT(bottom_bound_sprite != nullptr, "Error loading bounds.png for bottom boundary.");
    auto top_bound_sprite = Sprite::create("bounds.png");
    CCASSERT(top_bound_sprite != nullptr, "Error loading bounds.png for top boundary.");
    auto left_bound_sprite = Sprite::create("bounds.png");
    CCASSERT(left_bound_sprite != nullptr, "Error loading bounds.png for left boundary.");
    auto right_bound_sprite = Sprite::create("bounds.png");
    CCASSERT(right_bound_sprite != nullptr, "Error loading bounds.png for right boundary.");
    
    const Size bound_sprite_size(bottom_bound_sprite->getContentSize());
    
    const float horizontal_boundary_width = inner_gameplay_area.size.width + bound_sprite_size.width;
    const float horizontal_boundary_height = inner_gameplay_area.size.height + bound_sprite_size.height;
    const float horizontal_boundary_scale = horizontal_boundary_width / bound_sprite_size.width;
    const float vertical_boundary_scale = horizontal_boundary_height / bound_sprite_size.height;

    const float half_boundary_width = bound_sprite_size.width * 0.5f;
    const float half_boundary_height = bound_sprite_size.height * 0.5f;

    bottom_bound_sprite->setScaleX(horizontal_boundary_scale);
    const float bottom_bound_sprite_x = inner_gameplay_area.getMidX();
    const float bottom_bound_sprite_y = inner_gameplay_area.getMinY() - half_boundary_height;
    bottom_bound_sprite->setPosition(bottom_bound_sprite_x, bottom_bound_sprite_y);
    this->addChild(bottom_bound_sprite);

    top_bound_sprite->setScaleX(horizontal_boundary_scale);
    const float top_bound_sprite_x = inner_gameplay_area.getMidX();
    const float top_bound_sprite_y = inner_gameplay_area.getMaxY() + half_boundary_height;
    top_bound_sprite->setPosition(top_bound_sprite_x, top_bound_sprite_y);
    this->addChild(top_bound_sprite);

    left_bound_sprite->setScaleY(vertical_boundary_scale);
    const float left_bound_sprite_x = inner_gameplay_area.getMinX() - half_boundary_width;
    const float left_bound_sprite_y = inner_gameplay_area.getMidY();
    left_bound_sprite->setPosition(left_bound_sprite_x, left_bound_sprite_y);
    this->addChild(left_bound_sprite);
    
    right_bound_sprite->setScaleY(vertical_boundary_scale);
    const float right_bound_sprite_x = inner_gameplay_area.getMaxX() + half_boundary_width;
    const float right_bound_sprite_y = inner_gameplay_area.getMidY();
    right_bound_sprite->setPosition(right_bound_sprite_x, right_bound_sprite_y);
    this->addChild(right_bound_sprite);
  
    this->scheduleUpdate();
}

void GamePlayLayer::initPaddle(const Rect &inner_gameplay_area)
{
    m_paddle_sprite = Sprite::create("paddle.png");
    CCASSERT(m_paddle_sprite != nullptr, "Error loading for paddle sprite.");
    
    m_paddle_sprite->setPosition(inner_gameplay_area.getMidX(),
        inner_gameplay_area.getMinY() + GameSettings::m_paddle_height);

    this->addChild(m_paddle_sprite);
}

void GamePlayLayer::initBall(const Rect &inner_gameplay_area, 
    const Vec2 &paddle_position, const Size &paddle_size)
{
    m_ball_sprite = Sprite::create("ball.png");
    CCASSERT(m_ball_sprite != nullptr, "Error loading for ball sprite.");
    const Size ball_size(m_ball_sprite->getContentSize());
    const Size half_ball_size = ball_size * 0.5f;
    const Size half_paddle_size = paddle_size * 0.5f;
    const Vec2 init_ball_position(paddle_position.x,
        paddle_position.y + half_paddle_size.height + half_ball_size.height);

    m_ball_sprite->setPosition(init_ball_position);

    this->addChild(m_ball_sprite);
}

void GamePlayLayer::onEnter()
{
    Layer::onEnter();

    auto touch_listener = EventListenerTouchOneByOne::create();
    touch_listener->setSwallowTouches(true);
    touch_listener->onTouchBegan = CC_CALLBACK_2(GamePlayLayer::touchBegan, this);
    touch_listener->onTouchMoved = CC_CALLBACK_2(GamePlayLayer::touchMoved, this);
    touch_listener->onTouchEnded = CC_CALLBACK_2(GamePlayLayer::touchEnded, this);

    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);
}

void GamePlayLayer::onExit()
{
    Layer::onExit();

    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

bool GamePlayLayer::touchBegan(Touch* touch, Event* event)
{
    if (m_is_touch_pressed)
    {
        return false;
    }
    
    const Size visible_size = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    const float half_screen = (origin.x + visible_size.width) * 0.5f;

    const Vec2 touch_location = touch->getLocation();

    if (touch_location.x <= half_screen)
    {
        m_engine->movePaddle(PaddleMovement::move_left);
    }
    else
    {
        m_engine->movePaddle(PaddleMovement::move_right);
    }
    m_is_touch_pressed = true;

    return true;
}

void GamePlayLayer::touchMoved(Touch* touch, Event* event)
{
    // do nothing
}

void GamePlayLayer::touchEnded(Touch* touch, Event* event)
{
    if (m_is_touch_pressed)
    {
        m_is_touch_pressed = false;
        m_engine->stopPaddle();
    }
}

void GamePlayLayer::update(float dt)
{
    if (m_engine == nullptr || m_game_view == nullptr)
    {
        return;
    }

    m_engine->update(dt);

    m_game_view->updateView();
}

void GamePlayLayer::createBrickLayout(const cocos2d::Rect& inner_gameplay_area)
{
    auto temp_brick = Sprite::create("gray_brick.png");
    CCASSERT(temp_brick != nullptr, "Error loading for brick sprite for brick size calculation.");
    const Size brick_size(temp_brick->getContentSize());
    const Size half_brick_size = brick_size * 0.5;

    const float brick_layout_bound_x = (GameSettings::m_numCols * brick_size.width) +
        ((GameSettings::m_numCols - 1) * GameSettings::m_brick_gap);
    const float brick_layout_bound_y = (GameSettings::m_numRows * brick_size.height) +
        ((GameSettings::m_numRows - 1) * GameSettings::m_brick_gap);

    const float leftmost_brick_x_position = inner_gameplay_area.getMidX() -
        (brick_layout_bound_x * 0.5f) + half_brick_size.width;
    float x_position = leftmost_brick_x_position;

    float y_position = inner_gameplay_area.getMaxY() - GameSettings::m_brick_layout_top - half_brick_size.height;

    for (int row = 0; row < GameSettings::m_numRows; row++)
    {
        for (int col = 0; col < GameSettings::m_numCols; col++)
        {
            const Vec2 brick_position(x_position, y_position);
            createBrick(GameSettings::m_brickLayout[row][col], brick_position);
            x_position += brick_size.width + GameSettings::m_brick_gap;
        }
        x_position = leftmost_brick_x_position;
        y_position -= (brick_size.height + GameSettings::m_brick_gap);
    }
}

void GamePlayLayer::createBrick(const BrickType brick_type, const cocos2d::Vec2& position)
{
    std::string brick_image = "";
    switch (brick_type)
    {
    case BrickType::brick_gray:
        brick_image = "gray_brick.png";
        break;
    case BrickType::brick_green:
        brick_image = "green_brick.png";
        break;
    case BrickType::brick_red:
        brick_image = "red_brick.png";
        break;
    }

    auto brick_sprite = Sprite::create(brick_image.c_str());
    CCASSERT(brick_sprite != nullptr, "Error loading brick image.");

    m_game_view->addBrickSprite(brick_sprite);
    const Size brick_size(brick_sprite->getContentSize());
    m_engine->createBrick(brick_type, position, brick_size);

    brick_sprite->setPosition(position);
    this->addChild(brick_sprite);
}