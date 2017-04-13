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
using namespace std;

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

	void addGold(int count);
	void addWood(int count);
	void addPlayerExp(int count);
	void setMapLayer(Layer* layer);
	void setGoldCapacity(int count);
	void setWoodCapacity(int count);

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

	Layer* _mapLayer;

	Text* _playerName;
	Text* _playerLevel;
	LoadingBar* _playerBar;

	Text* _goldCountText;
	//Text* _goldCapacityText;
	LoadingBar* _goldBar;

	Text* _woodCountText;
	//Text* _woodCapacityText;
	LoadingBar*_woodBar;

	Text* _ringCountText;
};

#endif // _HOMEHUBLAYER_H__
