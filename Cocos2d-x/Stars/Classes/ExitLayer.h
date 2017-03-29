//
//  ExitLayer.h
//  Stars
//
//  Created by HAO on 15-7-28.
//
//

#ifndef __Stars__ExitLayer__
#define __Stars__ExitLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class ExitLayer : public LayerColor{

public:
    ExitLayer();    
    
private:
    Size _winSize;
    
public:
    void itemExitGameFunc();
    void itemCancelFunc();
    
};

#endif /* defined(__Stars__ExitLayer__) */








