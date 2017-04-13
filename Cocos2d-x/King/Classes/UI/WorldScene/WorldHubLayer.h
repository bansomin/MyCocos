/*************************BEGIN****************************************************
Created by HAO on 2017/04/10
BRIEF	:	世界信息栏
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef _WORLDHUBLAYER_H__
#define _WORLDHUBLAYER_H__

#include "cocos2d.h"
using namespace cocos2d;

//use
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
using namespace cocostudio;
using namespace ui;
using namespace std;
using namespace cocos2d;

class WorldHubLayer : public Layer {

public:
	WorldHubLayer();
	~WorldHubLayer();
	virtual bool init();
	CREATE_FUNC(WorldHubLayer);

public:
	void loadData();
	void loadUI();
	void btnCallback(Ref* sender, Widget::TouchEventType type);

	void addGold(int count);
	void addWood(int count);

private:
	Size _Wsize;

	string _name;
	int _level;
	int _exp;
	int _expRequire;
	int _ringCount;
	int _goldCount;
	int _woodCount;
	int _goldCapacity;
	int _woodCapacity;

	Text* _goldCountText;
	//Text* _goldCapacityText;
	LoadingBar* _goldBar;

	Text* _woodCountText;
	//Text* _woodCapacityText;
	LoadingBar* _woodBar;

};

#endif // _WORLDHUBLAYER_H__