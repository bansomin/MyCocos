/*************************BEGIN****************************************************
Created by HAO on 2017/04/06
BRIEF	: ÕÊº“≥«≥ÿ
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

using namespace std;

class HomeScene : public Layer {

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HomeScene);

public:
	//≤‚ ‘
	void onTouchesEnded(const vector<Touch*>& touches, Event* event);	//≤‚ ‘

public:
	HomeHubLayer* _hubLayer;
	HomeMapLayer* _mapLayer;
	HomeOptionLayer* _optionLayer;
};

#endif // _HOMESCENE_H__
