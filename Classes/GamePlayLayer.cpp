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

    const bool were_boundaries_initialized = initBoundarySprites(inner_gameplay_area);
    if (!were_boundaries_initialized)
    {
        return false;
    }
    
    const bool was_paddle_initialized = initPaddle(inner_gameplay_area);
    if (!was_paddle_initialized)
    {
        return false;
    }

    const Vec2 init_paddle_position(inner_gameplay_area.getMidX(), GameSettings::m_paddle_height);
    m_engine = new Engine(inner_gameplay_area, init_paddle_position);
    
    m_game_view = new GameView(m_engine, m_paddle_sprite);

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

bool GamePlayLayer::initBoundarySprites(const Rect &inner_gameplay_area)
{
    Rect visible_area(Director::getInstance()->getVisibleOrigin(),
                        Director::getInstance()->getVisibleSize());
        
    auto bottom_bound_sprite = Sprite::create("bounds.png");
    auto top_bound_sprite = Sprite::create("bounds.png");
    auto left_bound_sprite = Sprite::create("bounds.png");
    auto right_bound_sprite = Sprite::create("bounds.png");
    
    Size bound_sprite_size = bottom_bound_sprite->getContentSize();
    
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

    return true;
}

bool GamePlayLayer::initPaddle(const Rect& inner_gameplay_area)
{
    m_paddle_sprite = Sprite::create("paddle.png");
    if (!m_paddle_sprite)
    {
        CCLOG("Error loading bounds.png for paddle.");
        return false;
    }
    m_paddle_sprite->setPosition(inner_gameplay_area.getMidX(),
        inner_gameplay_area.getMinY() + GameSettings::m_paddle_height);

    this->addChild(m_paddle_sprite);
    return true;
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

    CCLOG("touch begin");

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