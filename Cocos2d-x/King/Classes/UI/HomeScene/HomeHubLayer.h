/*************************BEGIN****************************************************
Created by HAO on 2017/04/07
BRIEF	:	–≈œ¢¿∏
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef _HOMEHUBLAYER_H__
#define _HOMEHUBLAYER_H__

#include "cocos2d.h"
using namespace cocos2d;

//use
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
using namespace cocostudio;
using namespace ui;

class HomeHubLayer : public Layer {

public:
	HomeHubLayer();
	~HomeHubLayer();
	virtual bool init();
	CREATE_FUNC(HomeHubLayer);

public:
	void loadData();
	void loadUI();
	void btnCallback(Ref* sender, Widget::TouchEventType type);

private:
	Size _Wsize;

};

#endif // _HOMEHUBLAYER_H__
