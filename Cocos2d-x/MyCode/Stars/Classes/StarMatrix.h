//
//  StarMatrix.h
//  Stars
//
//  Created by HAO on 15-7-18.
//
//

#ifndef __Stars__StarMatrix__
#define __Stars__StarMatrix__

#include <deque>
#include <iostream>

#include "Stars.h"
#include "GameScene.h"

using namespace std;
using namespace cocos2d;

class GameScene;

class StarMatrix : public Node{
    
public:
    static StarMatrix* create(GameScene* scene);
    virtual bool init(GameScene* scene);
    void initMatrix();
    
public:
    Size _winSize;
    
    const static int _ROW_NUM = 10;
    const static int _COL_NUM = 10;
    
private:
    bool _needClear;    //游戏判断不能再继续后,这个flag变成true,开始消除剩下的星星
    GameScene* _my_scene;
    float _clearSumTime;    //累加器
    deque<Stars*>selectedList;
    static float _ONE_CLEAR_TIME;   //每颗星星消除的时间
    Stars* _stars[_ROW_NUM][_COL_NUM];
    
private:
    bool isEnded();
    void adjustMatrix();
    void refreshScore();
    int  getLeftStarNum();
    void deleteSelectedList();
    void clearMatrixOneByOne();
    void getSelectedList(Stars* s);
    Point  getPositionByIndex(int i, int j);
    Stars* getStarByTouch(const Point& p);
    
public:
    void updateStar(float delta);
    void onTouch(const Point& point);
    void setNeedClear(bool b);
};









#endif /* defined(__Stars__StarMatrix__) */












