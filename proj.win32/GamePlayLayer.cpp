#include "GamePlayLayer.h"
#include "GameSettings.h"

USING_NS_CC;

GamePlayLayer::GamePlayLayer() : 
    Layer(), 
    m_engine(nullptr),
    m_paddle_sprite(nullptr)
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

    return true;
}

bool GamePlayLayer::setBoundaries()
{
    const Size visible_size = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    const Size design_resolution = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

    auto top_bound_sprite = Sprite::create("bounds.png");
    if (top_bound_sprite == nullptr)
    {
        printf("Error loading bounds.png for top boundary.");
        return false;
    }

    auto bottom_bound_sprite = Sprite::create("bounds.png");
    if (bottom_bound_sprite == nullptr)
    {
        printf("Error loading bounds.png for bottom boundary.");
        return false;
    }

    auto left_bound_sprite = Sprite::create("bounds.png");
    if (left_bound_sprite == nullptr)
    {
        printf("Error loading bounds.png for left boundary.");
        return false;
    }

    auto right_bound_sprite = Sprite::create("bounds.png");
    if (right_bound_sprite == nullptr)
    {
        printf("Error loading bounds.png for right boundary.");
        return false;
    }

    const float bottom = origin.y + ((visible_size.height - design_resolution.height) * 0.5f);
    const float left = origin.x + ((visible_size.width - design_resolution.width) * 0.5f);
    const float top = bottom + design_resolution.height;
    const float right = left + design_resolution.width;
    const Rect gameplay_area(bottom, left, top, right);

    const Size bound_sprite_size = top_bound_sprite->getContentSize();
    const Rect inner_gameplay_area(bottom + bound_sprite_size.height,
        left + bound_sprite_size.width,
        top - bound_sprite_size.height,
        right - bound_sprite_size.width);
    m_inner_gameplay_area = inner_gameplay_area;

    const float horizontal_boundary_scale = design_resolution.width / bound_sprite_size.width;
    const float vertical_boundary_scale = design_resolution.height / bound_sprite_size.height;

    const float bound_sprite_half_width = bound_sprite_size.width * 0.5f;
    const float bound_sprite_half_height = bound_sprite_size.height * 0.5f;

    bottom_bound_sprite->setScaleX(horizontal_boundary_scale);
    const float bottom_bound_sprite_x = gameplay_area.getMidX();
    const float bottom_bound_sprite_y = gameplay_area.getMinY() + bound_sprite_half_height;
    bottom_bound_sprite->setPosition(bottom_bound_sprite_x, bottom_bound_sprite_y);
    this->addChild(bottom_bound_sprite);

    top_bound_sprite->setScaleX(horizontal_boundary_scale);
    const float top_bound_sprite_x = gameplay_area.getMidX();
    const float top_bound_sprite_y = gameplay_area.getMaxY() - bound_sprite_half_height;
    bottom_bound_sprite->setPosition(top_bound_sprite_x, top_bound_sprite_y);
    this->addChild(top_bound_sprite);

    left_bound_sprite->setScaleY(vertical_boundary_scale);
    const float left_bound_sprite_x = gameplay_area.getMinX() + bound_sprite_half_width;
    const float left_bound_sprite_y = gameplay_area.getMidY();
    left_bound_sprite->setPosition(left_bound_sprite_x, left_bound_sprite_y);
    this->addChild(left_bound_sprite);

    right_bound_sprite->setScaleY(vertical_boundary_scale);
    const float right_bound_sprite_x = gameplay_area.getMaxX() - bound_sprite_half_width;
    const float right_bound_sprite_y = gameplay_area.getMidY();
    right_bound_sprite->setPosition(right_bound_sprite_x, right_bound_sprite_y);
    this->addChild(right_bound_sprite);

    return true;
}

bool GamePlayLayer::initPaddle()
{
    m_paddle_sprite = Sprite::create("paddle.png");
    if (m_paddle_sprite == nullptr)
    {
        printf("Error loading bounds.png for top boundary.");
        return false;
    }

    return true;
}