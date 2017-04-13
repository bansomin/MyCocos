/*************************BEGIN****************************************************
Created by HAO on 2017/04/06
BRIEF	: Íæ¼Ò³Ç³Ø
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef _HOMESCENE_H__
#define _HOMESCENE_H__

#include "cocos2d.h"

//use
#include "UI\HomeScene\HomeHubLayer.h"
#include "UI\HomeScene\HomeMapLayer.h"
#include "UI\HomeScene\HomeOptionLayer.h"
using namespace cocos2d;

class HomeScene : public Layer {

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HomeScene);

private:
	HomeHubLayer* _hubLayer;
	HomeMapLayer* _mapLayer;
	HomeOptionLayer* _optionLayer;
};

#endif // _HOMESCENE_H__
