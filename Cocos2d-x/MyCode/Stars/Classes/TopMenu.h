//
//  TopMenu.h
//  Stars
//
//  Created by HAO on 15-7-19.
//
//

#ifndef __Stars__TopMenu__
#define __Stars__TopMenu__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class TopMenu : public Node{

public:
    CREATE_FUNC(TopMenu);    
    virtual bool init();
    
private:
    Label* _levelContent;
    Label* _curScoreContent;
    Label* _targetScoreContent;
    Label* _highestScoreContent;
    
public:
    void refresh();
};

#endif /* defined(__Stars__TopMenu__) */






