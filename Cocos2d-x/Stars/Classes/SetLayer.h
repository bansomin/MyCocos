//
//  SetLayer.h
//  Stars
//
//  Created by HAO on 15-7-28.
//
//
#ifndef __Stars__SetLayer__
#define __Stars__SetLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class SetLayer : public LayerColor{

public:
    SetLayer();
    
public:
    
    ControlSlider* sliderMusic;
    ControlSlider* sliderSound;
    
    MenuItemImage* checkBoxMusic;
    MenuItemImage* checkBoxSound;
    
    MenuItemImage* sigCheckBoxStarsOne;
    MenuItemImage* sigCheckBoxStarsTwo;

    MenuItemImage* sigCheckBoxHeartsOne;
    MenuItemImage* sigCheckBoxHeartsTwo;

    
public:
    void itemCancelFunc(Ref* sender);
    void checkBoxChangeFunc(Ref* sender);
    void sigcheckBoxChangeFunc(Ref* sender);

    void valueChanged(Ref* sender, Control::EventType type);    
};

#endif /* defined(__Stars__SetLayer__) */














