#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "GamePlayLayer.h"

USING_NS_CC;

Scene* GamePlayScene::createScene()
{
    return GamePlayScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GamePlayScene.cpp\n");
}

bool GamePlayScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto gameplay_layer = GamePlayLayer::create();
    if (!gameplay_layer)
    {
        return false;
    }

    this->addChild(gameplay_layer); 

    return true;
}