//
//  MenuScene.cpp
//  Stars
//
//  Created by HAO on 15-7-17.
//
//

#include "SetLayer.h"
#include "GameData.h"
#include "ExitLayer.h"
#include "GameScene.h"
#include "MenuScene.h"

Scene* MenuScene::scene(){
    
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool MenuScene::init(){
    
    if (!Layer::init()) {
        
        return false;
    }
    
    Size winSize     = Director::getInstance()->getWinSize();
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();
    
//背景
    auto bg = Sprite::create("bg_MenuScene.png");
    Rect rectBg = bg->getBoundingBox();
    float scalex = winSize.width / rectBg.size.width;
    float scaley = winSize.height/ rectBg.size.height;
    bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    bg->setScale(scalex, scaley);
    addChild(bg, -1);
    
//新游戏按钮
    itemStart = MenuItemImage::create("Btn_new.png",
                                      "Btn_new.png",
                                      CC_CALLBACK_1(MenuScene::startGameFunc, this));
    itemStart->setTag(1);
    itemStart->setScale(1.2f, 1.2f);
    itemStart->setPosition(Vec2(-200, visibleSize.height/2 + 100));
    itemStartRect = itemStart->getBoundingBox();
    this->buttonMoveAnimateIn(itemStart, 0.6f, Vec2(itemStartRect.size.width/2, /*visibleSize.height/2 + 80*/itemStart->getPositionY()));
    
    
//设置游戏按钮
    itemSet = MenuItemImage::create("Btn_set.png",
                                     "Btn_set.png",
                                     CC_CALLBACK_1(MenuScene::setGameFunc, this));
    
    itemSet->setTag(2);
    itemSet->setScale(1.2f, 1.2f);
    itemSet->setPosition(Vec2(-200, visibleSize.height/2 - 0));
    
    this->buttonMoveAnimateIn(itemSet, 0.7f, Vec2(itemStartRect.size.width/2, /*visibleSize.height/2 - 0*/itemSet->getPositionY()));
    
//退出游戏按钮
    itemExit = MenuItemImage::create("Btn_exit2.png",
                                     "Btn_exit2.png",
                                     CC_CALLBACK_1(MenuScene::exitGameFunc, this));
    itemExit->setTag(3);
    itemExit->setScale(1.2f, 1.2f);
    itemExit->setPosition(Vec2(-200, visibleSize.height/2 - 100));
    this->buttonMoveAnimateIn(itemExit, 0.8f, Vec2(itemStartRect.size.width/2 , /*visibleSize.height/2 - 80*/itemExit->getPositionY()));
    
    auto menu = Menu::create(itemStart, itemSet, itemExit, NULL);
    //?????
    //menu->alignItemsVertically();
    menu->setPosition(Vec2::ZERO);
    
    addChild(menu);
    
    
//安卓平台返回键监听
    auto listenerKeyBoard = EventListenerKeyboard::create();
    listenerKeyBoard->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);
    
    return true;
}

void MenuScene::startGameFunc(Ref* sender){
    printf("startGameFunc()");
    scaleSelf(sender, 1.3f, 1.1f);

//开始新游戏时清空关数与当前分数
    GAMEDATA::getInstance()->setCurLevel(0);
    GAMEDATA::getInstance()->setCurScore(0);
    
    //回弹
    this->buttonMoveAnimateOut(itemStart);
    this->buttonMoveAnimateOut(itemExit);
    this->buttonMoveAnimateOut(itemSet);
    
    Director::getInstance()->replaceScene(TransitionFade::create(1.5, GameScene::scene()));
}

void MenuScene::setGameFunc(Ref* sender){
    printf("setGameFunc()\n");
    scaleSelf(sender, 1.3f, 1.1f);
    
//回弹
    this->buttonMoveAnimateOut(itemStart);
    this->buttonMoveAnimateOut(itemExit);
    this->buttonMoveAnimateOut(itemSet);
    
//设置层
    SetLayer* layer = new SetLayer();
    layer->setName("SetLayer");
    this->addChild(layer);
}

//退出游戏
void MenuScene::exitGameFunc(Ref* sender){
    printf("exitGameFunc()\n");
    scaleSelf(sender, 1.3f, 1.1f);
    
    //回弹
    this->buttonMoveAnimateOut(itemStart);
    this->buttonMoveAnimateOut(itemExit);
    this->buttonMoveAnimateOut(itemSet);
    
    //设置层
    ExitLayer* layer = new ExitLayer();
    this->addChild(layer);
}

void MenuScene::scaleSelf(Ref* sender, float before, float after){
    
    auto self    = (Menu*)sender;
    
    auto scaleBg = ScaleTo::create(0.1, before);
    auto scaleLt = ScaleTo::create(0.1, after);
    auto seq     = Sequence::create(scaleBg, scaleLt, NULL);
    
    self->runAction(seq);
}

//按钮动画
void MenuScene::buttonMoveAnimateIn(Ref* sender, float delay, Point point){
    
    auto self = (Menu*)sender;
    
    if (self->getTag() == 3) {
        
        printf("Tag = 3_setButton");
    }
    
    auto moveTo1 = MoveTo::create(delay, point);
    auto moveTo2 = MoveTo::create(0.1, point + Vec2(-30, 0));
    auto moveTo3 = MoveTo::create(0.2, point);
    auto seq     = Sequence::create(moveTo1, moveTo2, moveTo3,NULL);

    self->runAction(seq);
}

void MenuScene::buttonMoveAnimateOut(Ref* sender){

    auto self = (Menu*)sender;
    
    float delay;
    
    if (self->getTag() == 1) {  //新游戏
        
        delay = 0.2;
    }
    else if (self->getTag() == 2){  //继续游戏
        
        delay = 0.4;
    }
    else if (self->getTag() == 3){  //设置
        
        delay = 0.6;
    }
    
    auto moveTo1 = MoveTo::create(0.1f, Vec2(self->getPosition() + Vec2(30, 0)));
    auto moveTo2 = MoveTo::create(delay, Vec2(-200, self->getPositionY()));

//移除
    auto callFunc = CallFunc::create([=](){
        self->removeFromParent();
    });
    
    auto seq = Sequence::create(moveTo1, moveTo2, callFunc, NULL);
    
    self->runAction(seq);
}

void MenuScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event){
    
    switch (keycode) {
        case EventKeyboard::KeyCode::KEY_ESCAPE:{  //返回
            
            if (isBack) {   //进入退出层
                isBack = false;
                
                auto callfunc1 = CallFunc::create([=](){
                
                //回弹
                    this->buttonMoveAnimateOut(itemStart);
                    this->buttonMoveAnimateOut(itemExit);
                    this->buttonMoveAnimateOut(itemSet);
                    
                });
                
                auto delay = DelayTime::create(0.5f);
                
                auto callfunc2 = CallFunc::create([=](){
                    
                    ExitLayer* layer = new ExitLayer();
                    layer->setName("ExitLayer");
                    this->addChild(layer);
                });
                
                auto seq = Sequence::create(callfunc1, delay, callfunc2, NULL);
                this->runAction(seq);
                
            }
            else{
                isBack = true;
                
                auto callfunc1 = CallFunc::create([=](){
                    
                    Director::getInstance()->replaceScene( MenuScene::scene());
                });
                
                auto delay = DelayTime::create(0.5f);
                
                auto callfunc2 = CallFunc::create([=](){
                    
                    this->removeChildByName("ExitLayer");
                    this->removeChildByName("SetLayer");
                });
                
                auto seq = Sequence::create(callfunc1, delay, callfunc2, NULL);
                
                this->runAction(seq);
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_MENU:{   //菜单
            printf("KEY_MENU!!");
            break;
        }
        default:
            break;
    }
}






