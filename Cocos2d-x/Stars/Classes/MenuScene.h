//
//  MenuScene.h
//  Stars
//
//  Created by HAO on 15-7-17.
//
//

#ifndef __Stars__MenuScene__
#define __Stars__MenuScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class MenuScene : public Layer{
    
public:
    CREATE_FUNC(MenuScene);
    
    virtual bool init();
    static Scene* scene();
    
public:
    
    bool isBack = true;
    Rect itemStartRect;
    
    MenuItemImage* itemStart;
    MenuItemImage* itemExit;
    MenuItemImage* itemSet;
    
public:
    Size visibleSize;
    
    void setGameFunc(Ref* sender);
    void startGameFunc(Ref* sender);
    void exitGameFunc(Ref* sender);
    
    void scaleSelf(Ref* sender, float before, float after);
    
    void buttonMoveAnimateOut(Ref* sender);
    void buttonMoveAnimateIn(Ref* sender, float delay, Point point);
    
public:
    //安卓平台返回键监听
    virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

    
};

#endif /* defined(__Stars__MenuScene__) */














