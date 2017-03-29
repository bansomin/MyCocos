//
//  PauseLayer.h
//  Stars
//
//  Created by HAO on 15-7-28.
//
//

#ifndef __Stars__PauseLayer__
#define __Stars__PauseLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class PauseLayer : public LayerColor{

public:
    PauseLayer();
    
private:
    Size _winSize;
    
public:
    void itemCancelFunc();
    void itemRestartFunc();
    void itemExitFunc();
    
    void scaleSelf(Ref* sender, float before, float after);
    
};

#endif /* defined(__Stars__PauseLayer__) */






