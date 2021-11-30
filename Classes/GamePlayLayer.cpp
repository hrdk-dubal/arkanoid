#include "GamePlayLayer.h"
#include "GameSettings.h"

USING_NS_CC;

GamePlayLayer::GamePlayLayer() : 
    Layer(), 
    m_engine(nullptr),
    m_paddle_sprite(nullptr),
    m_is_left_half_touched(false),
    m_is_right_half_touched(false)
{}

GamePlayLayer::~GamePlayLayer()
{
    if (!m_engine)
    {
        delete m_engine;
    }
}

bool GamePlayLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    const bool were_boundaries_initialized = setBoundaries();
    if (!were_boundaries_initialized)
    {
        return false;
    }
    
    /*
    const bool was_paddle_initialized = initPaddle();
    if (!was_paddle_initialized)
    {
        return false;
    }

    const Vec2 init_paddle_position(m_inner_gameplay_area.getMidX(), GameSettings::m_paddle_height);
    m_engine = new Engine(
        init_paddle_position, 
        m_paddle_sprite,
        m_inner_gameplay_area.getMaxX(), 
        m_inner_gameplay_area.getMaxY());
    */

    return true;
}

bool GamePlayLayer::setBoundaries()
{
    Size visible_size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float contentScaleFactor = Director::getInstance()->getContentScaleFactor();
    Size design_resolution = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    ResolutionPolicy r = Director::getInstance()->getOpenGLView()->getResolutionPolicy();

    CCLOG("origin: (%f, %f)", origin.x, origin.y);
    CCLOG("contentScaleFactor: %f", contentScaleFactor);
    CCLOG("visible size: %f x %f", visible_size.width, visible_size.height);
    CCLOG("win size: %f x %f", design_resolution.width, design_resolution.height);
    CCLOG("res policy: %d", r);

    auto bottom_bound_sprite = Sprite::create("bounds.png");
    auto top_bound_sprite = Sprite::create("bounds.png");
    auto left_bound_sprite = Sprite::create("bounds.png");
    auto right_bound_sprite = Sprite::create("bounds.png");
    
    const Rect gameplay_area(0, 0, design_resolution.width, design_resolution.height);

    Size bound_sprite_size = bottom_bound_sprite->getContentSize();
    const float half_boundary_width = bound_sprite_size.width * 0.5f;
    const float half_boundary_height = bound_sprite_size.height * 0.5f;

    const Rect inner_gameplay_area(
        origin.x + half_boundary_width,
        origin.y + half_boundary_height,
        visible_size.width - bound_sprite_size.width,
        visible_size.height - bound_sprite_size.height);
    m_inner_gameplay_area = inner_gameplay_area;

    const float horizontal_boundary_scale = gameplay_area.size.width / bound_sprite_size.width;
    const float vertical_boundary_scale = gameplay_area.size.height / bound_sprite_size.height;

    bottom_bound_sprite->setScaleX(horizontal_boundary_scale);
    const float bottom_bound_sprite_x = gameplay_area.getMidX();
    const float bottom_bound_sprite_y = gameplay_area.getMinY() + half_boundary_height;
    bottom_bound_sprite->setPosition(bottom_bound_sprite_x, bottom_bound_sprite_y);
    this->addChild(bottom_bound_sprite);

    top_bound_sprite->setScaleX(horizontal_boundary_scale);
    const float top_bound_sprite_x = gameplay_area.getMidX();
    const float top_bound_sprite_y = gameplay_area.getMaxY() - half_boundary_height;
    top_bound_sprite->setPosition(top_bound_sprite_x, top_bound_sprite_y);
    this->addChild(top_bound_sprite);

    left_bound_sprite->setScaleY(vertical_boundary_scale);
    const float left_bound_sprite_x = gameplay_area.getMinX() + half_boundary_width;
    const float left_bound_sprite_y = gameplay_area.getMidY();
    left_bound_sprite->setPosition(left_bound_sprite_x, left_bound_sprite_y);
    this->addChild(left_bound_sprite);
    
    right_bound_sprite->setScaleY(vertical_boundary_scale);
    const float right_bound_sprite_x = gameplay_area.getMaxX() - half_boundary_width;
    const float right_bound_sprite_y = gameplay_area.getMidY();
    right_bound_sprite->setPosition(right_bound_sprite_x, right_bound_sprite_y);
    this->addChild(right_bound_sprite);
    

    //this->scheduleUpdate();

    return true;
}

bool GamePlayLayer::initPaddle()
{
    m_paddle_sprite = Sprite::create("paddle.png");
    if (!m_paddle_sprite)
    {
        log("Error loading bounds.png for paddle.");
        return false;
    }

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
    if (m_is_left_half_touched || m_is_right_half_touched)
    {
        return false;
    }

    const Size visible_size = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    const float half_screen = (origin.x + visible_size.width) * 0.5f;

    const Vec2 touch_location = touch->getLocation();

    if (touch_location.x <= half_screen)
    {
        m_is_left_half_touched = true;
        m_is_right_half_touched = false;
    }
    else
    {
        m_is_left_half_touched = false;
        m_is_right_half_touched = true;
    }

    return true;
}

void GamePlayLayer::touchMoved(Touch* touch, Event* event)
{
    // do nothing
}

void GamePlayLayer::touchEnded(Touch* touch, Event* event)
{
    if (m_is_left_half_touched || m_is_right_half_touched)
    {
        m_is_left_half_touched = false;
        m_is_right_half_touched = false;
    }
}

void GamePlayLayer::update(float dt)
{
    if (!m_engine)
    {
        return;
    }
    m_engine->update(dt);

    if (m_is_left_half_touched)
    {
        m_engine->acceleratePaddle();
    }

    if (m_is_right_half_touched)
    {
        m_engine->deceleratePaddle();
    }
}