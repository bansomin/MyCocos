//
//  ExitLayer.cpp
//  Stars
//
//  Created by HAO on 15-7-28.
//
//

#include "MenuScene.h"
#include "ExitLayer.h"

ExitLayer::ExitLayer(){

    this->initWithColor(Color4B(150, 150, 150, 150));
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _winSize = Director::getInstance()->getWinSize();
    
    
//背景
    auto bg     = Sprite::create("bg_pause.png");
    Rect bgRect = bg->getBoundingBox();
    bg->setPosition(Vec2(_winSize.width/2, _winSize.height/2));
    bg->setScale(1.0f, 1.6f);
    this->addChild(bg, -1);

//确定按钮
    auto itemOk = MenuItemImage::create("Btn_ok.png",
                                        "Btn_ok.png",
                                        CC_CALLBACK_0(ExitLayer::itemExitGameFunc, this));
    //itemOk->setPosition(Vec2(bg->getPositionX()/2 + 30, bg->getPositionY() - bgRect.size.height/2));
    itemOk->setPosition(Vec2(_winSize.width/2 - 100, _winSize.height/2 - bgRect.size.height*2/3));
    
//取消按钮
    auto itemCancel = MenuItemImage::create("Btn_close.png",
                                            "Btn_close.png",
                                            CC_CALLBACK_0(ExitLayer::itemCancelFunc, this));
    //itemCancel->setPosition(Vec2(bg->getPositionX()*3/2 - 30, bg->getPositionY() - bgRect.size.height/2));
    itemCancel->setPosition(Vec2(_winSize.width/2 + 100, _winSize.height/2 - bgRect.size.height*2/3));
    itemCancel->setScale(0.85f);
    
//菜单
    auto menu = Menu::create(itemOk, itemCancel, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
//提示信息
    auto label = Label::createWithSystemFont("确定退出游戏?", "Arial", 40);
    label->setColor(Color3B::RED);
    label->setAnchorPoint(Vec2(0.5, 0.5));
    label->setPosition(Vec2(_winSize.width/2, _winSize.height/2 + 20));
    addChild(label);
    
//触摸
    auto callFunc = [](Touch*, Event*){
        
        return true;
    };
    
    auto listenerTouch = EventListenerTouchOneByOne::create();
    listenerTouch->onTouchBegan = callFunc;
    
    listenerTouch->setSwallowTouches(true);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);
 
}

void ExitLayer::itemExitGameFunc(){
    printf("ExitLayer_itemExitGameFunc()");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}

void ExitLayer::itemCancelFunc(){
    printf("ExitLayer_itemCancelFunc()");
 
    this->removeFromParentAndCleanup(true);
    
    auto scene = MenuScene::scene();
    Director::getInstance()->replaceScene(scene);
}



