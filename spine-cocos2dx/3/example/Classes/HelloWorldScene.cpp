#include "HelloWorldScene.h"
#include "spine/spine.h"
#include <spine/spine-cocos2dx.h>

USING_NS_CC;
using namespace spine;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	int xNum = 8;
	int yNum = 5;
	for (auto i = 1; i < xNum; i++){
			for (auto j = 1; j < yNum; j++){
				
				auto skeletonNode = spine::BatchSkeletonAnimation::createWithFile("spine/goblins.json", "spine/goblins.atlas", 0.4f);
				skeletonNode->setAnimation(0, "walk", true);
				if ((i + j) % 2 == 0){
					skeletonNode->setSkin("goblin");
				}
				else{
					//goblin
					skeletonNode->setSkin("goblin");
				}
				skeletonNode->setPosition(Vec2(i*visibleSize.width / 8, j*visibleSize.width / 8));
				addChild(skeletonNode);

			}

	}
	

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
