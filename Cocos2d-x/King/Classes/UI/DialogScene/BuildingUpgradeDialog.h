/*************************BEGIN****************************************************
Created by HAO on 2017/04/18
BRIEF	:	建筑升级栏
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef __BUILDINGUPGRADEDIALOG_H_
#define __BUILDINGUPGRADEDIALOG_H_

#include "cocos2d.h"
using namespace cocos2d;

//use
#include "Model\BuildingSprite.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
using namespace cocostudio;
using namespace ui;

class BuildingUpgradeDialog : public Layer {

	public:
	static BuildingUpgradeDialog* create(BuildingSprite* spr);
	virtual bool init(BuildingSprite* spr);

	public:
	void removeFunc();		//移除		
	void addData();			//加载数据
	void showDialog();		//显示信息栏
	void hideDialog();		//隐藏信息栏
	void showNowInfo();	//当前信息
	void showNextInfo();	//升级后信息
	void showRequire();		//需要的资源数目
	void upgradeFunc(Ref* sender, Widget::TouchEventType type);
	void btnCloseFunc(Ref* sender, Widget::TouchEventType type);

	private:
	Size _Wsize;
	Widget* _ui;
	TextureCache*_cache;	//纹理缓存
	BuildingSprite* _buildingSprite;

	int _goldRequire;
	int _woodRequire;
	int _timeRequire;

	__Dictionary* _chnStr;
};

#endif // __BUILDINGUPGRADEDIALOG_H_


