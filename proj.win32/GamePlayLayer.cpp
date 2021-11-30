#include "GamePlayLayer.h"

USING_NS_CC;

bool GamePlayLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

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
    const Rect gameplayArea(bottom, left, top, right);

    const Size bound_sprite_size = top_bound_sprite->getContentSize();
    const float horizontal_scale = design_resolution.width / bound_sprite_size.width;

    bottom_bound_sprite->setScaleX(horizontal_scale);
    const float bottom_bound_sprite_x = gameplayArea.getMinX() + (bound_sprite_size.width * 0.5f);
    const float bottom_bound_sprite_y = gameplayArea.getMinY() + (bound_sprite_size.height * 0.5f);
    bottom_bound_sprite->setPosition(bottom_bound_sprite_x, bottom_bound_sprite_y);
    this->addChild(bottom_bound_sprite);
    
    return true;
}