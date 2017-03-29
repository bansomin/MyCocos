
/*************************BEGIN**************************************************** 
    			Created by HAO on 2016/9/12
    BRIEF	: 	
    VERSION	: 
    HISTORY	:
***************************END****************************************************/
#pragma once

#ifndef __CHOOSELAYER_LAYER__
#define __CHOOSELAYER_LAYER__

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace ui;

typedef enum {

	NOTHING	=	0,
	WHEAT	=	1,
	CORN	=	2,
	CARROT	=	3
} CropsType;

class SeedChooseLayer : public Layer {
	
public:
	virtual bool init () override;
	CREATE_FUNC (SeedChooseLayer);

	CC_SYNTHESIZE (CropsType, currType, currTypeFunc);

public:
	bool onTouchBegan (Touch* touch, Event* event);
	//void chooseCropFunc (Ref* pSender, Widget::TouchEventType type);
	void chooseCropFunc (Ref* pSender, Widget::TouchEventType type);

private:
	Size Wsize;

	Sprite* bgSpr;		//±³¾°Í¼Æ¬
	Node* chooseLayer;	//csb

	ImageView* wheatImg;
	ImageView* cronTmg;
	ImageView* carrotImg;
};


#endif //__CHOOSELAYER_LAYER__















