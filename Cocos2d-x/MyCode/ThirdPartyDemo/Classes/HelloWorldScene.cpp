#include "HelloWorldScene.h"

#include "ShareScene.h"
#include "AuthorizeScene.h"
#include "InformationScene.h"

USING_NS_CC;

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

	auto bg = Sprite::create("bg.png");
	bg->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(bg);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	//授权
	auto authorizeItem = MenuItemImage::create("auth.png", "auth.png", CC_CALLBACK_1(HelloWorld::authorizeFunc, this));
	authorizeItem->setPosition(visibleSize.width/2, visibleSize.height - 200);
	authorizeItem->setScale(1.5, 1.6);

	//分享
	auto shareItem = MenuItemImage::create("share.png", "share.png", CC_CALLBACK_1(HelloWorld::shareFunc, this));
	shareItem->setPosition(authorizeItem->getPositionX(), authorizeItem->getPositionY() - 300);
	shareItem->setScale(1.5, 1.6);

	//获取信息
	auto infoItem = MenuItemImage::create("info.png", "info.png", CC_CALLBACK_1(HelloWorld::informationFunc, this));
	infoItem->setPosition(shareItem->getPositionX(), shareItem->getPositionY()-300);
	infoItem->setScale(1.5, 1.6);

    auto menu = Menu::create(closeItem, authorizeItem, shareItem, infoItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void HelloWorld::authorizeFunc(Ref* pSender) {
	log("authorizeFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, AuthorizeScene::createScene()));
}

void HelloWorld::shareFunc(Ref* pSender) {
	log("shareFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, ShareScene::createScene()));
}

void HelloWorld::informationFunc(Ref* pSender) {
	log("information");

	Director::getInstance()->replaceScene(TransitionFade::create(1, InformationScene::createScene()));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
