#include "HelloWorldScene.h"

//use
#include "Utils\GlobalManager.h"
#include "Utils/Config.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio::timeline;

USING_NS_CC;

//资源数目
static int resCount = 0;

bool HelloWorld::init()
{

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//加载CSB
	_rootNode = CSLoader::createNode("LoadingLayer.csb");
	_loadingBar = static_cast<LoadingBar*>(_rootNode->getChildByName("LoadingBar_1"));
	_text = static_cast<Text*>(_rootNode->getChildByName("Text_1"));

    this->addChild(_rootNode);
	_rootNode->setOpacity(0);

	auto loadingResFunc = CallFunc::create(CC_CALLBACK_0(HelloWorld::loadingRes, this));
	auto action = Sequence::create(FadeTo::create(1.0f, 255),
								   loadingResFunc,
								   nullptr);
	_rootNode->runAction(action);

    return true;
}

//开始加载资源
void HelloWorld::loadingRes() {

	auto cache = Director::getInstance()->getTextureCache();	//缓存

	//资源异步加载
	cache->addImageAsync(IMG_CHAPTER_BG, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_GRAY_BG, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_HOME_BG, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_LOADING_BG, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_WORLD_BG, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BG_MAP, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
};

void HelloWorld::loadResourcesUpdate() {

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist, png);

	resCount++;
	//更新进度条
	float percent = 100*resCount/6;	//一共需要加载5次
	_loadingBar->setPercent(percent);
	_text->setString(StringUtils::format("%d%c", (int)_loadingBar->getPercent(), '%'));

	//加载完成,场景跳转
	if((int)_loadingBar->getPercent()>=100) {

		auto changeSceneFunc = CallFunc::create(CC_CALLBACK_0(HelloWorld::changeScene, this));
		auto delaytime = DelayTime::create(0.5f);
		this->runAction(
			Sequence::create(
				delaytime,
				changeSceneFunc,
				nullptr
			)
		);
	}
};

//场景跳转
void HelloWorld::changeScene() {
	log("changeScene");

	//GM()->enterHomeScene();
	GlobalManager::getInstance()->enterHomeScene();
};

Scene* HelloWorld::createScene() {

	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}