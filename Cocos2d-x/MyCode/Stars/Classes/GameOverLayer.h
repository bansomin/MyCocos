//
//  GameOverLayer.h
//  Stars
//
//  Created by HAO on 15-7-30.
//
//

#ifndef __Stars__GameOverLayer__
#define __Stars__GameOverLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class GameOverLayer : public LayerColor{
    
public:
    GameOverLayer();
    
private:
    Size _winSize;
    
public:
    void itemCancelFunc();
    void itemRestartFunc();
    void itemExitFunc();
    
    void scaleSelf(Ref* sender, float before, float after);    
};

#endif /* defined(__Stars__GameOverLayer__) */















