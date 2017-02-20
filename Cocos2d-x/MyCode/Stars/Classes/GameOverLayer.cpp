//
//  GameOverLayer.cpp
//  Stars
//
//  Created by HAO on 15-7-30.
//
//

#include "GameData.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "PauseLayer.h"
#include "GameOverLayer.h"

GameOverLayer::GameOverLayer(){
    
    this->initWithColor(Color4B(150, 150, 150, 150));
    
    _winSize = Director::getInstance()->getWinSize();
    
    //背景
    auto bg     = Sprite::create("bg_pause.png");
    Rect bgRect = bg->getBoundingBox();
    bg->setPosition(Vec2(_winSize.width/2, _winSize.height/2));
    bg->setScale(1.0f, 1.6f);
    this->addChild(bg, -1);
    
    //取消按钮
    auto itemCancel = MenuItemImage::create("Btn_close.png",
                                            "Btn_close.png",
                                            CC_CALLBACK_0(GameOverLayer::itemCancelFunc, this));
    itemCancel->setPosition(Vec2(bg->getPosition() + Vec2(bgRect.size.width/2 - 20, bgRect.size.height - 20)));
    itemCancel->setScale(0.7f);
    
    //重新开始按钮
    auto itemRestart = MenuItemImage::create("Btn_restart.png",
                                             "Btn_restart.png",
                                             CC_CALLBACK_0(GameOverLayer::itemRestartFunc, this));
    
    itemRestart->setPosition(Vec2(bg->getPositionX()/2 + 50, bg->getPositionY()));
    itemRestart->setScale(2.0f);
    
    //退出按钮
    auto itemExit = MenuItemImage::create("Btn_exit.png",
                                          "Btn_exit.png",
                                          CC_CALLBACK_0(GameOverLayer::itemExitFunc, this));
    
    itemExit->setPosition(Vec2(bg->getPositionX()*3/2 - 50, bg->getPositionY()));
    itemExit->setScale(0.9f);
    
    //菜单
    auto menu = Menu::create(itemCancel, itemRestart, itemExit, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    //触摸
    auto callFunc = [](Touch*, Event*){
        
        return true;
    };
    
    auto listenerTouch = EventListenerTouchOneByOne::create();
    listenerTouch->onTouchBegan = callFunc;
    
    listenerTouch->setSwallowTouches(true);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);
    
    //安卓平台返回键监听
    auto listenerKeyBoard = EventListenerKeyboard::create();
    listenerKeyBoard->onKeyReleased = CC_CALLBACK_2(PauseLayer::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);
    
}

void GameOverLayer::itemCancelFunc(){
    
    this->removeFromParentAndCleanup(true);
    Director::getInstance()->resume();
}

void GameOverLayer::itemRestartFunc(){
    
    char tempLevel[20];
    sprintf(tempLevel, "cur_level_score%d",GAMEDATA::getInstance()->getCurLevel());
    
    float tempScore = UserDefault::getInstance()->getFloatForKey(tempLevel);
    
    GAMEDATA::getInstance()->setCurScore(tempScore);
    
    Director::getInstance()->resume();
    this->removeFromParentAndCleanup(true);
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::scene()));
}

void GameOverLayer::itemExitFunc(){
    
    Director::getInstance()->resume();
    this->removeFromParentAndCleanup(true);
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MenuScene::scene()));
}


