//
//  GameScene.h
//  Stars
//
//  Created by HAO on 15-7-17.
//
//

#ifndef __Stars__GameScene__
#define __Stars__GameScene__

#include <iostream>

#include "TopMenu.h"
#include "cocos2d.h"
#include "FloatWord.h"

using namespace cocos2d;

class StarMatrix;

class GameScene : public Layer{

public:
    CREATE_FUNC(GameScene);
    
    virtual bool init();
    static Scene* scene();
    
private:
    
    bool isBack = true;
    
    Size _winSize;
    TopMenu* _menu;
    Label* _linkNum;
    Size _visibleSize;
    StarMatrix* _matrix;
    FloatWord* _levelMsg;
    FloatWord* _targetScoreMsg;
    
public:
    void hideLinkNum();  //隐藏连击信息
    void refreshMenu(); //刷新顶部信息
    void gotoNextLevel();   //调到下一关
    void gotoGameOver();   //游戏结束
    void floatLevelWord();  //飘出关卡信息
    void showStarMatrix();  //创造星星矩阵(所有星星)
    void removeFloatWord(); //移除关卡信息和目标分数
    void showLinkNum(int size); //显示连击信息
    void floatTargetScoreWord();    //飘出目标分数信息
    void floatLeftStarMsg(int leftNum); //剩余星星的数量
    
    void setGameMenuFunc(Ref* sender);
    
    void scaleSelf(Ref* sender, float before, float after);
    
public:
//每帧刷新调用的回调函数
    virtual void update(float delta);
//触摸事件发生回调的函数
    virtual bool onTouchBegan(Touch* touch, Event* event);
    
//安卓平台返回键监听
    virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    
};

#endif /* defined(__Stars__GameScene__) */






